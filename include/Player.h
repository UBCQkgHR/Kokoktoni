#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player {
public:
  sf::Sprite sprite;
  sf::Texture texture;
  float speed = 200.0f;
  int score = 0;
  Player();
  ~Player();
  void moveX(float deltaTime);

  void moveY(float deltaTime);

  struct AABB {
    float left, top, right, bottom;

    AABB(const sf::FloatRect &bounds) {
      left = bounds.left;
      top = bounds.top;
      right = bounds.left + bounds.width;
      bottom = bounds.top + bounds.height;
    }
  };
  /*  void resolveCollision(sf::Sprite &player,
                          const sf::RectangleShape &platforms);
  */

  void resolveCollisionX(sf::Sprite &player,
                         const sf::RectangleShape &platforms);

  void resolveCollisionY(sf::Sprite &player,
                         const sf::RectangleShape &platforms);

  void updateAnimation(float deltaTime);

private:
  int currentFrame = 0;
  float animationTimer = 0.f;
  float frameDuration = 0.1f;
  int totalFrames = 4;
  sf::Vector2f velocity; // скорость по х и у
  float gravity = 300.f;
  float jumpStrength = -200.f;
  sf::FloatRect bounds;
  sf::Vector2f desiredSize;
};

#endif
