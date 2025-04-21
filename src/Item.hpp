#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>



class Item {
    public:
        sf::Sprite Sprite;
        sf::Texture Item_texture; 
        bool collect = false;
       
        Item(float x, float y);
        ~Item();
        void draw(sf::RenderWindow& window);
        sf::Sprite& getSprite(); 
private:
//        sf::Sprite Sprite;
        //sf::Texture Item_texture;


};


#endif
