#ifndef GAME_CPP
#define GAME_CPP
#include "../include/Game.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

Game::Game(){};
Game::~Game(){};

void drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite,
                sf::Color color) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape debugBox;
    debugBox.setSize(sf::Vector2f(bounds.width, bounds.height));
    debugBox.setPosition(bounds.left, bounds.top);
    debugBox.setFillColor(sf::Color::Transparent);
    debugBox.setOutlineColor(color);
    debugBox.setOutlineThickness(1.5f);
    window.draw(debugBox);
}

#endif
