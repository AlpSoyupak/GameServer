// dispatcher.hpp
#pragma once

#include "packet_parser.hpp"
#include <boost/asio/ip/udp.hpp>
#include <iostream>


class PacketDispatcher {
public:
    using Endpoint = boost::asio::ip::udp::endpoint;

    void dispatch(const std::byte* data, size_t size, const Endpoint& from);

private:
    void handle_join(const Endpoint& from);
    void handle_input(const InputPacket& pkt, const Endpoint& from);
};

