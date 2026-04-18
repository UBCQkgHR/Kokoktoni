#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "../include/Enemy.hpp"
#include "../include/Game.h"
#include "../include/Item.hpp"
#include "../include/Level.h"
#include "../include/Player.h"
#include "../include/Score.h"
#include "../include/json.hpp"
int main() {
    std::cout << "star" << std::endl;
    // Создаём окно
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Kokotoni Wilf");
    window.setFramerateLimit(60);
    Game game;
    Player player;
    Level level;
    level.loadmap();
    sf::Clock clock;
    Score scorePlayer("../arialmt.ttf");
    scorePlayer.healthText.setFont(scorePlayer.font);
    scorePlayer.healthText.setCharacterSize(24);
    scorePlayer.healthText.setPosition(10.f, 40.f);
    scorePlayer.healthText.setString("❤️ 3/3");
    scorePlayer.setHealString(3, 3);
    std::vector<std::unique_ptr<Enemy>> enemies;
    auto enemy1 = std::make_unique<Enemy>();
    auto enemy2 = std::make_unique<Enemy>();

    enemy1->setPosition(400.f, 500.f);
    enemy1->setSpeed(100);
    enemies.push_back(std::move(enemy1));

    enemy2->setPosition(400.f, 400.f);
    enemy2->setSpeed(100);
    enemies.push_back(std::move(enemy2));

    while (window.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Закрытие окна
            }
        }

        for (auto &item : level.items) {
            if (!item->collect && player.sprite.getGlobalBounds().intersects(
                                      item->getSprite().getGlobalBounds())) {
                item->collect = true;
                player.score++;
                scorePlayer.SetString(player.score);
            }
        }

        window.clear();  // Очищаем экран
        for (auto &item : level.items) {  // перебираем все объекты в векторе
                                          // Item для отрисовки
            item->draw(window);
        }

        for (const auto &platform : level.platforms) {
            window.draw(platform);
        }

        //  window.draw(items[0]->Sprite);
        for (auto &enemy : enemies) {
            if (enemy->isAlive()) {
                enemy->moveX(dt);
                enemy->moveY(dt);
                enemy->updateAnimation(dt);
                enemy->update(dt);
                game.checkCollisionX(*enemy, level);
                game.checkCollisionY(*enemy, level);
            }
        }

        game.checkCollisionWithEnemies(player, enemies, deltaTime.asSeconds());
        player.updateInvincibility(deltaTime.asSeconds());

        for (auto &enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->sprite);
                drawHitbox(window, enemy->sprite, sf::Color::Green);
            }
        }
        // enemy.update(deltaTime.asMicroseconds());  // обновление Враw
        // enemy2.update();  // обновление Враw
        player.moveX(deltaTime.asSeconds());
        // enemy.moveX(deltaTime.asSeconds());
        // enemy2.moveX(deltaTime.asSeconds());
        // game.checkCollisionX(enemy, level);
        game.checkCollisionX(player, level);
        // game.checkCollisionX(enemy2, level);

        player.updateAnimation(deltaTime.asSeconds());  // анимация  игрока
        // enemy.updateAnimation(deltaTime.asSeconds());  // анимация Врага.
        // enemy2.updateAnimation(deltaTime.asSeconds());  // анимация Врага.
        /* for (auto &platform : level.platforms_collision) {
             player.resolveCollisionX(player.sprite, platform);
             enemy.resolveCollisionX(enemy.sprite, platform);
             enemy2.resolveCollisionX(enemy2.sprite, platform);
         }
    */
        player.moveY(deltaTime.asSeconds());  // передвигаем игрока
        //       player.checkCollisionY(level);
        // enemy.moveY(deltaTime.asSeconds());
        // enemy2.moveY(deltaTime.asSeconds());
        // game.checkCollisionY(enemy, level);
        game.checkCollisionY(player, level);
        // game.checkCollisionY(enemy2, level);
        /*       for (auto &platform : level.platforms_collision) {
               for (auto &platform : level.platforms_collision) {
                   player.resolveCollisionY(player.sprite, platform);
                   enemy.resolveCollisionY(enemy.sprite, platform);
                   enemy2.resolveCollisionY(enemy2.sprite, platform);
               }
       */
        // window.draw(enemy.sprite);
        // window.draw(enemy2.sprite);
        window.draw(player.sprite);          // Рисуем игрока//
        window.draw(scorePlayer.scoreText);  // рисуем счет

        drawHitbox(window, player.sprite, sf::Color::Red);
        // drawHitbox(window, enemy.sprite, sf::Color::Green);

        // drawHitbox(window, enemy2.sprite, sf::Color::Green);
        window.draw(scorePlayer.healthText);  // рисуем здоровье
        window.display();  // Отображаем всё на экране
                           //        std::cout << 1000000.0f /
                           //        clock.getElapsedTime().asMicroseconds()
                           //                << '\n';
                           // clock.restart();
    }

    return 0;
}
