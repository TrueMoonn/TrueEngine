/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <utility>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Exception.hpp>
#include <ECS/DenseZipper.hpp>
#include <ECS/Registry.hpp>
#include <toml++/toml.hpp>
#include <events.hpp>

#include "physic/components/position.hpp"
#include "interaction/components/player.hpp"
#include "display/components/parallax.hpp"

#include "Sfml.hpp"
#include "sfml/components/sprite.hpp"
#include "sfml/components/window.hpp"
#include "sfml/factory.hpp"

namespace addon {
namespace sfml {

static int partition(std::vector<Sprite>& arr, int low, int high) {
    float pivot = arr[high].sp.getPosition().y;
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].sp.getPosition().y < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}


static void quickSortDraw(std::vector<Sprite>& arr, int low, int high) {
    if (low < high) {
        int piv = partition(arr, low, high);
        quickSortDraw(arr, low, piv - 1);
        quickSortDraw(arr, piv + 1, high);
    }
}

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

    //     for (auto && [win] : ECS::DenseZipper(window)) {
    //         for (auto&& [id, spr] : ECS::IndexedDenseZipper(sprite)) {
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
            auto s_origin = params["origin"].as_array();
            sf::Vector2f origin = s_origin ?
                sf::Vector2f{s_origin->at(0).value_or(0.0f),
                s_origin->at(0).value_or(0.0f)} : sf::Vector2f{0.f, 0.f};
            const auto &t_size = params["size"].as_array();
            sf::Vector2i size = t_size ?
                sf::Vector2i(t_size->at(0).value_or(1),
                t_size->at(1).value_or(1)) : sf::Vector2i(texture.getSize());
            auto t_scale = params["scale"].as_array();
            sf::Vector2f scale = t_scale ?
                sf::Vector2f{t_scale->at(0).value_or(1.0f) / size.x,
                t_scale->at(1).value_or(1.0f) / size.y} : sf::Vector2f{1, 1};
            reg.createComponent<Sprite>(e, texture,
                layer, size, scale, origin);
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Sprite): key not found" << std::endl;
        } catch (const sf::Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };
    _systems["display"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            auto& windows = reg.getComponents<Window>();
            for (auto &&[win] : ECS::DenseZipper(windows)) {
                for (std::size_t lay = 0; lay < win.draws.size(); ++lay) {
                    quickSortDraw(win.draws[lay],
                        0, win.draws[lay].size() - 1);
                    for (auto& sprite : win.draws[lay])
                        win.win->draw(sprite.sp);
                    win.draws[lay].clear();
                }
                win.win->display();
                win.win->clear();
            }
        });
    };
    _systems["poll_event"] = [&sig](ECS::Registry& reg) {
        reg.addSystem([&sig](ECS::Registry& reg) {
            auto& windows = reg.getComponents<Window>();
            static te::Keys keys = {false};
            static te::Mouse mouse;

            for (auto&& [win] : ECS::DenseZipper(windows)) {
                while (std::optional<sf::Event> ev = win.win->pollEvent()) {
                    if (ev->is<sf::Event::KeyPressed>()) {
                        keys[static_cast<te::Key>(
                            ev->getIf<sf::Event::KeyPressed>()->
                            code)] = true;
                    }
                    if (ev->is<sf::Event::KeyReleased>()) {
                        keys[static_cast<te::Key>(
                            ev->getIf<sf::Event::KeyReleased>()->
                            code)] = false;
                    }
                    if (ev->is<sf::Event::MouseButtonPressed>()) {
                        const auto& temp = ev->getIf<
                            sf::Event::MouseButtonPressed>();
                        mouse.type[static_cast<
                            te::MouseEvent>(temp->button)] = true;
                    }
                    if (ev->is<sf::Event::MouseButtonReleased>()) {
                        const auto& temp = ev->getIf<
                            sf::Event::MouseButtonReleased>();
                        mouse.type[static_cast<
                            te::MouseEvent>(temp->button)] = false;
                    }
                    mouse.position.x = sf::Mouse::getPosition(*win.win).x;
                    mouse.position.y = sf::Mouse::getPosition(*win.win).y;
                    if (ev->is<sf::Event::Closed>()) {
                        win.win->close();
                        sig.emit("closed");
                    }
                }
                sig.emit("key_input", keys);
                sig.emit("mouse_input", mouse);
            }
        });
    };
    _systems["draw"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            auto& sprites = reg.getComponents<Sprite>();
            auto& drawables = reg.getComponents<Drawable>();
            auto& positions = reg.getComponents<physic::Position2>();
            auto& windows = reg.getComponents<Window>();

            for (auto &&[win] : ECS::DenseZipper(windows)) {
                for (auto &&[sprite, pos, drawable] :
                    ECS::DenseZipper(sprites, positions, drawables)) {
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

            for (auto &&[win] : ECS::DenseZipper(windows)) {
                for (auto &&[pos, player] :
                    ECS::DenseZipper(positions, players)) {
                    win.win->setView(sf::View({pos.x, pos.y},
                        static_cast<sf::Vector2f>(win.win->getSize())));
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

            for (auto&& [win] : ECS::DenseZipper(windows)) {
                for (auto&& [para, sp, draw, pos] :
                    ECS::DenseZipper(
                        parallaxs, sprites, drawables, positions)) {
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
