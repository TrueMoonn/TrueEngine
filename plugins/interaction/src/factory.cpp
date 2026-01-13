/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <toml++/toml.hpp>

#include <ECS/DenseZipper.hpp>
#include <events.hpp>
#include <maths/Vector.hpp>
#include <physic/components/position.hpp>
#include <physic/components/hitbox.hpp>
#include <sfml/components/window.hpp>

#include "Interaction.hpp"
#include "interaction/components/hoverable.hpp"
#include "interaction/factory.hpp"

namespace addon {
namespace intact {

Interaction::Interaction(ECS::Registry& reg, te::SignalManager& sig)
    : te::plugin::APlugin(reg, sig) {
    reg.registerComponent<Player>();
    _components["player"] = [](ECS::Registry& reg,
        const ECS::Entity& e, const toml::table&) {
        reg.createComponent<Player>(e);
    };
    reg.registerComponent<Clickable>();
    _components["clickable"] = [](ECS::Registry& reg,
        const ECS::Entity& e, const toml::table&) {
        reg.createComponent<Clickable>(e);
    };
    reg.registerComponent<Hoverable>();
    _components["hoverable"] = [](ECS::Registry& reg,
        const ECS::Entity& e, const toml::table&) {
        reg.createComponent<Hoverable>(e);
    };
    sig.sub<te::Mouse>("mouse_input", [&reg, &sig](te::Mouse mouse) {
        auto& poss = reg.getComponents<physic::Position2>();
        auto& hits = reg.getComponents<physic::Hitbox>();
        auto& hovers = reg.getComponents<Hoverable>();
        auto& clicks = reg.getComponents<Clickable>();
        auto& wins = reg.getComponents<sfml::Window>();

        for (auto&& [win] : ECS::DenseZipper(wins)) {
            const auto& view = win.win->getView();
            mat::Vector2i mpos(
                mouse.position.x + view.getCenter().x - view.getSize().x / 2,
                mouse.position.y + view.getCenter().y - view.getSize().y / 2);
            for (auto&& [e, hit, pos, hover] :
                ECS::IndexedDenseZipper(hits, poss, hovers)) {
                mat::Vector2f hpos = pos + hit.position;
                if (mpos.x > hpos.x && mpos.x < hpos.x + hit.size.x &&
                mpos.y > hpos.y && mpos.y < hpos.y + hit.size.y) {
                    sig.emit("hovered", e);
                    hover.hovered = true;
                } else {
                    hover.hovered = false;
                }
            }
            for (auto&& [e, hit, pos, click] :
                ECS::IndexedDenseZipper(hits, poss, clicks)) {
                mat::Vector2f hpos = pos + hit.position;
                if ((mouse.type[te::MouseEvent::MouseLeft] ||
                    mouse.type[te::MouseEvent::MouseRight]) &&
                    mpos.x > hpos.x && mpos.x < hpos.x + hit.size.x &&
                    mpos.y > hpos.y && mpos.y < hpos.y + hit.size.y) {
                    sig.emit("clicked", e);
                    click.clicked = true;
                } else {
                    click.clicked = false;
                }
            }
        }
    });
}

}  // namespace intact
}  // namespace addon
