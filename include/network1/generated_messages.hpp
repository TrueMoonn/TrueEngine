#pragma once
#include <cstdint>
#include <vector>
#include <cstring>

#include <string>

namespace net {

// ===== Structs =====

struct CodeTimestamp {
    uint8_t code;
    uint32_t timestamp;
};

struct PlayerListEntry {
    uint32_t id;
    char username[32];
};

struct PlayerState {
    uint32_t id;
    float x;
    float y;
    double health;
    double shield;
    double mana;
};

struct PlayerInfo {
    uint32_t id;
    uint8_t weapon;
    uint32_t level;
    uint8_t status;
};

struct Projectile {
    uint32_t id;
    uint8_t type;
    float x;
    float y;
};

struct EnemyState {
    uint32_t id;
    float x;
    float y;
    double health;
    double shield;
    double mana;
};

struct EnemyInfo {
    uint32_t id;
    uint8_t weapon;
    uint32_t level;
    uint8_t status;
};

// ===== Messages =====

struct CONNECTED {
    static constexpr uint32_t ID = 1;

    std::vector<CodeTimestamp> entries;

    std::vector<uint8_t> serialize() const;
    static CONNECTED deserialize(const std::vector<uint8_t>& data);
};

struct DISCONNEXION {
    static constexpr uint32_t ID = 2;


    std::vector<uint8_t> serialize() const;
    static DISCONNEXION deserialize(const std::vector<uint8_t>& data);
};

struct ERROR_TOO_MANY_CLIENTS {
    static constexpr uint32_t ID = 3;


    std::vector<uint8_t> serialize() const;
    static ERROR_TOO_MANY_CLIENTS deserialize(const std::vector<uint8_t>& data);
};

struct PACKET_LOSS {
    static constexpr uint32_t ID = 4;

    uint8_t code;

    std::vector<uint8_t> serialize() const;
    static PACKET_LOSS deserialize(const std::vector<uint8_t>& data);
};

struct I_MISSED_SOMETHING {
    static constexpr uint32_t ID = 5;


    std::vector<uint8_t> serialize() const;
    static I_MISSED_SOMETHING deserialize(const std::vector<uint8_t>& data);
};

struct PING {
    static constexpr uint32_t ID = 6;


    std::vector<uint8_t> serialize() const;
    static PING deserialize(const std::vector<uint8_t>& data);
};

struct PONG {
    static constexpr uint32_t ID = 7;


    std::vector<uint8_t> serialize() const;
    static PONG deserialize(const std::vector<uint8_t>& data);
};

struct LOGIN {
    static constexpr uint32_t ID = 20;

    char username[256];

    std::vector<uint8_t> serialize() const;
    static LOGIN deserialize(const std::vector<uint8_t>& data);
};

struct LOGOUT {
    static constexpr uint32_t ID = 21;


    std::vector<uint8_t> serialize() const;
    static LOGOUT deserialize(const std::vector<uint8_t>& data);
};

struct LOGGED_IN {
    static constexpr uint32_t ID = 22;

    uint32_t id;

    std::vector<uint8_t> serialize() const;
    static LOGGED_IN deserialize(const std::vector<uint8_t>& data);
};

struct LOGGED_OUT {
    static constexpr uint32_t ID = 23;

    uint32_t id;

    std::vector<uint8_t> serialize() const;
    static LOGGED_OUT deserialize(const std::vector<uint8_t>& data);
};

struct USERNAME_ALREADY_TAKEN {
    static constexpr uint32_t ID = 25;


    std::vector<uint8_t> serialize() const;
    static USERNAME_ALREADY_TAKEN deserialize(const std::vector<uint8_t>& data);
};

struct JOIN_LOBBY {
    static constexpr uint32_t ID = 30;

    char lobby_code[6];

    std::vector<uint8_t> serialize() const;
    static JOIN_LOBBY deserialize(const std::vector<uint8_t>& data);
};

struct LEAVE_LOBBY {
    static constexpr uint32_t ID = 31;


    std::vector<uint8_t> serialize() const;
    static LEAVE_LOBBY deserialize(const std::vector<uint8_t>& data);
};

struct CREATE_LOBBY {
    static constexpr uint32_t ID = 32;


    std::vector<uint8_t> serialize() const;
    static CREATE_LOBBY deserialize(const std::vector<uint8_t>& data);
};

struct LOBBY_CREATED {
    static constexpr uint32_t ID = 33;

    char lobby_code[6];

    std::vector<uint8_t> serialize() const;
    static LOBBY_CREATED deserialize(const std::vector<uint8_t>& data);
};

struct BAD_LOBBY_CODE {
    static constexpr uint32_t ID = 34;


