#include "../include/Player.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player() {
  if (!(texture.loadFromFile("../player.png"))) {
    printf("%s", "Don`t load file!");
  };
  sprite.setTexture(texture);
  sprite.setPosition(100.0f, 100.0f);
}

Player::~Player(){};

void Player::move(float deltaTime) {
  velocity.y += gravity * deltaTime;
  if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key::Space))) {
    velocity.y = jumpStrength;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity.x = -100.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x = 100.f;
  } else {
    velocity.x = 0.f;
  }

  sprite.move(velocity * deltaTime);
  sf::Vector2f pos = sprite.getPosition();
  // if (pos.y > 500.f) {
  //   pos.y = 500.f;
  //   velocity.y = 0.f;
  // }
  if (pos.x < 0) {
    pos.x = 0;
  }
  if (pos.x > 800 - sprite.getGlobalBounds().width) {
    pos.x = 800 - sprite.getGlobalBounds().width;
  }
  /*for (const auto &platform : platforms) {
    if (sprite.getGlobalBounds().intersects(platform.getGlobalBounds())) {
      sf::Vector2f pos = sprite.getPosition();
      pos.y = platform.getPosition().y - sprite.getGlobalBounds().height;
      sprite.setPosition(pos);
      velocity.y = 0.f;
    }
  }*/
  sprite.setPosition(pos);
}

void Player::resolveCollision(sf::Sprite &player,
                              const sf::RectangleShape &platforms) {
  AABB A(player.getGlobalBounds());
  AABB B(platforms.getGlobalBounds());

  if (A.right > B.left && A.left < B.right && A.bottom > B.top &&
      A.top < B.bottom) {
    float overlaX = std::min(A.right, B.right) - std::max(A.left, B.left);
    float overlaY = std::min(A.bottom, B.bottom) - std::max(A.top, B.top);

    if (overlaX < overlaY) {
      if (A.left < B.left) {
        player.move(-overlaX, 0.f);
      } else {
        player.move(overlaX, 0.f);
      }
    } else {
      if (A.top < B.top) {
        player.move(0.f, -overlaY);
      } else {
        player.move(0.f, overlaY);
      }
    }
  }
};
