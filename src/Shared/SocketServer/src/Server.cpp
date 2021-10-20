//
// Created by Nuno Levezinho Silva on 30/09/2019.
//

#include <Socket/Server.hpp>

#include <Socket/Channels/SecureChannel.hpp>
#include <Socket/Channels/NormalChannel.hpp>

#include <Abstractions/Format.hpp>
#include <Abstractions/ThreadPool.hpp>
#include <Abstractions/Timer.hpp>

Server::Server()
        : serverSocket(0), serverAddress{}, manager{nullptr}, handler{nullptr}, channel{nullptr},
          connectionsMemPool{new MemoryPool(sizeof(SocketContext), 3, 100)},
          threadPool{new ThreadPool(1)},
          _configuration{nullptr}, running{false}
{ }

Server::Server(ServerConfiguration* configuration)
        : serverSocket{0}, serverAddress{}, manager{nullptr}, handler{nullptr}, channel{nullptr},
          connectionsMemPool{new MemoryPool(sizeof(SocketContext), 3, 100)},
          threadPool{new ThreadPool(1)},
          running{false}, _configuration{configuration}{
    assert(configuration != nullptr);
}

void Server::Setup() {
    assert(this->_configuration != nullptr);

	this->protocol = this->_configuration->Protocol;

    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->_configuration->ServerPort);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    bzero(&(this->serverAddress.sin_zero), sizeof(this->serverAddress.sin_zero));

    this->serverSocket = socket(
		AF_INET,
		this->protocol == TCP ? SOCK_STREAM : SOCK_DGRAM,
		this->protocol == TCP ? IPPROTO_TCP : IPPROTO_IP
	);

    for(auto option : this->_configuration->SocketOptions) {
        if (!this->SetSocketOption(option)) {
            TRACE("Failed to set socket option %d.", option);
        }
    }

    if (this->protocol == TCP && this->_configuration->SSLEnabled) {
        this->channel = new SecureChannel(
                this->_configuration->SSLCertificatePath,
                this->_configuration->SSLPrivateKeyPath
            );
    } else {
        this->channel = new NormalChannel();
    }

    this->handler = new EventHandler(this->GetHandle(), this->protocol);
}

void send_message(SocketAddressIn socketAddress) {
	int fd;
	int r;
	struct msghdr msg;
	struct iovec iov;

	fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	assert(fd != -1);

	memset(&msg, 0, sizeof(msg));

	const char *tmp = "xxxx";
	char buffer[50];

	memset(buffer, 0, sizeof buffer);
	strncpy(buffer, tmp, sizeof buffer - 1);

	r = sendto(fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &socketAddress, sizeof(socketAddress));

	if (r < 0) {
		TRACE("%s %s.", "Socket sendto() failed.", strerror(errno));
	}

	close(fd);
}

void Server::Boot() {
    assert(this->_configuration != nullptr);

	if (this->manager == nullptr) {
		TRACE("%s", "EventManager not set.")
		throw std::runtime_error(
			"SocketServer->EventManager not set"
		);
	}

	int flags;
	if((flags = fcntl(this->serverSocket, F_GETFD, 0)) < 0)
	{
		TRACE("%s", "Failed getting socket properties")
		close(this->serverSocket);
		throw std::runtime_error(
			Format::This("Failed getting socket properties %s.", strerror(errno))
		);
	}

	flags |= O_NONBLOCK;
	if (fcntl(this->serverSocket, F_SETFL, flags) < 0) { // Mark server socket as non blocking
		TRACE("%s", "Failed setting socket properties")
		close(this->serverSocket);
		throw std::runtime_error(
			Format::This("Failed setting socket properties %s.", strerror(errno))
		);
	}

    if (bind(this->serverSocket, (struct sockaddr *)&this->serverAddress, sizeof(SocketAddress)) < 0) {
        TRACE("%s %s.", "Socket bind() failed.", strerror(errno));
        close(this->serverSocket);
        throw std::runtime_error(
                    Format::This("Socket bind() failed. %s.", strerror(errno))
                    );
    }

	if (this->protocol == TCP) {
		if (listen(this->serverSocket, this->_configuration->MaxQueuedConnections) < 0) {
			TRACE("%s %s.", "Socket listen() failed.", strerror(errno));
			close(this->serverSocket);
			throw std::runtime_error(
				Format::This("Socket listen() failed. %s.", strerror(errno))
			);
		}
	}

	send_message(this->serverAddress);

    this->manager->RegisterEvent(this->GetHandle(), EventType::Read, EventAction::Add);

    this->running = true;

    TRACE("Running..%s", ".")

    this->HandleConnections();
}

