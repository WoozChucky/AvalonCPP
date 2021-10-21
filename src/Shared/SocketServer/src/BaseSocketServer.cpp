//
// Created by Nuno on 10/21/2021.
//

#include <Socket/IServer.hpp>
#include <utility>

/*
 * Public Methods
 */

IServer::IServer(ServerConfiguration *configuration) {
	this->configuration = configuration;
}

std::shared_ptr<IServer> IServer::makeShared(ServerConfiguration *configuration) {
	return std::shared_ptr<IServer>();
}


void IServer::OnMessage(OnMessageDelegate delegate) {
	this->messageDelegate = std::move(delegate);
}

void IServer::OnClientConnected(OnClientDelegate delegate) {
	this->clientConnectedDelegate = std::move(delegate);
}

void IServer::OnClientDisconnected(OnClientDelegate delegate) {
	this->clientDisconnectedDelegate = std::move(delegate);
}

/*
 * Protected Methods
 */

void IServer::SetEventManager(EventManager *eventManager) {
	this->manager = eventManager;
}

SocketHandle IServer::GetHandle() const {
	return this->serverSocket;
}


