/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

    #include <unordered_map>
    #include <functional>
    #include <variant>
    #include <vector>
    #include <optional>

    #include <ECS/Registry.hpp>

    #include "event/events.hpp"

    #define POLL_EVENT_ENDPOINT "pollEvent"

namespace te {
namespace event {

class EventManager {
 public:
    typedef void(*pollFunc)(Events&, ECS::Registry&);
    typedef std::variant<KeysEvent, MouseEvent, bool> eventContent;
    typedef std::function<void(ECS::Registry&, const eventContent&,
        std::optional<ECS::Entity>)> eventFunc;

 public:
    explicit EventManager();
    explicit EventManager(pollFunc func);
    ~EventManager() = default;

    void setPollFunc(pollFunc func);
    void pollEvents(ECS::Registry& reg);

    eventContent getEventContent(System system) const;
    Events getEvents(void) const;

    bool isEvent(System sys) const;
    void setSystemEvent(System sys, bool val);

    void addSubscription(System sys, eventFunc func);
    void emit(ECS::Registry& reg,
        std::optional<ECS::Entity> target_entity = std::nullopt);

 private:
    pollFunc _pollFunc;

    Events _events;

    void fillSubscriptions(void);
    std::unordered_map<System, std::vector<eventFunc>> _subscription;
};

}  // namespace event
}  // namespace te
