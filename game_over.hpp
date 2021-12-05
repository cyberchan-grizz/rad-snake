//
//  game_over.hpp
//  Snake
//
//  Created by Channing Christian on 3/31/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef game_over_hpp
#define game_over_hpp

#include "snake.hpp"
#include "gameplay.hpp"
#include "food.hpp"
#include "mystery_box.hpp"
#include "open_mystery_box.hpp"
#include "game.hpp"
#include "bots.hpp"
#include "selecting_power_up.hpp"
#include "start_screen.hpp"

#include <stdio.h>
#include <iostream>


void game_over(game * g, sf::RenderWindow * window, snake * snake, food * food, super_food * superFood, mystery_box * mysteryBox, text_box * level, text_box * score, text_box * levelUp1, text_box * levelUp2, std::vector<bot*> * bots, sf::Sprite inventorySprite, audio_manager * am){
    bool breakLoop = false;
    
    am->play_game_over();
    text_box * game = new text_box("game");
    game->set_size(3);
    game->set_pos(400, -100);
    
    text_box * over = new text_box("over");
    over->set_size(3);
    over->set_pos(400, 1100);
    
    text_box * cont = new text_box("press any button to continue");
    cont->set_size(2);
    cont->set_pos(10, 600);
    
    sf::Clock contClock;
    double contTime;
    
    while(NULL == NULL){
        if(breakLoop == true){
            break;
        }
        sf::Event event;
        while(window->pollEvent(event)){
            if(event.type == sf::Event::KeyPressed){
                breakLoop = true;
            } else if(event.type == sf::Event::Closed){
                window->close();
            }
        }
        
        if(game->getText().getPosition().y <= 400){
            game->movement(sf::Vector2f(0, 0.25));
        } else {
            game->movement(sf::Vector2f(0, 0));
        }
        
        if(over->getText().getPosition().y >= 500){
            over->movement(sf::Vector2f(0, -0.25));
        } else {
            over->movement(sf::Vector2f(0, 0));
        }
        
        window->clear();
        if(food->get_sprite().getScale().x > 0 && food->get_sprite().getScale().y > 0){
            food->set_scale(food->get_sprite().getScale().x - 0.001, food->get_sprite().getScale().y - 0.001);
            window->draw(food->get_sprite());
        } else {
            food->set_pos(-100, -100);
        }
        
        if(superFood->get_sprite().getScale().x > 0 && superFood->get_sprite().getScale().y > 0){
            superFood->set_scale(superFood->get_sprite().getScale().x - 0.001, superFood->get_sprite().getScale().y - 0.001);
            window->draw(superFood->get_sprite());
        } else {
            superFood->set_pos(-100, -100);
        }
        
        if(mysteryBox->get_sprite().getScale().x > 0 && mysteryBox->get_sprite().getScale().y > 0){
            mysteryBox->set_scale(mysteryBox->get_sprite().getScale().x - 0.001, mysteryBox->get_sprite().getScale().y - 0.001);
            window->draw(mysteryBox->get_sprite());
        }
        window->draw(level->getText());
        window->draw(score->getText());
        for(bot * bot : *bots){
            if(bot->get_dead() == false){
                bot->update();
                bot->kill_bot();
                for(snake_part * snakePart : bot->get_snake()->get_snake_parts()){
                    window->draw(snakePart->get_sprite());
                }
            }
        }
        if(snake->get_snake_parts().size() != 0){
            snake->die();
            snake->update_snake_movement();
            for(snake_part * snakePart : snake->get_snake_parts()){
                window->draw(snakePart->get_sprite());
            }
        }
        window->draw(inventorySprite);
        window->draw(game->getText());
        window->draw(over->getText());
        if(game->get_movement().x == 0 && game->get_movement().y == 0 && over->get_movement().x == 0 && over->get_movement().y == 0){
            contTime = contClock.getElapsedTime().asSeconds();
            if(contTime >= 0.5){
                if(contTime <= 1){
                    window->draw(cont->getText());
                } else {
                    contClock.restart();
                }
            }
        }
        window->display();
    }
    delete game;
    delete over;
    g->go_title_screen();
}

#endif /* game_over_hpp */
