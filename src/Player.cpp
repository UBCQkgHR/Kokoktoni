#include "../include/Player.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
Player::Player() {
  desiredSize.x = 25.f;
  desiredSize.y = 25.f;

  if (!(texture.loadFromFile("../playerDr.png"))) {
    printf("%s", "Don`t load file!");
  };
  sprite.setTexture(texture);
  sprite.setTextureRect(sf::IntRect(0, 105, 105, 105));
  sprite.setPosition(100.0f, 100.0f);
  sprite.setScale(desiredSize.x / bounds.width, desiredSize.y / bounds.height);
  sf::FloatRect localBounds = sprite.getLocalBounds();
  sf::IntRect rect = sprite.getTextureRect();

  std::cout << "Rect: " << rect.width << "x" << rect.height << std::endl;

  bounds = sprite.getGlobalBounds();
  sprite.setScale(desiredSize.x / localBounds.width,
                  desiredSize.y / localBounds.height);
  sprite.setPosition(100.f, 100.f);
  currentFrame = 0;
  animationTimer = 0.f;
  frameDuration = 0.1f;
  totalFrames = 3;
}

Player::~Player() {};

void Player::updateAnimation(float deltaTime) {
  animationTimer += deltaTime;
  if (animationTimer >= frameDuration) {
    animationTimer = 0.f;
    currentFrame = (currentFrame + 1) % totalFrames;
    sprite.setTextureRect(sf::IntRect(currentFrame * 105, 105, 105, 105));
  }
}

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
