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

        case PacketType::Command: {
            auto cmd = parse_command(buf);
            handle_command(cmd);
            break;
        }

        default:
            break;
    }
}

void PacketDispatcher::handle_join(const Endpoint& from) {
    // Register client if not already connected
    auto it = std::find_if(
        state_.clients.begin(),
        state_.clients.end(),
        [&from](const ClientInfo& c) { return c.endpoint == from; }
    );

    if (it == state_.clients.end()) {
        ClientInfo client;
        client.endpoint = from;
        client.player_id = static_cast<uint32_t>(state_.clients.size() + 1); // assign new player ID
        state_.clients.push_back(client);

        std::cout << "New client joined: player_id=" << client.player_id
                  << " from " << from.address().to_string() << ":" << from.port() << "\n";
    }

    // Generate map if first client
    if (!state_.map.has_value()) {
        uint32_t seed = std::random_device{}();
        state_.map = MapGenerator::generate(seed);

        std::cout << "Map generated with seed "
                  << seed << "\n";
    }

    // Send map to client
    auto packet = build_map_init_packet(*state_.map);
    socket_.send_to(
        boost::asio::buffer(packet),
        from
    );
    std::cout << "Sent map to "
              << from.address().to_string()
              << ":" << from.port() << "\n";
}

void PacketDispatcher::handle_command(const CommandPacket& cmd) {
    // 1. Validate unit exists
    // auto it = state_.units.find(cmd.unit_id);
    // if (it == state_.units.end()) return;

    // Unit& unit = it->second;
    Unit unit;
    // 2. Validate player ownership
    // if (unit.player_id != cmd.player_id) return;

    // 3. Validate target tile is walkable
    if (!state_.map->is_walkable(cmd.target_x, cmd.target_y)) return;

    // 4. Apply movement (authoritative)
    unit.target_x = cmd.target_x;
    unit.target_y = cmd.target_y;
    unit.is_moving = true;

    std::cout << "Move command applied: unit=" << cmd.unit_id
              << " -> (" << cmd.target_x << ", "
              << cmd.target_y << ")\n";

    // 5. Optionally: broadcast movement to all clients
    auto update_packet = build_unit_update_packet(unit);
    for (auto& client : state_.clients) {
        socket_.send_to(boost::asio::buffer(update_packet), client.endpoint);
        std::cout << "Sent movement acknowledgement to "
            << client.endpoint.address().to_string()
            << ":" << client.endpoint.port() << "\n";
    }
}