    std::vector<uint8_t> serialize() const;
    static BAD_LOBBY_CODE deserialize(const std::vector<uint8_t>& data);
};

struct ADMIN_START_GAME {
    static constexpr uint32_t ID = 35;


    std::vector<uint8_t> serialize() const;
    static ADMIN_START_GAME deserialize(const std::vector<uint8_t>& data);
};

struct GAME_STARTING {
    static constexpr uint32_t ID = 36;


    std::vector<uint8_t> serialize() const;
    static GAME_STARTING deserialize(const std::vector<uint8_t>& data);
};

struct NOT_ADMIN {
    static constexpr uint32_t ID = 37;


    std::vector<uint8_t> serialize() const;
    static NOT_ADMIN deserialize(const std::vector<uint8_t>& data);
};

struct PLAYERS_LIST {
    static constexpr uint32_t ID = 38;

    std::vector<PlayerListEntry> players;

    std::vector<uint8_t> serialize() const;
    static PLAYERS_LIST deserialize(const std::vector<uint8_t>& data);
};

struct LOBBY_DESTROYED {
    static constexpr uint32_t ID = 39;


    std::vector<uint8_t> serialize() const;
    static LOBBY_DESTROYED deserialize(const std::vector<uint8_t>& data);
};

struct GAME_END {
    static constexpr uint32_t ID = 49;


    std::vector<uint8_t> serialize() const;
    static GAME_END deserialize(const std::vector<uint8_t>& data);
};

struct CLIENT_INPUTS {
    static constexpr uint32_t ID = 50;

    uint32_t input_count;
    uint8_t inputs[102];

    std::vector<uint8_t> serialize() const;
    static CLIENT_INPUTS deserialize(const std::vector<uint8_t>& data);
};

struct PLAYERS_STATES {
    static constexpr uint32_t ID = 51;

    std::vector<PlayerState> players;

    std::vector<uint8_t> serialize() const;
    static PLAYERS_STATES deserialize(const std::vector<uint8_t>& data);
};

struct PLAYERS_INFO {
    static constexpr uint32_t ID = 52;

    std::vector<PlayerInfo> players;

    std::vector<uint8_t> serialize() const;
    static PLAYERS_INFO deserialize(const std::vector<uint8_t>& data);
};

struct PROJECTILES_POS {
    static constexpr uint32_t ID = 53;

    std::vector<Projectile> projectiles;

    std::vector<uint8_t> serialize() const;
    static PROJECTILES_POS deserialize(const std::vector<uint8_t>& data);
};

struct NEW_WAVE {
    static constexpr uint32_t ID = 54;

    uint32_t wave_id;

    std::vector<uint8_t> serialize() const;
    static NEW_WAVE deserialize(const std::vector<uint8_t>& data);
};

struct ENEMIES_STATES {
    static constexpr uint32_t ID = 55;

    std::vector<EnemyState> enemies;

    std::vector<uint8_t> serialize() const;
    static ENEMIES_STATES deserialize(const std::vector<uint8_t>& data);
};

struct ENEMIES_INFO {
    static constexpr uint32_t ID = 56;

    std::vector<EnemyInfo> enemies;

    std::vector<uint8_t> serialize() const;
    static ENEMIES_INFO deserialize(const std::vector<uint8_t>& data);
};

struct GAME_DURATION {
    static constexpr uint32_t ID = 57;

    uint32_t duration;

    std::vector<uint8_t> serialize() const;
    static GAME_DURATION deserialize(const std::vector<uint8_t>& data);
};

struct GAME_LEVEL {
    static constexpr uint32_t ID = 58;

    uint32_t level;

    std::vector<uint8_t> serialize() const;
    static GAME_LEVEL deserialize(const std::vector<uint8_t>& data);
};

struct PLAYER_DEAD {
    static constexpr uint32_t ID = 60;


    std::vector<uint8_t> serialize() const;
    static PLAYER_DEAD deserialize(const std::vector<uint8_t>& data);
};

struct ADMIN_GAME_PAUSED {
    static constexpr uint32_t ID = 61;


    std::vector<uint8_t> serialize() const;
    static ADMIN_GAME_PAUSED deserialize(const std::vector<uint8_t>& data);
};

struct ADMIN_PAUSE_GAME {
    static constexpr uint32_t ID = 68;


    std::vector<uint8_t> serialize() const;
    static ADMIN_PAUSE_GAME deserialize(const std::vector<uint8_t>& data);
};

}  // namespace net
