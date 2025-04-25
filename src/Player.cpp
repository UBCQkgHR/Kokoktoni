#include "../include/Player.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
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

void Player::moveY(float deltaTime) {
  velocity.y += gravity * deltaTime;
  if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key::Space))) {
    velocity.y = jumpStrength;
  }
  // velocity.x = 0.f;

  sprite.move(0.f, velocity.y * deltaTime);
};

void Player::moveX(float deltaTime) {
  // velocity.y = 0;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity.x = -100.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x = 100.f;
  } else {
    velocity.x = 0.f;
  }

  sprite.move(velocity.x * deltaTime, 0.f);
};

void Player::resolveCollisionX(sf::Sprite &player,
                               const sf::RectangleShape &platforms) {
  sf::FloatRect playerBounds = player.getGlobalBounds();
  sf::FloatRect platformBounds = platforms.getGlobalBounds();

  if (playerBounds.intersects(platformBounds)) {
    if (velocity.x > 0) {
      player.setPosition(platformBounds.left - playerBounds.width,
                         playerBounds.top);
    } else if (velocity.x < 0) {
      player.setPosition(platformBounds.left + platformBounds.width,
                         playerBounds.top);
    }
    velocity.x = 0;
  }
}

void Player::resolveCollisionY(sf::Sprite &player,
                               const sf::RectangleShape &platforms) {
  sf::FloatRect playerBounds = player.getGlobalBounds();
  sf::FloatRect platformBounds = platforms.getGlobalBounds();

  if (playerBounds.intersects(platformBounds)) {
    if (velocity.y > 0) {
      player.setPosition(player.getPosition().x,
                         platformBounds.top - playerBounds.height);
    } else if (velocity.y < 0) {
      player.setPosition(player.getPosition().x,
                         platformBounds.height + platformBounds.top);
    }
    velocity.y = 0;
  }
}
