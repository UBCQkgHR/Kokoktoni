#include "Player.h"
#include "Item.hpp"
#include "Score.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <filesystem>
int main() {
    // Создаём окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kokotoni Wilf");
    
    sf::Texture Test_Item_texture;
    sf::Sprite Test_sprite;
    Test_Item_texture.loadFromFile("/home/dadei/C/product/Kokotoni/Item_texture.png");
  Test_sprite.setPosition( 10.f, 10.f);  
  Test_sprite.setTexture(Test_Item_texture);
  //  if(!Item.Item_texture->loadFromFile("/home/dadei/C/product/Kokotoni/Item_texture.png")){
    //        printf("%s", "Don`t load file item!.");}


Item test_item(10.f, 10.f);
    /*std::vector<Item> items = {
       Item(300.f, 300.f),
       Item(500.f, 300.f),
       Item(600.f, 300.f),
    };*/
std::vector<std::unique_ptr<Item>> items;

items.emplace_back(std::make_unique<Item>(300.f, 300.f));
items.emplace_back(std::make_unique<Item>(500.f, 300.f));
items.emplace_back(std::make_unique<Item>(600.f, 300.f));

    items[0]->Sprite.setTexture(Test_Item_texture);
   test_item.Sprite.setTexture(Test_Item_texture); 
    Player player;
    sf::Clock clock;
    Score scorePlayer("/home/dadei/C/product/Kokotoni/arialmt.ttf");
std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;
   // std::cout << items[0].collect << std::endl;
    while (window.isOpen()) {
        sf::Event event;
//    std::cout << &items[0]<<std::endl;
  //  std::cout << &items[1]<<std::endl;
    //std::cout << &items[2]<< std::endl;
        sf::Time deltaTime = clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Закрытие окна
            }
        }
        player.move(deltaTime.asSeconds());// передвигаем игрока
        
        
        for (auto& item : items) {
            if (!item->collect && player.sprite.getGlobalBounds().intersects(item->getSprite().getGlobalBounds())){
                item->collect =  true;
                player.score++;
                scorePlayer.SetString(player.score);
            }
        }

                                                       
                                                      

        window.clear(); // Очищаем экран
        for (auto& item : items) {
          item->draw(window);
        }

        window.draw(items[0]->Sprite);

        window.draw(test_item.Sprite);
        window.draw(player.sprite); // Рисуем игрока//
        window.draw(scorePlayer.scoreText);//рисуем счет  



        window.display(); // Отображаем всё на экране
    }

    return 0;
}

