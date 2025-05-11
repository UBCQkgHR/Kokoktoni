
#include "../include/Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

Enemy::Enemy() {
  desiredSize.x = 120.f;
  desiredSize.y = 120.f;
  direction = 0;
  velocity.x = 100.f;
  if (!(texture_Idle.loadFromFile("../asset/Enemy.png"))) {
    printf("%s", " Do not load File Enemy!");
  };
  if (!(texture_Walk.loadFromFile("../asset/Enemy_Walk.png"))) {
    printf("%s", " Do not load File Enemy_Walk!");
  };
  if (!(texture_Attack.loadFromFile("../asset/Enemy_Attack.png"))) {
    printf("%s", " Do not load File Enemy_Attack!");
  };

  sprite.setTexture(texture_Idle);
  sprite.setTextureRect(sf::IntRect(0, 105, 105, 105));
  sprite.setPosition(200.0f, 200.0f);
  sf::FloatRect localBounds = sprite.getLocalBounds();
  sf::IntRect rect = sprite.getTextureRect();

  std::cout << " Enemy Rect: " << rect.width << "x" << rect.height << std::endl;

  bounds = sprite.getGlobalBounds();
  sprite.setScale(desiredSize.x / localBounds.width,
                  desiredSize.y / localBounds.height);
}
Enemy::~Enemy(){};

void Enemy::moveY(float deltaTime) {
  velocity.y += gravity * deltaTime;
  sprite.move(0.f, velocity.y * deltaTime);
};

void Enemy::moveX(float deltaTime) {
  // if (direction == 0) {
  //  velocity.x = -50.0f;
  //} else if (direction == 1) {
  // velocity.x = 50.0f;
  // };
  sprite.move(velocity.x * deltaTime, 0.f);
};

void Enemy::resolveCollisionX(sf::Sprite &enemy,
                              const sf::RectangleShape &platforms) {
  sf::FloatRect enemyBounds = enemy.getGlobalBounds();
  sf::FloatRect platformBounds = platforms.getGlobalBounds();
  if (enemyBounds.intersects(platformBounds)) {
    if (velocity.x > 0) {

      enemy.setPosition(platformBounds.left - enemyBounds.width,
                        enemyBounds.top);
    } else if (velocity.x < 0) {
      enemy.setPosition(platformBounds.left + enemyBounds.width,
                        enemyBounds.top);
    }
    velocity.x = -velocity.x;
  }
}

void Enemy::resolveCollisionY(sf::Sprite &enemy,
                              const sf::RectangleShape &platforms) {
  sf::FloatRect enemyBounds = enemy.getGlobalBounds();
  sf::FloatRect platformBounds = platforms.getGlobalBounds();
  if (enemyBounds.intersects(platformBounds)) {
    if (velocity.y > 0) {
      enemy.setPosition(enemy.getPosition().x,
                        platformBounds.top - enemyBounds.height);
    } else if (velocity.y < 0) {
      enemy.setPosition(enemy.getPosition().x,
                        platformBounds.height + platformBounds.top);
    }
    velocity.y = 0;
  }
}
