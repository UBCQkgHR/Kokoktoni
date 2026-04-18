#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
class Score {
   public:
    sf::Font font;
    sf::Text scoreText;
    sf::Text healthText;

    Score(std::string font_in);
    ~Score();
    void setHealString(int health, int maxhealth);
    void SetString(int score);
};
#endif
