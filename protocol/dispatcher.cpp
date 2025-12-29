// dispatcher.cpp
#include "dispatcher.hpp"
#include "packet_builder.hpp"
#include "server/map_generator.hpp"
#include <random>

PacketDispatcher::PacketDispatcher(ServerState& state,
                                   boost::asio::ip::udp::socket& socket)
    : state_(state), socket_(socket)
{
}

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

        // case PacketType::Input: {
        //     auto input = parse_input(buf);
        //     handle_input(input, from);
        //     break;
        // }

        default:
            break;
    }
}

void PacketDispatcher::handle_join(const Endpoint& from) {
    if (!state_.map.has_value()) {
        uint32_t seed = std::random_device{}();
        state_.map = MapGenerator::generate(seed);

        std::cout << "Map generated with seed "
                  << seed << "\n";
    }

    auto packet = build_map_init_packet(*state_.map);

    socket_.send_to(
        boost::asio::buffer(packet),
        from
    );

    std::cout << "Sent map to "
              << from.address().to_string()
              << ":" << from.port() << "\n";
}

// void PacketDispatcher::handle_input(
//     const InputPacket& pkt,
//     const Endpoint& from
// ) {
//     std::cout << "INPUT from "
//               << from.address().to_string()
//               << ":" << from.port()
//               << " | player=" << pkt.player_id
//               << " dx=" << pkt.dx
//               << " dy=" << pkt.dy
//               << "\n";
// }
