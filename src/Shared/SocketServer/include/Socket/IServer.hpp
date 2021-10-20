//
// Created by Nuno Silva on 20/10/2021.
//

#ifndef AVALON_SRC_SHARED_SOCKETSERVER_INCLUDE_SOCKET_ISERVER_H_
#define AVALON_SRC_SHARED_SOCKETSERVER_INCLUDE_SOCKET_ISERVER_H_

class IServer {

 public:

	virtual void Setup() = 0;
	virtual void Boot() = 0;
	virtual void Terminate() = 0;

	virtual void OnMessage(OnMessageDelegate delegate);
	virtual void OnClientConnected(OnClientDelegate delegate);
	virtual void OnClientDisconnected(OnClientDelegate delegate);

 protected:

	IChannel * GetChannel();

	SocketHandle GetHandle() const;

 private:

};

#endif //AVALON_SRC_SHARED_SOCKETSERVER_INCLUDE_SOCKET_ISERVER_H_