void Server::Terminate() {

    // stop the main event loop
    this->running = false;

    // unregister server socket from read notifications
    this->manager->RegisterEvent(this->GetHandle(), EventType::Read, EventAction::Delete);

    // close the transport channel
    this->GetChannel()->Terminate();

    // close the server file descriptor
    close(this->GetHandle());
}

void Server::SetConfiguration(ServerConfiguration *configuration) {
    assert(configuration != nullptr);
    this->_configuration = configuration;
}

void Server::SetEventManager(EventManager *eventManager) {
    this->manager = eventManager;
}

void Server::OnMessage(OnMessageDelegate delegate) {
    this->messageDelegate = std::move(delegate);
}

void Server::OnClientConnected(OnClientDelegate delegate) {
    this->clientConnectedDelegate = std::move(delegate);
}

void Server::OnClientDisconnected(OnClientDelegate delegate) {
    this->clientDisconnectedDelegate = std::move(delegate);
}

void Server::HandleDisconnectionEvent(SocketContext *ctx) {

    // Register the disconnection event
    this->manager->RegisterEvent(ctx->Socket.Handle, EventType::Read, EventAction::Delete);

    this->channel->DisposeConnection(ctx);

    this->clientDisconnectedDelegate(ctx);

    this->connectionsMemPool->Release(ctx);
}

IChannel * Server::GetChannel() {
    return this->channel;
}

SocketHandle Server::GetHandle() const {
    return this->serverSocket;
}

bool Server::SetSocketOption(int option) const {

    int optval = 1;
    socklen_t  optlen = sizeof(optval);

    auto error = setsockopt(this->serverSocket, SOL_SOCKET, option, &optval, optlen) < 0;
    if(error) {
        perror("setsockpot()");
        close(this->serverSocket);
    }

    return optval;
}

U16 Server::GetSocketOption(int option) const {

    int optval = 1;
    socklen_t  optlen = sizeof(optval);

    auto error = getsockopt(this->serverSocket, SOL_SOCKET, option, &optval, &optlen) < 0;

    if (error) {
        perror("getsockopt()");
        close(this->serverSocket);
    }

    return optval;
}

void Server::HandleConnections() {

    int maxEvents = 32;
    auto evtList = static_cast<Event *>(malloc(sizeof(Event) * maxEvents));
    int nEvents;

    while (this->running) {

        nEvents = this->manager->GetFiredNotifications(evtList, maxEvents);

        // iterate through all of the events received
        for (auto i = 0; i < nEvents; ++i) {

            auto result = this->handler->DigestEvent(evtList[i]);

            if (result.Context == nullptr && this->protocol == TCP) {

                this->HandleNewConnectionEvent();

            } else {

                switch (result.Type)
                {
                    case Read:

                        try {
                            this->HandleMessageEvent(result.Context);
                        } catch (...) {
                            TRACE("%s", "Error HandleMessageEvent");
                        }

                        break;
                    case Write:

                        //TODO(Levezinho): Think about how we can handle this case.
                        TRACE("%s", "Socket Wanted to Write!");

                        break;
                    case Disconnect:

                        this->HandleDisconnectionEvent(result.Context);

                        break;
                    case Weird:
                        TRACE("%s", "Socket Wanted to Write!");
                        break;
                }

            }
        }

    }

    free(evtList);
}

void Server::HandleNewConnectionEvent() {

    // accept the client
    auto* ctx = this->connectionsMemPool->Allocate<SocketContext>();

    auto timer = new Timer(true);

    this->channel->AcceptConnection(this->GetHandle(), ctx);

    TRACE("Accepted Connection took %f ms", timer->Stop() * 0.001)

    if (this->clientConnectedDelegate != nullptr)
        this->clientConnectedDelegate(ctx);

    // register read events from client
    this->manager->RegisterEvent(ctx, EventType::Read, EventAction::Add, true);
}

void Server::HandleMessageEvent(SocketContext *ctx) {

    auto buffer = this->channel->Read(ctx);

    if (!buffer.empty()) {

        if (this->messageDelegate != nullptr) {

            this->messageDelegate(ctx, buffer);

        } else {
            TRACE("%s", "Received a message, but no message delegate was defined.");
        }

    } else {
        TRACE("%s", "Received a message, but no bytes could be read.");
    }

}

std::shared_ptr<Server> Server::makeShared(ServerConfiguration* configuration) {
	return std::make_shared<Server>(configuration);
}
