#include "Item.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

Item::Item(float x, float y){
    std::cout << "constructor"<<std::endl;
    //Item_texture = new sf::Texture();

    if(!Item_texture.loadFromFile("/home/dadei/C/product/Kokotoni/test_Item_texture.png")){
        printf("%s","Don`t load fite texture ITEM test\n");
    }else{
    printf("%s"," Texture is load: test_Item_texture.png\n");}
    Sprite.setTexture(Item_texture);
    Sprite.setPosition(x,y);
};
Item::~Item(){
    //delete Item_texture;
};


sf::Sprite& Item::getSprite(){
return Sprite;}

void Item::draw(sf::RenderWindow& window){
    if(!collect){
        window.draw(Sprite);
    }
}
