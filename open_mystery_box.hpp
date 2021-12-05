//
//  open_mystery_box.hpp
//  Snake
//
//  Created by Channing Christian on 3/23/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef open_mystery_box_hpp
#define open_mystery_box_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "snake.hpp"
#include "mystery_box.hpp"
#include "game.hpp"

using namespace std;

void open_mystery_box(sf::RenderWindow * window, game * game, snake * snake, mystery_box * mysteryBox, food * food, super_food * superFood, text_box * level, text_box * score, std::vector<bot*> * bots, sf::Sprite inventorySprite){
    double initXPos = mysteryBox->get_sprite().getPosition().x;
    double initYPos = mysteryBox->get_sprite().getPosition().y;
    
    double changeInX = 500 - initXPos;
    double changeInY = 500 - initYPos;
    
    sf::Sprite star;
    sf::Texture texture;
    texture.loadFromFile("Textures/star.png");
    star.setTexture(texture);
    star.setScale(17, 17);
    star.setOrigin(16, 16);
    star.setPosition(500, 500);
    
    mystery_box_item * mbi;
    
    bool showStar = false;
    bool showContents = false;
    bool breakLoop = false;
    bool anamateMysteryBox = true;
    
    std::string contents = mysteryBox->get_contents();
    
    sf::Clock clock;
    double time;
    
    while(NULL == NULL){
        if(breakLoop == true){
            break;
        }
        time = clock.getElapsedTime().asMilliseconds();
        if(time >= 1){
            if(time <= 2){
                sf::Event event;
                while(window->pollEvent(event)){
                    if(event.type == sf::Event::KeyPressed){
                        breakLoop = true;
                    } else if(event.type == sf::Event::Closed){
                        window->close();
                    }
                }
                if(anamateMysteryBox == true){
                    if(mysteryBox->get_sprite().getPosition().x >= 501 || mysteryBox->get_sprite().getPosition().x <= 499) {
                        if(changeInX > 0){
                            mysteryBox->movement(sf::Vector2f(0.3, 0));
                        } else if (changeInX < 0){
                            mysteryBox->movement(sf::Vector2f(-0.3, 0));
                        }
                        mysteryBox->update_mystery_box();
                    } else if(mysteryBox->get_sprite().getPosition().y >= 501 || mysteryBox->get_sprite().getPosition().y <= 499) {
                        if(changeInY > 0){
                            mysteryBox->movement(sf::Vector2f(0, 0.3));
                        } else if (changeInY < 0){
                            mysteryBox->movement(sf::Vector2f(0, -0.3));
                        }
                        mysteryBox->update_mystery_box();
                    } else {
                        mysteryBox->movement(sf::Vector2f(0, 0));
                        if(mysteryBox->get_sprite().getScale().x < 20 && mysteryBox->get_sprite().getScale().y < 20) {
                            mysteryBox->set_scale(mysteryBox->get_sprite().getScale().x + 0.003, mysteryBox->get_sprite().getScale().y + 0.003);
                            if(mysteryBox->get_sprite().getScale().x > 19.99 && mysteryBox->get_sprite().getScale().y > 19.99){
                                mysteryBox->set_open_texture();
                                mysteryBox->reset_anamation();
                            } else {
                                mysteryBox->update_mystery_box();
                            }
                        } else {
                            if(mysteryBox->get_sprite().getPosition().x > -99 && mysteryBox->get_sprite().getPosition().y > -99){
                                mysteryBox->open_box();
                            }
                            if(mysteryBox->get_sprite().getPosition().x < -99 && mysteryBox->get_sprite().getPosition().y < -99){
                                if(contents == "level up"){
                                    mbi = new level_up();
                                    game->set_active_level_up_mb(true);
                                } else if (contents == "bomb"){
                                    mbi = new bomb();
                                    game->set_bomb(true);
                                } else if (contents == "poison"){
                                    mbi = new poison();
                                    game->set_active_poison(true);
                                } else if (contents == "freeze"){
                                    mbi = new freeze();
                                    game->set_freeze(true);
                                } else if (contents == "shield"){
                                    mbi = new shield();
                                    game->set_shield(true);
                                } else if (contents == "wall"){
                                    mbi = new wall();
                                    game->set_wall(true);
                                }
                                mbi->set_scale(0, 0);
                                mbi->set_orig(16, 16);
                                mbi->set_pos(500, 500);
                                showContents = true;
                                anamateMysteryBox = false;
                            }
                            showStar = true;
                        }
                    }
                }
                window->clear();
                window->draw(level->getText());
                window->draw(score->getText());
                window->draw(food->get_sprite());
                window->draw(superFood->get_sprite());
                for(snake_part * snakePart : snake->get_snake_parts()){
                    window->draw(snakePart->get_sprite());
                }
                for(bot * bot : * bots){
                    for(snake_part * snakePart : bot->get_snake()->get_snake_parts()){
                        window->draw(snakePart->get_sprite());
                    }
                }
                if(showStar == true){
                    window->draw(star);
                    star.rotate(0.05);
                    star.setScale(star.getScale().x - 0.005, star.getScale().y - 0.005);
                    if(star.getScale().x < 0 && star.getScale().y < 0){
                        showStar = false;
                    }
                }
                if(showContents == true){
                    window->draw(mbi->get_sprite());
                    if(mbi->get_sprite().getScale().x <= 20 && mbi->get_sprite().getScale().y <= 20){
                        mbi->set_scale(mbi->get_sprite().getScale().x + 0.005, mbi->get_sprite().getScale().y + 0.005);
                    } else {
                        mbi->movement(sf::Vector2f(0, -0.5));
                        if(mbi->get_sprite().getPosition().y < -900){
                            breakLoop = true;
                            mbi->movement(sf::Vector2f(0, 0));
                        }
                    }
                }
                window->draw(mysteryBox->get_sprite());
                window->draw(inventorySprite);
                window->display();
            } else {
                clock.restart();
            }
        }
    }
    game->go_playing();
}

#endif /* open_mystery_box_hpp */
