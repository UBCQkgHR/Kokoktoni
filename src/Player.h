#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>


class Player{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed = 200.0f;
    int score = 0;
    Player();
    ~Player();
    void move(float deltaTime);
   

private:
    sf::Vector2f velocity; //скорость по х и у
    float gravity =  300.f;
    float jumpStrength = -200.f;
};

#endif
