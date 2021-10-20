//
// Created by Nuno Levezinho on 04/03/2020.
//

#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <Abstractions/Types.hpp>

/**
 * @brief
 */
class EventHandler {

public:

    /**
     * @brief
     * @param serverHandle
     */
    explicit EventHandler(EventHandle serverHandle, SocketProtocol protocol);

    /**
     * @brief
     * @param [in]event
     * @return
     */
    HandledEvent DigestEvent(Event event);

private:
    EventHandle  _serverHandle;
	SocketProtocol _serverProtocol;

	HandledEvent DigestTCPEvent(Event event);
	HandledEvent DigestUDPEvent(Event event);
};

#endif //EVENTHANDLER_HPP
