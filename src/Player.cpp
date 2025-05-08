#include "../include/Player.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
Player::Player() {

  desiredSize.x = 63.f;
  desiredSize.y = 64.f;

  if (!(texture_Idle.loadFromFile("../asset/Idle.png"))) {
    printf("%s", "Don`t load file Idle Player!");
  };

  if (!(texture_Walk.loadFromFile("../asset/Walk.png"))) {
    printf("%s", "Don`t load file walki_player !");
  };

  if (!(texture_Attack.loadFromFile("../asset/Attack.png"))) {
    printf("%s", "Don`t load file walki_player !");
  };
  sprite.setTexture(texture_Idle);
  sprite.setTextureRect(sf::IntRect(20, 30, 128, 128));
  sprite.setPosition(100.0f, 100.0f);
  // sprite.setScale(desiredSize.x / bounds.width, desiredSize.y /
  // bounds.height);
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
  switch (currentState) {
  case PlayerState::Attack:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 5;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Attack);
      sprite.setTextureRect(sf::IntRect((currentFrame * 128), 37, 128, 91));
    }
    break;
  case PlayerState::Idle:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 10;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Idle);
      sprite.setTextureRect(sf::IntRect(currentFrame * 128 + 20, 37, 67, 91));
    }
    break;

  case PlayerState::RunLeft:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      currentFrame = (currentFrame + 1) % totalFrames;
      totalFrames = 12;
      sprite.setTexture(texture_Walk);
      sprite.setTextureRect(
          sf::IntRect((currentFrame * 128) + 128 - 40, 37, -67, 91));
    }
    break;
  case PlayerState::RunRight:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 12;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Walk);
      sprite.setTextureRect(sf::IntRect((currentFrame * 128) + 20, 37, 67, 91));
    }

    break;
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
    currentState = PlayerState::RunLeft;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x = 100.f;
    currentState = PlayerState::RunRight;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    currentState = PlayerState::Attack;
  } else {
    velocity.x = 0.f;
    currentState = PlayerState::Idle;
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
