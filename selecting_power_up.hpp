//
//  selecting_power_up.hpp
//  Snake
//
//  Created by Channing Christian on 3/31/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef selecting_power_up_hpp
#define selecting_power_up_hpp

#include "game.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "mystery_box.hpp"

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class selector {
private:
    sf::Sprite sprite;
    sf::Texture texture;
public:
    selector(){
        this->texture.loadFromFile("Textures/selector.png");
        this->sprite.setTexture(this->texture);
        this->set_orig(16, 16);
        this->set_scale(2.5, 2.5);
        this->set_pos(410, 950);
    }
    
    sf::Sprite get_sprite(){
        return this->sprite;
    }
    
    void set_orig(double x, double y){
        this->sprite.setOrigin(x, y);
    }
    
    void set_pos(double x, double y){
        this->sprite.setPosition(x, y);
    }
    
    void set_scale(double x, double y){
        this->sprite.setScale(x, y);
    }
};

void a_pressed(selector * selector){
    if(selector->get_sprite().getPosition().x > 50){
        selector->set_pos(selector->get_sprite().getPosition().x - 90, selector->get_sprite().getPosition().y);
    }
}

void d_pressed(selector * selector){
    if(selector->get_sprite().getPosition().x < 410){
        selector->set_pos(selector->get_sprite().getPosition().x + 90, selector->get_sprite().getPosition().y);
    }
}

void selecting_power_up(sf::RenderWindow * window, snake * snake, food * food, super_food * superfood, game * game, sf::Sprite inventorySprite, mystery_box * mysteryBox, text_box * level, text_box * score, text_box * levelUp1, text_box * levelUp2, std::vector<bot*> * bots){
    
    selector * selector = new class selector();
    sf::Clock selectorClock;
    double selectorTime;
    
    bool drawBomb = false;
    bool drawFreeze = false;
    bool drawWall = false;
    bool drawShield = false;
    bool drawSelector = false;
    bool closeInventory = false;
    
    bomb * b = new bomb();
    b->set_orig(16, 16);
    b->set_scale(2.5, 2.5);
    b->set_pos(50, inventorySprite.getPosition().y);
    if(game->get_bomb() == false){
        b->set_color(128, 128, 128);
    }
    
    freeze * f = new freeze();
    f->set_orig(16, 16);
    f->set_scale(2.5, 2.5);
    f->set_pos(140, inventorySprite.getPosition().y);
    if(game->get_freeze() == false){
        f->set_color(128, 128, 128);
    }
    
    wall * w = new wall();
    w->set_orig(16, 16);
    w->set_scale(2.5, 2.5);
    w->set_pos(230, inventorySprite.getPosition().y);
    if(game->get_wall() == false){
        w->set_color(128, 128, 128);
    }
    
    shield * s = new shield();
    s->set_orig(16, 16);
    s->set_scale(2.5, 2.5);
    s->set_pos(320, inventorySprite.getPosition().y);
    if(game->get_shield() == false){
        s->set_color(128, 128, 128);
    }
    
    bool breakLoop = false;
    while(NULL == NULL){
        if(breakLoop ==  true){
            break;
        }
        sf::Event event;
        while(window->pollEvent(event)){
            if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::A:
                        a_pressed(selector);
                        break;
                    case sf::Keyboard::D:
                        d_pressed(selector);
                        break;
                    case sf::Keyboard::E:
                        closeInventory = true;
                        break;
                    case sf::Keyboard::S:
                        if(selector->get_sprite().getPosition().x == 410){
                            closeInventory = true;
                        } else if (selector->get_sprite().getPosition().x == 320 && game->get_shield() == true){
                            game->set_shield(false);
                            game->set_active_shield(true);
                            closeInventory = true;
                        } else if (selector->get_sprite().getPosition().x == 230 && game->get_wall() == true){
                            game->set_wall(false);
                            game->set_active_wall(true);
                            closeInventory = true;
                        } else if (selector->get_sprite().getPosition().x == 140 && game->get_freeze() == true){
                            game->set_freeze(false);
                            game->set_active_freeze(true);
                            closeInventory = true;
                        } else if (selector->get_sprite().getPosition().x == 50 && game->get_bomb() == true){
                            game->set_bomb(false);
                            game->set_active_bomb(true);
                            closeInventory = true;
                        } else {
                            NULL;
                        }
                        break;
                    default:
                        break;
                }
            } else if(event.type == sf::Event::Closed){
                window->close();
            }
        }
        if(closeInventory == false){
            if(inventorySprite.getPosition().x <= 410){
                inventorySprite.move(sf::Vector2f(0.25, 0));
            } else {
                inventorySprite.move(sf::Vector2f(0, 0));
            }
            
            if(inventorySprite.getPosition().x >= 50){
                drawBomb = true;
            }
            if(inventorySprite.getPosition().x >= 140){
                drawFreeze = true;
            }
            if(inventorySprite.getPosition().x >= 230){
                drawWall = true;
            }
            if(inventorySprite.getPosition().x >= 320){
                drawShield = true;
            }
            if(inventorySprite.getPosition().x >= 410){
                drawSelector = true;
            }
        }
        
        if(closeInventory == true){
            drawSelector = false;
            if(inventorySprite.getPosition().x >= 50){
                inventorySprite.move(sf::Vector2f(-0.25, 0));
            } else {
                inventorySprite.move(sf::Vector2f(0, 0));
                breakLoop = true;
            }
            if(inventorySprite.getPosition().x <= 50){
                drawBomb = false;
            }
            if(inventorySprite.getPosition().x <= 140){
                drawFreeze = false;
            }
            if(inventorySprite.getPosition().x <= 230){
                drawWall = false;
            }
            if(inventorySprite.getPosition().x <= 320){
                drawShield = false;
            }
        }
        
        window->clear();
        for(snake_part * snakePart : snake->get_snake_parts()){
            window->draw(snakePart->get_sprite());
        }
        for(bot * bot : *bots){
            for(snake_part * snakePart : bot->get_snake()->get_snake_parts()){
                window->draw(snakePart->get_sprite());
            }
        }
        window->draw(food->get_sprite());
        window->draw(superfood->get_sprite());
        window->draw(mysteryBox->get_sprite());
        window->draw(level->getText());
        window->draw(score->getText());
        window->draw(levelUp1->getText());
        window->draw(levelUp2->getText());
        if(drawBomb == true){
            window->draw(b->get_sprite());
        }
        if(drawFreeze == true){
            window->draw(f->get_sprite());
        }
        if(drawWall == true){
            window->draw(w->get_sprite());
        }
        if(drawShield == true){
            window->draw(s->get_sprite());
        }
        window->draw(inventorySprite);
        if(drawSelector == true){
            selectorTime = selectorClock.getElapsedTime().asSeconds();
            if(selectorTime > 0.5){
                if(selectorTime < 1){
                    window->draw(selector->get_sprite());
                } else {
                    selectorClock.restart();
                }
            }
        }
        window->display();
    }
    game->go_playing();
}



#endif /* selecting_power_up_hpp */
