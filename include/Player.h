#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Level.h"

enum class PlayerState { Idle, Walk, RunLeft, RunRight, Jump, Fall, Attack };

class Player {
public:
  sf::Sprite sprite;
  sf::Texture texture;
  sf::Texture texture_Idle;
  sf::Texture texture_Attack;
  sf::Texture texture_Walk;
  float speed = 200.0f;
  int score = 0;
  Player();
  ~Player();
  void moveX(float deltaTime);

  void moveY(float deltaTime);
  sf::Vector2f &getVelocity() { return velocity; };
  sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); };
  void setPosition(float x, float y) { sprite.setPosition(x, y); };
  /* struct AABB {
       float left, top, right, bottom;

       AABB(const sf::FloatRect &bounds) {
           left = bounds.left;
           top = bounds.top;
           right = bounds.left + bounds.width;
           bottom = bounds.top + bounds.height;
       }
   };
     void resolveCollision(sf::Sprite &player,
                           const sf::RectangleShape &platforms);
   */

  void resolveCollisionX(sf::Sprite &player,
                         const sf::RectangleShape &platforms);

  void resolveCollisionY(sf::Sprite &player,
                         const sf::RectangleShape &platforms);

  void updateAnimation(float deltaTime);
  void checkCollisionX(const Level &level);
  void checkCollisionY(const Level &level);

private:
  int currentFrame = 0;
  float animationTimer = 0.f;
  float frameDuration = 0.1f;
  int totalFrames = 4;
  sf::Vector2f velocity; // скорость по х и у
  float gravity = 100.f;
  float jumpStrength = -200.f;
  sf::FloatRect bounds;
  sf::Vector2f desiredSize;
  PlayerState currentState;
  int tileleft, tileright, tiletop, tilebottom;
  float tileSize = 32;
  float left, top, right, bottom;
  bool collision;
};

#endif
