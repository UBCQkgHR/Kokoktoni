#include "../include/Enemy.hpp"
#include "../include/Item.hpp"
#include "../include/Level.h"
#include "../include/Player.h"
#include "../include/Score.h"
#include "../include/json.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <iostream>
#include <vector>
int main() {
  std::cout << "star" << std::endl;
  // Создаём окно
  sf::RenderWindow window(sf::VideoMode(1024, 768), "Kokotoni Wilf");
  Enemy enemy;
  Player player;
  Level level;
  level.loadmap();
  sf::Clock clock;
  Score scorePlayer("../arialmt.ttf");

  while (window.isOpen()) {
    sf::Event event;
    sf::Time deltaTime = clock.restart();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close(); // Закрытие окна
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

    window.clear(); // Очищаем экран
    for (auto &item :
         level.items) { // перебираем все объекты в векторе Item для отрисовки
      item->draw(window);
    }

    for (const auto &platform : level.platforms) {
      window.draw(platform);
    }

    //  window.draw(items[0]->Sprite);

    player.moveX(deltaTime.asSeconds());
    enemy.moveX(deltaTime.asSeconds());
    player.updateAnimation(deltaTime.asSeconds()); // передвигаем игрока
    for (auto &platform : level.platforms_collision) {
      player.resolveCollisionX(player.sprite, platform);
      enemy.resolveCollisionX(enemy.sprite, platform);
    }

    player.moveY(deltaTime.asSeconds()); // передвигаем игрока
    enemy.moveY(deltaTime.asSeconds());
    for (auto &platform : level.platforms_collision) {
      player.resolveCollisionY(player.sprite, platform);
      enemy.resolveCollisionY(enemy.sprite, platform);
    }

    window.draw(enemy.sprite);
    window.draw(player.sprite);         // Рисуем игрока//
    window.draw(scorePlayer.scoreText); // рисуем счет

    window.display(); // Отображаем всё на экране
  }

  return 0;
}
