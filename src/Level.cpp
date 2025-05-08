#include "../include/Level.h"
#include "../include/json.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include <iostream>

Level::Level() {
  if (!(blockTexture.loadFromFile("../goodly-2x.png"))) {
    printf("%s", "Don`t load texture trava!");
  }

  //  sf::RectangleShape block(sf::Vector2f(31.f, 31.f));
  block.setTexture(&blockTexture);
  block.setTextureRect(sf::IntRect(0, 0, 32, 32));

  std::ifstream file("../map/test1.json");
  std::cout << " file json is open" << std::endl;
  // std::vector<int> map;
  if (!file.is_open()) {
    std::cout << " File do not open" << std::endl;
  } else {
    file >> levelData;
  }

  std::cout << " File  is open" << std::endl;
};

Level::~Level() {};

// Проверка наличия и загрузки данных из JSON
void Level::loadmap() {

  if (!(blockTexture.loadFromFile("../goodly-2x.png"))) {
    printf("%s", "Don`t load texture trava!");
  }
  for (auto i = 0; i < 2; ++i) {
    if (levelData.contains("layers") && levelData["layers"].is_array() &&
        !levelData["layers"].empty()) {
      auto &layer = levelData["layers"][i];
      std::cout << "Массив 'layer' загружен" << std::endl;

      if (layer.contains("data") && layer["data"].is_array()) {
        layer_class = layer["class"];
        map = layer["data"].get<std::vector<int>>();
        std::cout << "Массив 'data' загружен в map" << std::endl;
      } else {
        std::cout << "Поле 'data' не найдено или не массив" << std::endl;
      }
    } else {
      std::cout << "Поле 'layers' не найдено или не массив" << std::endl;
    }

    // Получаем размеры карты
    y_size = levelData.contains("height") ? levelData["height"].get<int>() : 0;
    x_size = levelData.contains("width") ? levelData["width"].get<int>() : 0;

    if (y_size == 0 || x_size == 0) {
      std::cout << "Ошибка: размеры уровня не определены или равны нулю!"
                << std::endl;
    }

    // Проверка корректности размера массива
    if (map.size() != static_cast<size_t>(y_size * x_size)) {
      std::cout << "Ошибка: размер данных 'map' (" << map.size()
                << ") не соответствует заданным размерам уровня ("
                << y_size * x_size << ")!" << std::endl;
    }

    // Добавление платформ в зависимости от данных карты
    for (int y = 0; y < y_size; ++y) {
      for (int x = 0; x < x_size; ++x) {
        int maptit = map[y * x_size + x];

        // Проверка значений для мапы
        if (maptit == 0) {
          continue;
        }
        --maptit;
        sf::RectangleShape block(sf::Vector2f(31.f, 31.f));
        block.setPosition(32.f * x, 32.f * y);
        block.setTexture(&blockTexture);
        block.setTextureRect(
            sf::IntRect(32 * (maptit % 16), 32 * (maptit / 16), 32, 32));
        // block.setFillColor(sf::Color(100, 100, 100));
        platforms.push_back(block);
        if (layer_class == "CollisionLayer") {
          for (int y = 0; y < y_size; ++y) {
            for (int x = 0; x < x_size; ++x) {
              int maptit = map[y * x_size + x];

              // Проверка значений для мапы
              if (maptit == 0) {
                continue;
              }
              --maptit;
              sf::RectangleShape block(sf::Vector2f(31.f, 31.f));
              block.setPosition(32.f * x, 32.f * y);
              // block.setTexture(&blockTexture);
              block.setTextureRect(
                  sf::IntRect(32 * (maptit % 16), 32 * (maptit / 16), 32, 32));
              // block.setFillColor(sf::Color(100, 100, 100));
              platforms_collision.push_back(block);
            }
          }
        }
        std::cout << " add block" << std::endl;
      }
    }
  }
};
