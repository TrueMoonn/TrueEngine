/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <unordered_map>
#include <string>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Exception.hpp>
#include <ECS/Zipper.hpp>
#include <ECS/Registry.hpp>
#include <toml++/toml.hpp>

#include "physic/components/position.hpp"
#include "interaction/components/player.hpp"
#include "display/components/parallax.hpp"

#include "Sfml.hpp"
#include "sfml/components/window.hpp"
#include "sfml/factory.hpp"

namespace addon {
namespace sfml {

Sfml::Sfml(ECS::Registry& reg, te::SignalManager& sig)
    : te::plugin::APlugin(reg, sig) {
    reg.registerComponent<Window>();
    _components["window"] = [](ECS::Registry& reg,
        const ECS::Entity& e, const toml::table& params) {
        if (!params.empty()) {
            const auto& wName = params["name"].value_or(DEFAULT_WIN_NAME);
            const auto& size = params["size"].as_array();
            mat::Vector2u sizeVect;
            sizeVect.x = size->at(0).value_or(1280);
            sizeVect.y = size->at(1).value_or(720);
            const auto& fps =
                params["framelimit"].value_or(DEFAULT_FRAME_LIMIT);
            reg.createComponent<Window>(e, wName, sizeVect, fps);
        } else  {
            reg.createComponent<Window>(e);
        }
    };
    reg.registerComponent<Drawable>();
    _components["drawable"] = [](ECS::Registry& reg,
        const ECS::Entity& e, const toml::table&) {
        reg.createComponent<Drawable>(e);
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
    // events.addSubscription(te::event::System::MouseButtonPressed,
    //     [&events](ECS::Registry& reg,
    //     const te::SignalManager::eventContent& content,
    //     std::optional<ECS::Entity> e){
    //     auto &window = reg.getComponents<Window>();
    //     auto &sprite = reg.getComponents<Sprite>();
    //     auto& event = std::get<te::event::MouseEvent>(content);
    //     int i = 0;

    //     for (auto && [win] : ECS::Zipper(window)) {
    //         for (auto&& [id, spr] : ECS::IndexedZipper(sprite)) {
    //             if (event._MouseKey.at(te::event::MouseButton::MouseLeft)
    //             .active) {
    //                 const auto &pos = sf::Mouse::getPosition(win);
    //                 const auto &translated = win.mapPixelToCoords(pos);

    //                 if (spr.sp.getGlobalBounds().contains(translated)) {
    //                     if (i == 1) {
    //                         if (id == MENU_BEGIN)
    //                             events.setSystemEvent(
    //                                 te::event::System::ChangeScene, true);
    //                         if (id == (MENU_BEGIN + 1))
    //                             events.setSystemEvent(
    //                                 te::event::System::Closed, true);
    //                     }
    //                     i++;
    //                 }
    //             }
    //         }
    //     }
    // });
    reg.registerComponent<Sprite>();
    _components["sprite"] = [](ECS::Registry& reg,
        const ECS::Entity& e, const toml::table& params) {
        static std::unordered_map<std::string, sf::Texture> textures;
        try {
            const auto& path = params["path"].value_or("");
            auto [it, inserted] = textures.try_emplace(path);
            if (inserted)
                (void)it->second.loadFromFile(path);
            auto& texture = it->second;
            const auto &layer = params["layer"].value_or(0);
            const auto &t_size = params["size"].as_array();
            sf::Vector2i size = t_size ?
                sf::Vector2i(t_size->at(0).value_or(1),
                t_size->at(1).value_or(1)) : sf::Vector2i(texture.getSize());
            auto t_scale = params["scale"].as_array();
            sf::Vector2f scale = t_scale ?
                sf::Vector2f{t_scale->at(0).value_or(1.0f) / size.x,
                t_scale->at(1).value_or(1.0f) / size.y} : sf::Vector2f{1, 1};
            reg.createComponent<Sprite>(e, texture,
                layer, size, scale);
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Sprite): key not found" << std::endl;
        } catch (const sf::Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };
    _systems["display"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            auto& windows = reg.getComponents<Window>();
            for (auto &&[win] : ECS::Zipper(windows)) {
                for (std::size_t i = 0; i < win.draws.size(); ++i) {
                    for (auto& sprite : win.draws[i])
                        win.draw(sprite.sp);
                    win.draws[i].clear();
                }
                win.display();
                win.clear();
            }
        });
    };
    _systems["poll_event"] = [&sig](ECS::Registry& reg) {
        reg.addSystem([&sig](ECS::Registry& reg) {
            auto& windows = reg.getComponents<Window>();

            for (auto&& [win] : ECS::Zipper(windows)) {
                while (std::optional<sf::Event> pevent = win.pollEvent()) {
                    if (pevent->is<sf::Event::Closed>())
                        sig.emit("closed");
                }
            }
        });
    };
    _systems["draw"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            auto& sprites = reg.getComponents<Sprite>();
            auto& drawables = reg.getComponents<Drawable>();
            auto& positions = reg.getComponents<physic::Position2>();
            auto& windows = reg.getComponents<Window>();

            for (auto &&[win] : ECS::Zipper(windows)) {
                for (auto &&[sprite, pos, drawable] :
                    ECS::Zipper(sprites, positions, drawables)) {
                    sprite.sp.setPosition({pos.x, pos.y});
                    win.push_back(sprite);
                }
            }
        });
    };
    _systems["follow_player"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            auto& players = reg.getComponents<intact::Player>();
            auto& positions = reg.getComponents<physic::Position2>();
            auto& windows = reg.getComponents<Window>();

            for (auto &&[win] : ECS::Zipper(windows)) {
                for (auto &&[pos, player] : ECS::Zipper(positions, players)) {
                    win.setView(sf::View({pos.x, pos.y},
                        static_cast<sf::Vector2f>(win.getSize())));
                }
            }
        });
    };
    _systems["parallax_sys"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg){
            auto& windows = reg.getComponents<Window>();
            auto& parallaxs = reg.getComponents<display::Parallax>();
            auto& sprites = reg.getComponents<Sprite>();
            auto& drawables = reg.getComponents<Drawable>();
            auto& positions = reg.getComponents<physic::Position2>();

            for (auto&& [win] : ECS::Zipper(windows)) {
                for (auto&& [para, sp, draw, pos] :
                    ECS::Zipper(parallaxs, sprites, drawables, positions)) {
                    auto size = sp.sp.getTextureRect().size;
                    size.x *= sp.sp.getScale().x;
                    size.y *= sp.sp.getScale().y;
                    if (para.reset.x > pos.x + size.x) {
                        pos.x = para.reset.x;
                    }
                    for (std::size_t i = 0; i < para.iterations; ++i) {
                        sp.sp.setPosition({pos.x + size.x * i, pos.y});
                        win.push_back(sp);
                    }
                }
            }
        });
    };
}

}  // namespace sfml
}  // namespace addon
