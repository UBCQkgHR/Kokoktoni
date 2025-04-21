#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
class Score {
    public:
    sf::Font font;
    sf::Text scoreText;

    Score(std::string font_in);
    ~Score();
   void  SetString(int score);






};
#endif
