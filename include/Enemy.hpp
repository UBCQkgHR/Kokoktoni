#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
enum class State { Idle, Attack, Left, Right };
class Enemy {
   public:
    sf::Sprite sprite;
    sf::Texture texture_Idle;
    sf::Texture texture_Walk;
    sf::Texture texture_Attack;
    Enemy();
    ~Enemy();
    void moveY(float deltaTime);
    void moveX(float deltaTime);

    sf::FloatRect bounds;
    int direction;
    void resolveCollisionX(sf::Sprite &enemy,
                           const sf::RectangleShape &platforms);
    void resolveCollisionY(sf::Sprite &enemy,
                           const sf::RectangleShape &platforms);
    void updateAnimation(float deltaTime);
    void update();

   private:
    int currentFrame = 0;
    sf::Vector2f desiredSize;
    float animationTimer = 0.1f;
    float frameDuration = 0.1f;
    int totalFrames = 4;
    bool wallhit = false;
    sf::Vector2f rect;
    sf::Vector2f velocity;
    float gravity = 20.f;
    State EnemyCurrent = State::Right;
    int speed;
};
#endif
