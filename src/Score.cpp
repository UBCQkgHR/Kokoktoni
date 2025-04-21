#ifndef SCORE_CPP
#define SCORE_CPP
#include "Score.h"
#include <SFML/Graphics/Color.hpp>
#include <string>

Score::Score(std::string font_in){
    if(!font.loadFromFile(font_in)){
        printf("%s"," Don`t load Font_score!:");}
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

}
Score::~Score(){};

void Score::SetString(int score){
    scoreText.setString("Score :" + std::to_string(score));
    
    }
#endif



