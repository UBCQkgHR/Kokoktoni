#ifndef GAME_H
#define GAME_H
#include <SFML/Window/Keyboard.hpp>
#include <type_traits>
#include <vector>

#include "../include/Enemy.hpp"
#include "../include/Player.h"
#include "./Level.h"

void drawHitbox(sf::RenderWindow &window, const sf::Sprite &sprite,
                sf::Color color = sf::Color::Red);

class Game {
   public:
    Game();
    ~Game();

    template <typename T>
    void checkCollisionX(T &obj, const Level &level) {
        const int TILE = 32;
        auto bounds = obj.getBounds();
        auto &velocity = obj.getVelocity();
        //  sf::FloatRect bounds = obj.sprite.getGlobalBounds();

        int topTile =
            (int)(bounds.top / TILE);  // координата по Y(  верхний левый угол)
        int bottomTile = (int)((bounds.top + bounds.height - 1) /
                               TILE);  // координата нижне точки по левому краю(
                                       // левый нижний угол )
        if (velocity.x > 0) {
            int rightTile = (int)((bounds.left + bounds.width) /
                                  TILE);  // верхний правый угол
            for (int y = topTile; y <= bottomTile; ++y) {
                int index = y * level.x_size + rightTile;
                if (level.mapColisium[index] == 1) {
                    obj.setPosition(rightTile * TILE - bounds.width,
                                    bounds.top);
                    velocity.x = -velocity.x;
                    break;
                }
            }
        } else if (velocity.x < 0) {
            int leftTile = (int)(bounds.left / TILE);  // координата по Х

            for (int y = topTile; y <= bottomTile; ++y) {
                int index = y * level.x_size + leftTile;
                if (level.mapColisium[index] == 1) {
                    obj.setPosition((leftTile + 1) * TILE, bounds.top);
                    velocity.x = -velocity.x;
                    break;
                }
            }
        }
    }

    template <typename T>
    void checkCollisionY(T &obj, const Level &level) {
        const int TILE = 32;
        auto bounds = obj.getBounds();
        auto &velocity = obj.getVelocity();
        //   sf::FloatRect bounds = obj.sprite.getGlobalBounds();
        int leftTile = (int)(bounds.left / TILE);
        int rightTile = (int)((bounds.left + bounds.width - 1) / TILE);

        if (velocity.y > 0) {
            int bottomTile =
                static_cast<int>((bounds.top + bounds.height) / TILE);
            for (int x = leftTile; x <= rightTile; ++x) {
                int index = bottomTile * level.x_size + x;
                if (level.mapColisium[index] == 1) {
                    obj.setPosition(bounds.left,
                                    bottomTile * TILE - bounds.height);
                    if constexpr (std::is_same_v<T, Player>) {
                        obj.setIsJump(false);
                    }
                    velocity.y = 0;
                    break;
                }
            }
        } else if (velocity.y < 0) {
            int topTile = static_cast<int>(bounds.top / TILE);
            for (int x = leftTile; x <= rightTile; ++x) {
                int index = topTile * level.x_size + x;
                if (level.mapColisium[index] == 1) {
                    obj.setPosition(bounds.left, (topTile + 1) * TILE);
                    velocity.y = 0;
                    break;
                }
            }
        }
    }

    template <typename T>
    void checkCollisionWithEnemies(T &player,
                                   std::vector<std::unique_ptr<Enemy>> &enemies,
                                   float deltaTime) {
        for (auto &enemy : enemies) {
            if (player.getBounds().intersects(enemy->getBounds())) {
                if (player.getVelocity().y > 0 &&
                    player.getBounds().top + player.getBounds().height -
                            enemy->getBounds().top <
                        30.f) {
                    enemy->takeDamage();
                    player.getVelocity().y = -200.f;
                    player.setIsJump(true);
                } else if (!player.getIsInvicible()) {
                    player.takeDamage(1);
                    if (player.getBounds().left < enemy->getBounds().left) {
                        player.setPosition(
                            enemy->getBounds().left - player.getBounds().width,
                            player.getBounds().top);
                        player.getVelocity().x = -150.f;
                    } else {
                        player.setPosition(
                            enemy->getBounds().left + enemy->getBounds().width,
                            player.getBounds().top);
                        player.getVelocity().y = -150.f;
                    }
                    player.getVelocity().y = -150.f;
                    player.setIsJump(true);
                }
                break;
            }
        }
    }
};
#endif
