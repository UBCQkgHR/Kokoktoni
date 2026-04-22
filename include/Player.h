#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Level.h"

enum class PlayerState { Idle, Walk, RunLeft, RunRight, Jump, Fall, Attack };
struct AttackHitbox {
    sf::Vector2f size = {50.f, 50.f};
    sf::Vector2f offset = {40.f, 20.f};
    float damage = 1;
    float knockback = 300.f;
    float activeDuration = 0.2f;
};

class Player {
   public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture texture_Idle;
    sf::Texture texture_Attack;
    sf::Texture texture_Walk;
    float speed = 200.0f;
    int direction = 1;
    int health = 3;
    int maxhealth = 3;
    void takeDamage(int damage = 1);
    void heal(int amount = 1);
    bool isAlive() const { return health > 0; }

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
    //  void checkCollisionX(const Level &level);
    void setIsJump(bool value);
    bool getIsJump() const;
    // void checkCollisionY(const Level &level);
    void updateInvincibility(float deltaTime);
    bool getIsInvicible();
    // Метод для рабооты с хитбоксом
    void attack();
    bool isAttacking() const { return m_isAttacking; }
    sf::FloatRect getAttackHitbox() const;
    void updateAttack(float deltaTime);
    void drawAttackhitbox(sf::RenderWindow &Window) const;
    // Геттеры для настроек
    const AttackHitbox &getAttackSetting() const { return m_attackSetting; }

   private:
    bool IsInvincible = false;
    float IsInvincibleTimer = 0.f;
    float IsInvincibleDuration = 1.5f;
    int currentFrame = 0;
    float animationTimer = 0.f;
    float frameDuration = 0.1f;
    int totalFrames = 4;

    // состояние анимации атаки
    float attackTimer = 0.f;
    bool isAttack = false;
    float attackDuration = 0.4f;  // длительность атаки

    sf::Vector2f velocity;  // скорость по х и у
    float gravity = 400.f;
    float jumpStrength = -200.f;
    sf::FloatRect bounds;
    sf::Vector2f desiredSize;
    PlayerState currentState;
    int tileleft, tileright, tiletop, tilebottom;
    float tileSize = 32;
    float left, top, right, bottom;
    bool collision;
    bool IsJump = false;
    // состояние атаки
    bool m_isAttacking = false;
    float m_attackTimer = 0.f;
    float m_attackCooldown = 0.f;
    // Настройка Хитбокса
    AttackHitbox m_attackSetting;
    bool m_factingRight = true;  // Направление взгляда.
};

#endif
