#include <boost/asio.hpp>
#include <iostream>
#include <array>

#include "protocol/dispatcher.hpp"

using boost::asio::ip::udp;

int main() {
    try {
        boost::asio::io_context io;

        udp::socket socket(io, udp::endpoint(udp::v4(), 7777));

        PacketDispatcher dispatcher;

        std::array<std::byte, 1024> recv_buffer;
        udp::endpoint remote_endpoint;

        std::cout << "UDP server listening on port 7777...\n";

        for (;;) {
            size_t bytes = socket.receive_from(
                boost::asio::buffer(recv_buffer),
                remote_endpoint
            );

            dispatcher.dispatch(
                recv_buffer.data(),
                bytes,
                remote_endpoint
            );
        }

    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }

    return 0;
}

