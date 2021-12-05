//
//  start_screen.hpp
//  Snake
//
//  Created by Channing Christian on 3/31/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef start_screen_hpp
#define start_screen_hpp

#include "textBox.hpp"
#include "snake.hpp"
#include "bots.hpp"
#include "game.hpp"
#include "audio_manager.hpp"

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

void start_screen(game * game, sf::RenderWindow * window, audio_manager * audioManager){
    bool breakLoop = false;
    
    bot * bot1 = new bot();
    bot * bot2 = new bot();
    bot * bot3 = new bot();
    
    text_box * title = new text_box("snake");
    title->set_size(4);
    title->set_pos(320, 300);
    
    text_box * startGame = new text_box("press any button to play");
    startGame->set_size(2);
    startGame->set_pos(85, 450);
    
    text_box * credits = new text_box("BearBox Studios");
    credits->set_size(1);
    credits->set_pos(0, 0);
    
    sf::Clock startGameClock;
    double startGameTime;
    
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
        bot1->update();
        bot2->update();
        bot3->update();
        window->clear();
        for(snake_part * snakePart : bot1->get_snake()->get_snake_parts()){
            if(snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0){
                snakePart->set_pos(1010, snakePart->get_sprite().getPosition().y);
            } else if(snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0){
                snakePart->set_pos(-10, snakePart->get_sprite().getPosition().y);
            }
            
            if(snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0){
                snakePart->set_pos(snakePart->get_sprite().getPosition().x, 1010);
            } else if(snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0){
                snakePart->set_pos(snakePart->get_sprite().getPosition().x, -10);
            }
            
            snakePart->movement(snakePart->get_movement());
            window->draw(snakePart->get_sprite());
        }
        for(snake_part * snakePart : bot2->get_snake()->get_snake_parts()){
            if(snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0){
                snakePart->set_pos(1010, snakePart->get_sprite().getPosition().y);
            } else if(snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0){
                snakePart->set_pos(-10, snakePart->get_sprite().getPosition().y);
            }
            
            if(snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0){
                snakePart->set_pos(snakePart->get_sprite().getPosition().x, 1010);
            } else if(snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0){
                snakePart->set_pos(snakePart->get_sprite().getPosition().x, -10);
            }
            
            snakePart->movement(snakePart->get_movement());
            window->draw(snakePart->get_sprite());
        }
        for(snake_part * snakePart : bot3->get_snake()->get_snake_parts()){
            if(snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0){
                snakePart->set_pos(1010, snakePart->get_sprite().getPosition().y);
            } else if(snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0){
                snakePart->set_pos(-10, snakePart->get_sprite().getPosition().y);
            }
            
            if(snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0){
                snakePart->set_pos(snakePart->get_sprite().getPosition().x, 1010);
            } else if(snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0){
                snakePart->set_pos(snakePart->get_sprite().getPosition().x, -10);
            }
            
            snakePart->movement(snakePart->get_movement());
            window->draw(snakePart->get_sprite());
        }
        window->draw(title->getText());
        window->draw(credits->getText());
        startGameTime = startGameClock.getElapsedTime().asSeconds();
        if(startGameTime > 0.5){
            if(startGameTime < 1){
                window->draw(startGame->getText());
            } else {
                startGameClock.restart();
            }
        }
        window->display();
        
    }
    delete title;
    delete startGame;
    delete credits;
    bot1->kill_bot();
    while(bot1->get_snake()->get_snake_parts().size() > 0){
        bot1->update();
    }
    delete bot1;
    
    bot2->kill_bot();
    while(bot2->get_snake()->get_snake_parts().size() > 0){
        bot2->update();
    }
    delete bot2;
    
    bot3->kill_bot();
    while(bot3->get_snake()->get_snake_parts().size() > 0){
        bot3->update();
    }
    delete bot3;
    
    audioManager->stop_music();
    game->go_playing();
}

#endif /* start_screen_hpp */
