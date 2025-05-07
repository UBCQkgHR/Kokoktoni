#include "../include/Item.hpp"
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
  /*
        int blocks[32][32] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
             0, 1, 0, 0, 0, 1, 2, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
             0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0,
             0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 1, 1, 1, 1,
             1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
             0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
             0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
             0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1,
             0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
             1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
             1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 2, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0,
             0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };*/
  std::vector<sf::RectangleShape> platforms;

  std::vector<std::unique_ptr<Item>> items; // Создаём вектор указателей на Item

  sf::Texture blockTexture;
  if (!(blockTexture.loadFromFile("../goodly-2x.png"))) {
    printf("%s", "Don`t load texture trava!");
  }

  sf::RectangleShape block(sf::Vector2f(32.f, 32.f));
  block.setTexture(&blockTexture);
  block.setTextureRect(sf::IntRect(0, 0, 32, 32));

  using json = nlohmann::json;
  json levelData;
  std::ifstream file("../map/test1.json");
  std::cout << " file json is open" << std::endl;
  std::vector<int> map;
  if (!file.is_open()) {
    std::cout << " File do not open" << std::endl;
  } else {
    file >> levelData;
  }

  std::cout << " File  is open" << std::endl;
  // int tileSize = levelData["tileheight"];
  /*if (levelData.contains("data") && levelData.is_array()) {
    auto &layer = levelData["layers"][0];
    std::cout << " массив layer загружен " << std::endl;
    if (layer.contains("data") && layer["data"].is_array()) {
      map = layer["data"].get<std::vector<int>>();
      std::cout << " массив data загрузен в map" << std::endl;
    } else {
      printf("%s", "поле 'data' не найдено или не массив\n");
    }
  } else {
    printf("%s", "поле 'layer' не найдено или не массив\n");
  }
  int y_size = levelData["height"];
  int x_size = levelData["width"];
  if (map.size() != static_cast<size_t>(y_size * x_size)) {
    std::cout << "Ошибка: размер данных 'map' не соответствует заданным "
                 "размерам уровня!"
              << std::endl;
    return -1; // Завершаем программу
  }
  for (int y = 0; y < y_size; ++y) {
    for (int x = 0; x < x_size; ++x) {
      int maptit = map[y * x_size + x];
      if (maptit == 34) {
        block.setPosition(32.f * x, 32.f * y);
        block.setFillColor(sf::Color(100, 100, 100));
        platforms.push_back(block);
      }
    }
  }
  */
  // Проверка наличия и загрузки данных из JSON
  if (levelData.contains("layers") && levelData["layers"].is_array() &&
      !levelData["layers"].empty()) {
    auto &layer = levelData["layers"][0];
    std::cout << "Массив 'layer' загружен" << std::endl;

    if (layer.contains("data") && layer["data"].is_array()) {
      map = layer["data"].get<std::vector<int>>();
      std::cout << "Массив 'data' загружен в map" << std::endl;
    } else {
      std::cout << "Поле 'data' не найдено или не массив" << std::endl;
      return -1; // Завершаем программу, так как данные некорректны
    }
  } else {
    std::cout << "Поле 'layers' не найдено или не массив" << std::endl;
    return -1; // Завершаем программу, так как данные некорректны
  }

  // Получаем размеры карты
  int y_size =
      levelData.contains("height") ? levelData["height"].get<int>() : 0;
  int x_size = levelData.contains("width") ? levelData["width"].get<int>() : 0;

  if (y_size == 0 || x_size == 0) {
    std::cout << "Ошибка: размеры уровня не определены или равны нулю!"
              << std::endl;
    return -1; // Завершаем программу, так как данные неверны
  }

  // Проверка корректности размера массива
  if (map.size() != static_cast<size_t>(y_size * x_size)) {
    std::cout << "Ошибка: размер данных 'map' (" << map.size()
              << ") не соответствует заданным размерам уровня ("
              << y_size * x_size << ")!" << std::endl;
    return -1; // Завершаем программу, так как данные неверны
  }

  // Добавление платформ в зависимости от данных карты
  for (int y = 0; y < y_size; ++y) {
    for (int x = 0; x < x_size; ++x) {
      int maptit = map[y * x_size + x];

      // Проверка значений для мапы
      //  if (maptit == 34) {
      if (maptit == 0) {
        continue;
      }
      --maptit;
      block.setPosition(32.f * x, 32.f * y);
      block.setTextureRect(
          sf::IntRect(32 * (maptit % 16), 32 * (maptit / 16), 32, 32));
      // block.setFillColor(sf::Color(100, 100, 100));
      platforms.push_back(block);
      std::cout << " add block" << std::endl;
    }
  }

  /*
    for (int i = 0; i < 32; ++i) {
      for (int u = 0; u < 32; ++u) {
        if (blocks[i][u] == 1) {
          //      sf::RectangleShape block(sf::Vector2f(32.f, 32.f));
          block.setPosition(32.f * u, 32.f * i);
          block.setFillColor(sf::Color(100, 100, 100));
          platforms.push_back(block);
        }
        if (blocks[i][u] == 2) {
          items.emplace_back(std::make_unique<Item>(32.f * u, 32.f * i));
        }
      }
    }
  */
  /*
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

  std::vector<std::unique_ptr<Item>>
      items; // Создаём вектор указателей на Item
  items.emplace_back(std::make_unique<Item>(
      300.f, 300.f)); // Создаём объект без копирования прямо в векторе
  items.emplace_back(std::make_unique<Item>(500.f, 300.f));
  items.emplace_back(std::make_unique<Item>(600.f, 300.f));
  */
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

    //  window.draw(items[0]->Sprite);

    player.moveX(deltaTime.asSeconds());
    player.updateAnimation(deltaTime.asSeconds()); // передвигаем игрока
    for (auto &platform : platforms) {
      player.resolveCollisionX(player.sprite, platform);
    }

    player.moveY(deltaTime.asSeconds()); // передвигаем игрока
    for (auto &platform : platforms) {
      player.resolveCollisionY(player.sprite, platform);
    }

    window.draw(player.sprite);         // Рисуем игрока//
    window.draw(scorePlayer.scoreText); // рисуем счет

    window.display(); // Отображаем всё на экране
  }

  return 0;
}
