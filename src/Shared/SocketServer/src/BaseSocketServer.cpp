//
// Created by Nuno on 10/21/2021.
//

#include <Socket/IServer.hpp>
#include "TcpSocketServer.cpp"
#include "UdpSocketServer.cpp"
#include <utility>

/*
 * Public Methods
 */

std::shared_ptr<IServer> IServer::makeShared(ServerConfiguration *configuration) {
	switch (configuration->Protocol) {
		case UDP:
			return std::make_shared<UdpSocketServer>(configuration);
		case TCP:
			return std::make_shared<TcpSocketServer>(configuration);
	}
	throw new std::runtime_error("No protocol was defined");
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

IServer::IServer(ServerConfiguration *configuration) {
	this->configuration = configuration;
}

void IServer::SetEventManager(EventManager *eventManager) {
	this->manager = eventManager;
}

SocketHandle IServer::GetHandle() const {
	return this->serverSocket;
}

SocketProtocol* IServer::GetProtocol() {
	return this->protocol;
}

SocketAddressIn IServer::GetAddress() {
	return this->serverAddress;
}

EventManager* IServer::GetEventManager() {
	return this->manager;
}

EventHandler* IServer::GetEventHandler() {
	return this->handler;
}

ServerConfiguration* IServer::GetConfiguration() {
	return this->configuration;
}

