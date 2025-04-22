#include "../include/Item.hpp"
#include "../include/Player.h"
#include "../include/Score.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
int main() {
  // Создаём окно
  sf::RenderWindow window(sf::VideoMode(800, 600), "Kokotoni Wilf");

  std::vector<sf::RectangleShape> platforms;

  sf::RectangleShape floor(sf::Vector2f(800.f, 40.f));
  floor.setPosition(0.f, 560.f);
  floor.setFillColor(sf::Color(100, 60, 30));
  platforms.push_back(floor);

  sf::RectangleShape p1(sf::Vector2f(800.f, 40.f));
  p1.setPosition(200.f, 450.f);
  p1.setFillColor(sf::Color(120, 30, 59));
  platforms.push_back(p1);

  sf::RectangleShape p2(sf::Vector2f(800.f, 40.f));
  p2.setPosition(300.f, 150.f);
  p2.setFillColor(sf::Color(120, 30, 59));
  platforms.push_back(p2);

  std::vector<std::unique_ptr<Item>> items; // Создаём вектор указателей на Item
  items.emplace_back(std::make_unique<Item>(
      300.f, 300.f)); // Создаём объект без копирования прямо в векторе
  items.emplace_back(std::make_unique<Item>(500.f, 300.f));
  items.emplace_back(std::make_unique<Item>(600.f, 300.f));

  Player player;
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
    player.move(deltaTime.asSeconds(), platforms); // передвигаем игрока

    for (auto &item : items) {
      if (!item->collect && player.sprite.getGlobalBounds().intersects(
                                item->getSprite().getGlobalBounds())) {
        item->collect = true;
        player.score++;
        scorePlayer.SetString(player.score);
      }
    }

    window.clear(); // Очищаем экран
    for (auto &item :
         items) { // перебираем все объекты в векторе Item для отрисовки
      item->draw(window);
    }

    for (const auto &platform : platforms) {
      window.draw(platform);
    }

    window.draw(items[0]->Sprite);

    window.draw(player.sprite);         // Рисуем игрока//
    window.draw(scorePlayer.scoreText); // рисуем счет

    window.display(); // Отображаем всё на экране
  }

  return 0;
}
