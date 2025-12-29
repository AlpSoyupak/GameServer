// dispatcher.hpp
#pragma once

#include "packet_parser.hpp"
#include "server/server_state.hpp" 
#include "protocol/net_types.hpp" 
#include <boost/asio/ip/udp.hpp>
#include <iostream>

class PacketDispatcher {
public:
    PacketDispatcher(ServerState& state,
                     boost::asio::ip::udp::socket& socket);

    void dispatch(const std::byte* data, size_t size, const Endpoint& from);

private:
    ServerState& state_;
    boost::asio::ip::udp::socket& socket_;

    void handle_join(const Endpoint& from);
};

