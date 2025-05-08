#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "./Item.hpp"
#include "./json.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <string>
using json = nlohmann::json;

class Level {
public:
  Level();
  ~Level();

  std::vector<std::unique_ptr<Item>> items;
  sf::Texture blockTexture;
  sf::RectangleShape block;
  json levelData;
  std::vector<int> map;
  void loadmap();
  int x_size;
  int y_size;
  std::vector<sf::RectangleShape> platforms;

  std::vector<sf::RectangleShape> platforms_collision;
  std::string layer_class;
};
#endif
