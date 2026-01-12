#include "network/generated_messages.hpp"

#include <vector>

namespace net {

std::vector<uint8_t> CONNECTED::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write entries
    {
        uint32_t size = static_cast<uint32_t>(entries.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : entries) {
        buffer.push_back(elem.code);
        buffer.push_back((elem.timestamp >> 24) & 0xFF);
        buffer.push_back((elem.timestamp >> 16) & 0xFF);
        buffer.push_back((elem.timestamp >> 8) & 0xFF);
        buffer.push_back((elem.timestamp >> 0) & 0xFF);
        }

    return buffer;
}

CONNECTED CONNECTED::deserialize(const std::vector<uint8_t>& data) {
    CONNECTED msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read entries
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.entries.resize(size);
    }
    for (auto& elem : msg.entries) {
        elem.code = data[offset];
        offset += 1;
        elem.timestamp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
        }

    return msg;
}

std::vector<uint8_t> DISCONNEXION::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

DISCONNEXION DISCONNEXION::deserialize(
    const std::vector<uint8_t>& data) {
    DISCONNEXION msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> ERROR_TOO_MANY_CLIENTS::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

ERROR_TOO_MANY_CLIENTS ERROR_TOO_MANY_CLIENTS::deserialize(
    const std::vector<uint8_t>& data) {
    ERROR_TOO_MANY_CLIENTS msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> PACKET_LOSS::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write code
    buffer.push_back(code);

    return buffer;
}

PACKET_LOSS PACKET_LOSS::deserialize(const std::vector<uint8_t>& data) {
    PACKET_LOSS msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read code
    msg.code = data[offset];
    offset += 1;

    return msg;
}

std::vector<uint8_t> I_MISSED_SOMETHING::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

I_MISSED_SOMETHING I_MISSED_SOMETHING::deserialize(
    const std::vector<uint8_t>& data) {
    I_MISSED_SOMETHING msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> PING::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

PING PING::deserialize(const std::vector<uint8_t>& data) {
    PING msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> PONG::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

PONG PONG::deserialize(const std::vector<uint8_t>& data) {
    PONG msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> LOGIN::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write username
    for (uint32_t i = 0; i < 256; ++i) {
        buffer.push_back(username[i]);
    }

    return buffer;
}

LOGIN LOGIN::deserialize(const std::vector<uint8_t>& data) {
    LOGIN msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read username
    std::memcpy(msg.username, data.data() + offset, 256);
    offset += 256;

    return msg;
}

std::vector<uint8_t> LOGOUT::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

LOGOUT LOGOUT::deserialize(const std::vector<uint8_t>& data) {
    LOGOUT msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> LOGGED_IN::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write id
    buffer.push_back((id >> 24) & 0xFF);
    buffer.push_back((id >> 16) & 0xFF);
    buffer.push_back((id >> 8) & 0xFF);
    buffer.push_back((id >> 0) & 0xFF);

    return buffer;
}

LOGGED_IN LOGGED_IN::deserialize(const std::vector<uint8_t>& data) {
    LOGGED_IN msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read id
    msg.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
        (static_cast<uint32_t>(data[offset + 1]) << 16) |
        (static_cast<uint32_t>(data[offset + 2]) << 8) |
        (static_cast<uint32_t>(data[offset + 3]) << 0);
    offset += 4;

    return msg;
}

std::vector<uint8_t> LOGGED_OUT::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write id
    buffer.push_back((id >> 24) & 0xFF);
    buffer.push_back((id >> 16) & 0xFF);
    buffer.push_back((id >> 8) & 0xFF);
    buffer.push_back((id >> 0) & 0xFF);

    return buffer;
}

LOGGED_OUT LOGGED_OUT::deserialize(const std::vector<uint8_t>& data) {
    LOGGED_OUT msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read id
    msg.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
        (static_cast<uint32_t>(data[offset + 1]) << 16) |
        (static_cast<uint32_t>(data[offset + 2]) << 8) |
        (static_cast<uint32_t>(data[offset + 3]) << 0);
    offset += 4;

    return msg;
}

std::vector<uint8_t> USERNAME_ALREADY_TAKEN::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

USERNAME_ALREADY_TAKEN USERNAME_ALREADY_TAKEN::deserialize(
    const std::vector<uint8_t>& data) {
    USERNAME_ALREADY_TAKEN msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> JOIN_LOBBY::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write lobby_code
    for (uint32_t i = 0; i < 6; ++i) {
        buffer.push_back(lobby_code[i]);
    }

    return buffer;
}

JOIN_LOBBY JOIN_LOBBY::deserialize(const std::vector<uint8_t>& data) {
    JOIN_LOBBY msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read lobby_code
    std::memcpy(msg.lobby_code, data.data() + offset, 6);
    offset += 6;

    return msg;
}

std::vector<uint8_t> LEAVE_LOBBY::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

LEAVE_LOBBY LEAVE_LOBBY::deserialize(const std::vector<uint8_t>& data) {
    LEAVE_LOBBY msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> CREATE_LOBBY::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

CREATE_LOBBY CREATE_LOBBY::deserialize(const std::vector<uint8_t>& data) {
    CREATE_LOBBY msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> LOBBY_CREATED::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write lobby_code
    for (uint32_t i = 0; i < 6; ++i) {
        buffer.push_back(lobby_code[i]);
    }

    return buffer;
}

LOBBY_CREATED LOBBY_CREATED::deserialize(const std::vector<uint8_t>& data) {
    LOBBY_CREATED msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read lobby_code
    std::memcpy(msg.lobby_code, data.data() + offset, 6);
    offset += 6;

    return msg;
}

std::vector<uint8_t> BAD_LOBBY_CODE::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

BAD_LOBBY_CODE BAD_LOBBY_CODE::deserialize(const std::vector<uint8_t>& data) {
    BAD_LOBBY_CODE msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> ADMIN_START_GAME::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

ADMIN_START_GAME ADMIN_START_GAME::deserialize(
    const std::vector<uint8_t>& data) {
    ADMIN_START_GAME msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> GAME_STARTING::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

GAME_STARTING GAME_STARTING::deserialize(const std::vector<uint8_t>& data) {
    GAME_STARTING msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> NOT_ADMIN::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

NOT_ADMIN NOT_ADMIN::deserialize(const std::vector<uint8_t>& data) {
    NOT_ADMIN msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> PLAYERS_LIST::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write players
    {
        uint32_t size = static_cast<uint32_t>(players.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : players) {
        buffer.push_back((elem.id >> 24) & 0xFF);
        buffer.push_back((elem.id >> 16) & 0xFF);
        buffer.push_back((elem.id >> 8) & 0xFF);
        buffer.push_back((elem.id >> 0) & 0xFF);
            for (uint32_t j = 0; j < 32; ++j) {
            buffer.push_back(elem.username[j]);
        }
    }

    return buffer;
}

PLAYERS_LIST PLAYERS_LIST::deserialize(const std::vector<uint8_t>& data) {
    PLAYERS_LIST msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read players
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.players.resize(size);
    }
    for (auto& elem : msg.players) {
        elem.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            std::memcpy(elem.username, data.data() + offset, 32);
        offset += 32;
    }

    return msg;
}

std::vector<uint8_t> LOBBY_DESTROYED::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

LOBBY_DESTROYED LOBBY_DESTROYED::deserialize(
    const std::vector<uint8_t>& data) {
    LOBBY_DESTROYED msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> GAME_END::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

GAME_END GAME_END::deserialize(const std::vector<uint8_t>& data) {
    GAME_END msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> CLIENT_INPUTS::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write input_count
    buffer.push_back((input_count >> 24) & 0xFF);
    buffer.push_back((input_count >> 16) & 0xFF);
    buffer.push_back((input_count >> 8) & 0xFF);
    buffer.push_back((input_count >> 0) & 0xFF);

    // Write inputs
    for (uint32_t i = 0; i < input_count && i < 102; ++i) {
        buffer.push_back(inputs[i]);
    }

    return buffer;
}

CLIENT_INPUTS CLIENT_INPUTS::deserialize(const std::vector<uint8_t>& data) {
    CLIENT_INPUTS msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read input_count
    msg.input_count = (static_cast<uint32_t>(data[offset + 0]) << 24) |
        (static_cast<uint32_t>(data[offset + 1]) << 16) |
        (static_cast<uint32_t>(data[offset + 2]) << 8) |
        (static_cast<uint32_t>(data[offset + 3]) << 0);
    offset += 4;

    // Read inputs
    for (uint32_t i = 0; i < msg.input_count && i < 102; ++i) {
        msg.inputs[i] = data[offset];
        offset += 1;
    }

    return msg;
}

std::vector<uint8_t> PLAYERS_STATES::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write players
    {
        uint32_t size = static_cast<uint32_t>(players.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : players) {
        buffer.push_back((elem.id >> 24) & 0xFF);
        buffer.push_back((elem.id >> 16) & 0xFF);
        buffer.push_back((elem.id >> 8) & 0xFF);
        buffer.push_back((elem.id >> 0) & 0xFF);
            {
            uint32_t temp;
            std::memcpy(&temp, &elem.x, sizeof(float));
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint32_t temp;
            std::memcpy(&temp, &elem.y, sizeof(float));
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint64_t temp;
            std::memcpy(&temp, &elem.health, sizeof(double));
            buffer.push_back((temp >> 56) & 0xFF);
            buffer.push_back((temp >> 48) & 0xFF);
            buffer.push_back((temp >> 40) & 0xFF);
            buffer.push_back((temp >> 32) & 0xFF);
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint64_t temp;
            std::memcpy(&temp, &elem.shield, sizeof(double));
            buffer.push_back((temp >> 56) & 0xFF);
            buffer.push_back((temp >> 48) & 0xFF);
            buffer.push_back((temp >> 40) & 0xFF);
            buffer.push_back((temp >> 32) & 0xFF);
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint64_t temp;
            std::memcpy(&temp, &elem.mana, sizeof(double));
            buffer.push_back((temp >> 56) & 0xFF);
            buffer.push_back((temp >> 48) & 0xFF);
            buffer.push_back((temp >> 40) & 0xFF);
            buffer.push_back((temp >> 32) & 0xFF);
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
    }

    return buffer;
}

PLAYERS_STATES PLAYERS_STATES::deserialize(const std::vector<uint8_t>& data) {
    PLAYERS_STATES msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read players
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.players.resize(size);
    }
    for (auto& elem : msg.players) {
        elem.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            {
            uint32_t temp;
            temp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
                (static_cast<uint32_t>(data[offset + 1]) << 16) |
                (static_cast<uint32_t>(data[offset + 2]) << 8) |
                (static_cast<uint32_t>(data[offset + 3]) << 0);
            offset += 4;
                    std::memcpy(&elem.x, &temp, sizeof(float));
        }
        {
            uint32_t temp;
            temp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
                (static_cast<uint32_t>(data[offset + 1]) << 16) |
                (static_cast<uint32_t>(data[offset + 2]) << 8) |
                (static_cast<uint32_t>(data[offset + 3]) << 0);
            offset += 4;
                    std::memcpy(&elem.y, &temp, sizeof(float));
        }
        {
            uint64_t temp;
            temp = (static_cast<uint64_t>(data[offset + 0]) << 56) |
                (static_cast<uint64_t>(data[offset + 1]) << 48) |
                (static_cast<uint64_t>(data[offset + 2]) << 40) |
                (static_cast<uint64_t>(data[offset + 3]) << 32) |
                (static_cast<uint64_t>(data[offset + 4]) << 24) |
                (static_cast<uint64_t>(data[offset + 5]) << 16) |
                (static_cast<uint64_t>(data[offset + 6]) << 8) |
                (static_cast<uint64_t>(data[offset + 7]) << 0);
            offset += 8;
                    std::memcpy(&elem.health, &temp, sizeof(double));
        }
        {
            uint64_t temp;
            temp = (static_cast<uint64_t>(data[offset + 0]) << 56) |
                (static_cast<uint64_t>(data[offset + 1]) << 48) |
                (static_cast<uint64_t>(data[offset + 2]) << 40) |
                (static_cast<uint64_t>(data[offset + 3]) << 32) |
                (static_cast<uint64_t>(data[offset + 4]) << 24) |
                (static_cast<uint64_t>(data[offset + 5]) << 16) |
                (static_cast<uint64_t>(data[offset + 6]) << 8) |
                (static_cast<uint64_t>(data[offset + 7]) << 0);
            offset += 8;
                    std::memcpy(&elem.shield, &temp, sizeof(double));
        }
        {
            uint64_t temp;
            temp = (static_cast<uint64_t>(data[offset + 0]) << 56) |
                (static_cast<uint64_t>(data[offset + 1]) << 48) |
                (static_cast<uint64_t>(data[offset + 2]) << 40) |
                (static_cast<uint64_t>(data[offset + 3]) << 32) |
                (static_cast<uint64_t>(data[offset + 4]) << 24) |
                (static_cast<uint64_t>(data[offset + 5]) << 16) |
                (static_cast<uint64_t>(data[offset + 6]) << 8) |
                (static_cast<uint64_t>(data[offset + 7]) << 0);
            offset += 8;
                    std::memcpy(&elem.mana, &temp, sizeof(double));
        }
    }

    return msg;
}

std::vector<uint8_t> PLAYERS_INFO::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write players
    {
        uint32_t size = static_cast<uint32_t>(players.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : players) {
        buffer.push_back((elem.id >> 24) & 0xFF);
        buffer.push_back((elem.id >> 16) & 0xFF);
        buffer.push_back((elem.id >> 8) & 0xFF);
        buffer.push_back((elem.id >> 0) & 0xFF);
            buffer.push_back(elem.weapon);
        buffer.push_back((elem.level >> 24) & 0xFF);
        buffer.push_back((elem.level >> 16) & 0xFF);
        buffer.push_back((elem.level >> 8) & 0xFF);
        buffer.push_back((elem.level >> 0) & 0xFF);
            buffer.push_back(elem.status);
    }

    return buffer;
}

PLAYERS_INFO PLAYERS_INFO::deserialize(const std::vector<uint8_t>& data) {
    PLAYERS_INFO msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read players
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.players.resize(size);
    }
    for (auto& elem : msg.players) {
        elem.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            elem.weapon = data[offset];
        offset += 1;
        elem.level = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            elem.status = data[offset];
        offset += 1;
    }

    return msg;
}

std::vector<uint8_t> PROJECTILES_POS::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write projectiles
    {
        uint32_t size = static_cast<uint32_t>(projectiles.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : projectiles) {
        buffer.push_back((elem.id >> 24) & 0xFF);
        buffer.push_back((elem.id >> 16) & 0xFF);
        buffer.push_back((elem.id >> 8) & 0xFF);
        buffer.push_back((elem.id >> 0) & 0xFF);
            buffer.push_back(elem.type);
        {
            uint32_t temp;
            std::memcpy(&temp, &elem.x, sizeof(float));
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint32_t temp;
            std::memcpy(&temp, &elem.y, sizeof(float));
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
    }

    return buffer;
}

PROJECTILES_POS PROJECTILES_POS::deserialize(
    const std::vector<uint8_t>& data) {
    PROJECTILES_POS msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read projectiles
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.projectiles.resize(size);
    }
    for (auto& elem : msg.projectiles) {
        elem.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            elem.type = data[offset];
        offset += 1;
        {
            uint32_t temp;
            temp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
                (static_cast<uint32_t>(data[offset + 1]) << 16) |
                (static_cast<uint32_t>(data[offset + 2]) << 8) |
                (static_cast<uint32_t>(data[offset + 3]) << 0);
            offset += 4;
                    std::memcpy(&elem.x, &temp, sizeof(float));
        }
        {
            uint32_t temp;
            temp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
                (static_cast<uint32_t>(data[offset + 1]) << 16) |
                (static_cast<uint32_t>(data[offset + 2]) << 8) |
                (static_cast<uint32_t>(data[offset + 3]) << 0);
            offset += 4;
                    std::memcpy(&elem.y, &temp, sizeof(float));
        }
    }

    return msg;
}

std::vector<uint8_t> NEW_WAVE::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write wave_id
    buffer.push_back((wave_id >> 24) & 0xFF);
    buffer.push_back((wave_id >> 16) & 0xFF);
    buffer.push_back((wave_id >> 8) & 0xFF);
    buffer.push_back((wave_id >> 0) & 0xFF);

    return buffer;
}

NEW_WAVE NEW_WAVE::deserialize(const std::vector<uint8_t>& data) {
    NEW_WAVE msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read wave_id
    msg.wave_id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
        (static_cast<uint32_t>(data[offset + 1]) << 16) |
        (static_cast<uint32_t>(data[offset + 2]) << 8) |
        (static_cast<uint32_t>(data[offset + 3]) << 0);
    offset += 4;

    return msg;
}

std::vector<uint8_t> ENEMIES_STATES::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write enemies
    {
        uint32_t size = static_cast<uint32_t>(enemies.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : enemies) {
        buffer.push_back((elem.id >> 24) & 0xFF);
        buffer.push_back((elem.id >> 16) & 0xFF);
        buffer.push_back((elem.id >> 8) & 0xFF);
        buffer.push_back((elem.id >> 0) & 0xFF);
            {
            uint32_t temp;
            std::memcpy(&temp, &elem.x, sizeof(float));
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint32_t temp;
            std::memcpy(&temp, &elem.y, sizeof(float));
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint64_t temp;
            std::memcpy(&temp, &elem.health, sizeof(double));
            buffer.push_back((temp >> 56) & 0xFF);
            buffer.push_back((temp >> 48) & 0xFF);
            buffer.push_back((temp >> 40) & 0xFF);
            buffer.push_back((temp >> 32) & 0xFF);
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint64_t temp;
            std::memcpy(&temp, &elem.shield, sizeof(double));
            buffer.push_back((temp >> 56) & 0xFF);
            buffer.push_back((temp >> 48) & 0xFF);
            buffer.push_back((temp >> 40) & 0xFF);
            buffer.push_back((temp >> 32) & 0xFF);
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
        {
            uint64_t temp;
            std::memcpy(&temp, &elem.mana, sizeof(double));
            buffer.push_back((temp >> 56) & 0xFF);
            buffer.push_back((temp >> 48) & 0xFF);
            buffer.push_back((temp >> 40) & 0xFF);
            buffer.push_back((temp >> 32) & 0xFF);
            buffer.push_back((temp >> 24) & 0xFF);
            buffer.push_back((temp >> 16) & 0xFF);
            buffer.push_back((temp >> 8) & 0xFF);
            buffer.push_back((temp >> 0) & 0xFF);
                }
    }

    return buffer;
}

ENEMIES_STATES ENEMIES_STATES::deserialize(const std::vector<uint8_t>& data) {
    ENEMIES_STATES msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read enemies
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.enemies.resize(size);
    }
    for (auto& elem : msg.enemies) {
        elem.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            {
            uint32_t temp;
            temp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
                (static_cast<uint32_t>(data[offset + 1]) << 16) |
                (static_cast<uint32_t>(data[offset + 2]) << 8) |
                (static_cast<uint32_t>(data[offset + 3]) << 0);
            offset += 4;
                    std::memcpy(&elem.x, &temp, sizeof(float));
        }
        {
            uint32_t temp;
            temp = (static_cast<uint32_t>(data[offset + 0]) << 24) |
                (static_cast<uint32_t>(data[offset + 1]) << 16) |
                (static_cast<uint32_t>(data[offset + 2]) << 8) |
                (static_cast<uint32_t>(data[offset + 3]) << 0);
            offset += 4;
                    std::memcpy(&elem.y, &temp, sizeof(float));
        }
        {
            uint64_t temp;
            temp = (static_cast<uint64_t>(data[offset + 0]) << 56) |
                (static_cast<uint64_t>(data[offset + 1]) << 48) |
                (static_cast<uint64_t>(data[offset + 2]) << 40) |
                (static_cast<uint64_t>(data[offset + 3]) << 32) |
                (static_cast<uint64_t>(data[offset + 4]) << 24) |
                (static_cast<uint64_t>(data[offset + 5]) << 16) |
                (static_cast<uint64_t>(data[offset + 6]) << 8) |
                (static_cast<uint64_t>(data[offset + 7]) << 0);
            offset += 8;
                    std::memcpy(&elem.health, &temp, sizeof(double));
        }
        {
            uint64_t temp;
            temp = (static_cast<uint64_t>(data[offset + 0]) << 56) |
                (static_cast<uint64_t>(data[offset + 1]) << 48) |
                (static_cast<uint64_t>(data[offset + 2]) << 40) |
                (static_cast<uint64_t>(data[offset + 3]) << 32) |
                (static_cast<uint64_t>(data[offset + 4]) << 24) |
                (static_cast<uint64_t>(data[offset + 5]) << 16) |
                (static_cast<uint64_t>(data[offset + 6]) << 8) |
                (static_cast<uint64_t>(data[offset + 7]) << 0);
            offset += 8;
                    std::memcpy(&elem.shield, &temp, sizeof(double));
        }
        {
            uint64_t temp;
            temp = (static_cast<uint64_t>(data[offset + 0]) << 56) |
                (static_cast<uint64_t>(data[offset + 1]) << 48) |
                (static_cast<uint64_t>(data[offset + 2]) << 40) |
                (static_cast<uint64_t>(data[offset + 3]) << 32) |
                (static_cast<uint64_t>(data[offset + 4]) << 24) |
                (static_cast<uint64_t>(data[offset + 5]) << 16) |
                (static_cast<uint64_t>(data[offset + 6]) << 8) |
                (static_cast<uint64_t>(data[offset + 7]) << 0);
            offset += 8;
                    std::memcpy(&elem.mana, &temp, sizeof(double));
        }
    }

    return msg;
}

std::vector<uint8_t> ENEMIES_INFO::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write enemies
    {
        uint32_t size = static_cast<uint32_t>(enemies.size());
        buffer.push_back((size >> 24) & 0xFF);
        buffer.push_back((size >> 16) & 0xFF);
        buffer.push_back((size >> 8) & 0xFF);
        buffer.push_back((size >> 0) & 0xFF);
        }
    for (const auto& elem : enemies) {
        buffer.push_back((elem.id >> 24) & 0xFF);
        buffer.push_back((elem.id >> 16) & 0xFF);
        buffer.push_back((elem.id >> 8) & 0xFF);
        buffer.push_back((elem.id >> 0) & 0xFF);
            buffer.push_back(elem.weapon);
        buffer.push_back((elem.level >> 24) & 0xFF);
        buffer.push_back((elem.level >> 16) & 0xFF);
        buffer.push_back((elem.level >> 8) & 0xFF);
        buffer.push_back((elem.level >> 0) & 0xFF);
            buffer.push_back(elem.status);
    }

    return buffer;
}

ENEMIES_INFO ENEMIES_INFO::deserialize(const std::vector<uint8_t>& data) {
    ENEMIES_INFO msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read enemies
    {
        uint32_t size;
        size = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            msg.enemies.resize(size);
    }
    for (auto& elem : msg.enemies) {
        elem.id = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            elem.weapon = data[offset];
        offset += 1;
        elem.level = (static_cast<uint32_t>(data[offset + 0]) << 24) |
            (static_cast<uint32_t>(data[offset + 1]) << 16) |
            (static_cast<uint32_t>(data[offset + 2]) << 8) |
            (static_cast<uint32_t>(data[offset + 3]) << 0);
        offset += 4;
            elem.status = data[offset];
        offset += 1;
    }

    return msg;
}

std::vector<uint8_t> GAME_DURATION::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write duration
    buffer.push_back((duration >> 24) & 0xFF);
    buffer.push_back((duration >> 16) & 0xFF);
    buffer.push_back((duration >> 8) & 0xFF);
    buffer.push_back((duration >> 0) & 0xFF);

    return buffer;
}

GAME_DURATION GAME_DURATION::deserialize(const std::vector<uint8_t>& data) {
    GAME_DURATION msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read duration
    msg.duration = (static_cast<uint32_t>(data[offset + 0]) << 24) |
        (static_cast<uint32_t>(data[offset + 1]) << 16) |
        (static_cast<uint32_t>(data[offset + 2]) << 8) |
        (static_cast<uint32_t>(data[offset + 3]) << 0);
    offset += 4;

    return msg;
}

std::vector<uint8_t> GAME_LEVEL::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    // Write level
    buffer.push_back((level >> 24) & 0xFF);
    buffer.push_back((level >> 16) & 0xFF);
    buffer.push_back((level >> 8) & 0xFF);
    buffer.push_back((level >> 0) & 0xFF);

    return buffer;
}

GAME_LEVEL GAME_LEVEL::deserialize(const std::vector<uint8_t>& data) {
    GAME_LEVEL msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    // Read level
    msg.level = (static_cast<uint32_t>(data[offset + 0]) << 24) |
        (static_cast<uint32_t>(data[offset + 1]) << 16) |
        (static_cast<uint32_t>(data[offset + 2]) << 8) |
        (static_cast<uint32_t>(data[offset + 3]) << 0);
    offset += 4;

    return msg;
}

std::vector<uint8_t> PLAYER_DEAD::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

PLAYER_DEAD PLAYER_DEAD::deserialize(const std::vector<uint8_t>& data) {
    PLAYER_DEAD msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> ADMIN_GAME_PAUSED::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

ADMIN_GAME_PAUSED ADMIN_GAME_PAUSED::deserialize(
    const std::vector<uint8_t>& data) {
    ADMIN_GAME_PAUSED msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

std::vector<uint8_t> ADMIN_PAUSE_GAME::serialize() const {
    std::vector<uint8_t> buffer;

    // Write message ID
    buffer.push_back((ID >> 24) & 0xFF);
    buffer.push_back((ID >> 16) & 0xFF);
    buffer.push_back((ID >> 8) & 0xFF);
    buffer.push_back((ID >> 0) & 0xFF);

    return buffer;
}

ADMIN_PAUSE_GAME ADMIN_PAUSE_GAME::deserialize(
    const std::vector<uint8_t>& data) {
    ADMIN_PAUSE_GAME msg;
    const std::vector<uint8_t>& actual_data = data;
    size_t offset = 0;

    // Skip message ID
    offset += 4;

    return msg;
}

}  // namespace net
