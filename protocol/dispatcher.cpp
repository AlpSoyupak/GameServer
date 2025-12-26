// dispatcher.cpp
#include "dispatcher.hpp"

void PacketDispatcher::dispatch(
    const std::byte* data,
    size_t size,
    const Endpoint& from
) {
    ReadBuffer buf(data, size);

    auto header = parse_header(buf);
    if (header.version != PROTOCOL_VERSION)
        return;

    switch (header.type) {
        case PacketType::Join:
            handle_join(from);
            break;

        case PacketType::Input: {
            auto input = parse_input(buf);
            handle_input(input, from);
            break;
        }

        default:
            break;
    }
}

void PacketDispatcher::handle_join(const Endpoint& from) {
    std::cout << "JOIN from "
              << from.address().to_string()
              << ":" << from.port() << "\n";
}

void PacketDispatcher::handle_input(
    const InputPacket& pkt,
    const Endpoint& from
) {
    std::cout << "INPUT from "
              << from.address().to_string()
              << ":" << from.port()
              << " | player=" << pkt.player_id
              << " dx=" << pkt.dx
              << " dy=" << pkt.dy
              << "\n";
}
