
#include "../include/Enemy.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

Enemy::Enemy() {
  desiredSize.x = 70.f;
  desiredSize.y = 50.f;
  direction = 1;
  speed = 100;
  velocity.x = 100.f;
  if (!(texture_Idle.loadFromFile("../asset/cow/cow_eat.png"))) {
    printf("%s", " Do not load File Enemy!");
  };
  if (!(texture_Walk.loadFromFile("../asset/cow/cow_walk.png"))) {
    printf("%s", " Do not load File Enemy_Walk!");
  };
  if (!(texture_Attack.loadFromFile("../asset/Enemy_Attack.png"))) {
    printf("%s", " Do not load File Enemy_Attack!");
  };

  sprite.setTexture(texture_Walk);
  sprite.setTextureRect(sf::IntRect(20, 170, 70, 45));
  sprite.setPosition(200.0f, 50.0f);
  sf::FloatRect localBounds = sprite.getLocalBounds();
  sf::IntRect rect = sprite.getTextureRect();

  std::cout << " Enemy Rect: " << rect.width << "x" << rect.height << std::endl;

  bounds = sprite.getGlobalBounds();
  sprite.setScale(desiredSize.x / localBounds.width,
                  desiredSize.y / localBounds.height);
}
Enemy::~Enemy(){};

void Enemy::setSpeed(int setSpeed) { speed = setSpeed; }

void Enemy::updateAnimation(float deltaTime) {
  animationTimer += deltaTime;
  switch (EnemyCurrent) {
  case State::Attack:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 5;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Attack);
      sprite.setTextureRect(sf::IntRect((currentFrame * 128), 37, 128, 91));
    }
    break;
  case State::Idle:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 10;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Idle);
      sprite.setTextureRect(sf::IntRect((currentFrame * 128) + 20, 37, 67, 91));
    }
    break;

  case State::Left:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 4;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Walk);
      sprite.setTextureRect(
          sf::IntRect((currentFrame * 128) + 20, 173, 70, 45));
    }
    break;
  case State::Right:
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      totalFrames = 4;
      currentFrame = (currentFrame + 1) % totalFrames;
      sprite.setTexture(texture_Walk);
      sprite.setTextureRect(
          sf::IntRect((currentFrame * 128) + 35, 429, 70, 45));
    }

    break;
  }
}

;
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
      direction = -1;
    } else if (velocity.x < 0) {
      enemy.setPosition(platformBounds.left + enemyBounds.width,
                        enemyBounds.top);
      direction = 1;
    }
    velocity.x = 0;
    //  wallhit = true;
  }
}

void Enemy::update() {
  // if (wallhit) {
  //    direction *= -1;
  //    wallhit = false;
  // }
  velocity.x = direction * speed;
  EnemyCurrent = (direction > 0) ? State::Right : State::Left;
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
