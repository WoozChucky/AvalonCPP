//
// Created by Nuno on 10/21/2021.
//

#include <Socket/IServer.hpp>

class UdpSocketServer : public IServer {

 public:

	explicit UdpSocketServer(ServerConfiguration* configuration)
		: IServer(configuration)  {
	}

	virtual void Setup() override {

	}

	virtual void Boot() override {

	}

	virtual void Terminate() override {

	}

 protected:

	virtual IChannel * GetChannel() override {
		return nullptr;
	}

	virtual void HandleDisconnectionEvent(SocketContext *handle) override {

	}

};

