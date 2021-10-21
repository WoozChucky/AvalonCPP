//
// Created by Nuno Silva on 20/10/2021.
//

#ifndef AVALON_SRC_SHARED_SOCKETSERVER_INCLUDE_SOCKET_ISERVER_H_
#define AVALON_SRC_SHARED_SOCKETSERVER_INCLUDE_SOCKET_ISERVER_H_

#include <Abstractions/MemoryPool.hpp>
#include <Socket/Sugar.hpp>
#include <Socket/Channels/IChannel.hpp>
#include <Events/EventManager.hpp>
#include <Events/EventHandler.hpp>

class IServer {

 public:

	virtual void Setup() = 0;
	virtual void Boot() = 0;
	virtual void Terminate() = 0;

	virtual void OnMessage(OnMessageDelegate delegate);
	virtual void OnClientConnected(OnClientDelegate delegate);
	virtual void OnClientDisconnected(OnClientDelegate delegate);

	static std::shared_ptr<IServer> makeShared(ServerConfiguration* configuration);

 protected:

	explicit IServer(ServerConfiguration* configuration);

	virtual IChannel * GetChannel() = 0;

	virtual void HandleDisconnectionEvent(SocketContext *handle) = 0;

	virtual void SetEventManager(EventManager* eventManager);

	SocketHandle GetHandle() const;

 private:

	SocketProtocol *protocol{};
	SocketAddressIn serverAddress{};
	SocketHandle serverSocket{};
	EventManager* manager{};
	EventHandler* handler{};
	IChannel* channel{};
	MemoryPool* connectionsMemPool{};
	ServerConfiguration* configuration;

	OnMessageDelegate messageDelegate;
	OnClientDelegate clientConnectedDelegate;
	OnClientDelegate clientDisconnectedDelegate;

};

#endif //AVALON_SRC_SHARED_SOCKETSERVER_INCLUDE_SOCKET_ISERVER_H_
