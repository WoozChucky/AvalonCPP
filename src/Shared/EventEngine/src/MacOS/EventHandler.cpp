//
// Created by nunol on 04/03/2020.
//

#include <Events/EventHandler.hpp>

EventHandler::EventHandler(EventHandle serverHandle, SocketProtocol protocol) {
	this->_serverHandle = serverHandle;
	this->_serverProtocol = protocol;
}

HandledEvent EventHandler::DigestTCPEvent(Event event) {

	HandledEvent evt{nullptr, Weird};

	if (event.ident == this->_serverHandle) {

		evt.Context = nullptr;

	} else {

		auto ctx = reinterpret_cast<SocketContext *>(event.udata);

		evt.Context = ctx;

		if ((event.flags & EV_EOF) || (event.flags & EV_ERROR)) { // Error or EOF Event

			evt.Type = EventType::Disconnect;
		}

		if (event.filter == EVFILT_READ) { // Read Event

			evt.Type = EventType::Read;
		}

		if (event.filter == EVFILT_WRITE) { // Write Event

			evt.Type = EventType::Write;
		}

	}

	return evt;
}

HandledEvent EventHandler::DigestUDPEvent(Event event) {

	HandledEvent evt{nullptr,Weird};

	evt.Context = new SocketContext;
	evt.Context->Socket = {
		this->_serverHandle, 0, Unsupported, Unknown
	};
	evt.Context->TLS = nullptr;
	evt.Context->Secure = false;

	if ((event.flags & EV_EOF) || (event.flags & EV_ERROR)) { // Error or EOF Event

		evt.Type = EventType::Disconnect;
	}

	if (event.filter == EVFILT_READ) { // Read Event

		evt.Type = EventType::Read;
	}

	if (event.filter == EVFILT_WRITE) { // Write Event

		evt.Type = EventType::Write;
	}

	return evt;
}

HandledEvent EventHandler::DigestEvent(Event event) {
	switch (this->_serverProtocol) {
		default:
		case TCP:
			return this->DigestTCPEvent(event);
		case UDP:
			return this->DigestUDPEvent(event);
	}
}
