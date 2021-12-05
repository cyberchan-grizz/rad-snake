//
//  gameplay.hpp
//  Snake
//
//  Created by Channing Christian on 3/19/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef gameplay_hpp
#define gameplay_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "snake.hpp"
#include "food.hpp"
#include "mystery_box.hpp"
#include "game.hpp"
#include "textBox.hpp"
#include "bots.hpp"
#include "audio_manager.hpp"

using namespace std;

void pressed_w(snake * snake){
    if(snake->get_snake_parts()[0]->get_movement().x > 0){ // if the snake is moving to the right
        snake->move_left();
    } else if (snake->get_snake_parts()[0]->get_movement().x < 0){ // if the snake is moving to the left
        snake->move_right();
    } else {
        NULL;
    }
}

void pressed_s(snake * snake){
    if(snake->get_snake_parts()[0]->get_movement().x > 0){ // if the snake is moving to the right
        snake->move_right();
    } else if (snake->get_snake_parts()[0]->get_movement().x < 0){ // if the snake is moving to the left
        snake->move_left();
    } else {
        NULL;
    }
}

void pressed_a(snake * snake){
    if(snake->get_snake_parts()[0]->get_movement().y > 0){ // if the snake is moving down
        snake->move_right();
    } else if (snake->get_snake_parts()[0]->get_movement().y < 0){ // if the snake is moving up
        snake->move_left();
    } else {
        NULL;
    }
}

void pressed_d(snake * snake){
    if(snake->get_snake_parts()[0]->get_movement().y > 0) { // if the snake is moving down
        snake->move_left();
    } else if (snake->get_snake_parts()[0]->get_movement().y < 0) { // if the snake is moving up
        snake->move_right();
    } else {
        NULL;
    }
}

void level_up_method(text_box * levelUp1, text_box * levelUp2, game * game, audio_manager * am){
    if(levelUp1->getText().getPosition().x <= 200){
        levelUp1->movement(sf::Vector2f(1.2, 0));
    } else if(levelUp1->getText().getPosition().x <= 300){
        if(levelUp1->get_movement().x >= 1){
            levelUp1->movement(sf::Vector2f(sqrt(levelUp1->get_movement().x), 0));
            if(levelUp1->get_movement().x <= 1){
                levelUp1->movement(sf::Vector2f(0.9, 0));
            }
        } else if(levelUp1->get_movement().x < 1 && levelUp1->get_movement().x > 0.1){
            levelUp1->movement(sf::Vector2f(pow(levelUp1->get_movement().x, 2), 0));
        } else if(levelUp1->get_movement().x <= 0.1){
            levelUp1->movement(sf::Vector2f(0.1, 0));
        }
    } else {
        if(levelUp1->get_movement().x < 1){
            levelUp1->movement(sf::Vector2f(sqrt(levelUp1->get_movement().x), 0));
        } else if (levelUp1->get_movement().x >= 1){
            levelUp1->movement(sf::Vector2f(1.2, 0));
        }
    }
    
    if(levelUp1->getText().getPosition().x >= 225){
        if(levelUp2->getText().getPosition().x >= 500){
            levelUp2->movement(sf::Vector2f(-1.2, 0));
        } else if(levelUp2->getText().getPosition().x >= 400){
            if(-levelUp2->get_movement().x >= 1){
                levelUp2->movement(sf::Vector2f(-sqrt(-levelUp2->get_movement().x), 0));
                if(-levelUp2->get_movement().x <= 1){
                    levelUp2->movement(sf::Vector2f(-0.9, 0));
                }
            } else if(-levelUp2->get_movement().x < 1 && -levelUp2->get_movement().x > 0.1){
                levelUp2->movement(sf::Vector2f(-pow(levelUp2->get_movement().x, 2), 0));
            } else if(-levelUp2->get_movement().x <= 0.1){
                levelUp2->movement(sf::Vector2f(-0.1, 0));
            }
        } else if (levelUp2->getText().getPosition().x < 400){
            if(-levelUp2->get_movement().x < 1){
                levelUp2->movement(sf::Vector2f(-sqrt(-levelUp2->get_movement().x), 0));
            } else if (-levelUp2->get_movement().x >= 1){
                levelUp2->movement(sf::Vector2f(-1.2, 0));
            }
        }
    }
    
    if(levelUp1->getText().getPosition().x > 1300){
        levelUp1->movement(sf::Vector2f(0, 0));
    }
    if(levelUp2->getText().getPosition().x < -300){
        levelUp2->movement(sf::Vector2f(0, 0));
        levelUp1->set_pos(-300, levelUp1->getText().getPosition().y);
        levelUp2->set_pos(1300, levelUp2->getText().getPosition().y);
        game->set_level_up(false);
        am->play_level_up();
    }
}

void gameplay(game * game, sf::RenderWindow * window, snake * snake, food * food, super_food * superFood, mystery_box * mysteryBox, text_box * level, text_box * score, text_box * levelUp1, text_box * levelUp2, std::vector<bot*> * bots, sf::Sprite inventorySprite, audio_manager * am){
    bool breakLoop = false;
    bool addedBot = false;
    
    sf::Sprite wallSprite;
    sf::Texture wallTexture;
    wallTexture.loadFromFile("Textures/barrier.png");
    wallSprite.setTexture(wallTexture);
    wallSprite.setOrigin(16, 16);
    wallSprite.setScale(33, 33);
    wallSprite.setPosition(500, 500);
    
    sf::Clock clock;
    double time;
    
    sf::Clock shieldClock;
    double shieldTime;
    
    sf::Clock wallClock;
    double wallTime;
    
    sf::Clock freezeClock;
    double freezeTime;
    
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
                        switch(event.key.code){
                            case sf::Keyboard::W:
                                pressed_w(snake);
                                break;
                            case sf::Keyboard::S:
                                pressed_s(snake);
                                break;
                            case sf::Keyboard::A:
                                pressed_a(snake);
                                break;
                            case sf::Keyboard::D:
                                pressed_d(snake);
                                break;
                            case sf::Keyboard::E:
                                game->go_selecting_power_up();
                                breakLoop = true;
                                break;
                            default:
                                NULL;
                                break;
                        }
                    } else if(event.type == sf::Event::Closed){
                        window->close();
                    }
                }
                if(game->get_level() > 5){
                    if(game->get_level() % 2 == 0){
                        if((snake->get_snake_parts().size() - 5 <= 0)){
                            while(bots->size() < ((int)(game->get_level() - 6) / 2) + 1){
                                bots->push_back(new bot());
                            }
                        }
                    }
                }
                
                if(game->get_active_freeze() == true){
                    freezeTime = freezeClock.getElapsedTime().asSeconds();
                    if(freezeTime > 10){
                        game->set_active_freeze(false);
                    }
                } else {
                    freezeClock.restart();
                }
                
                if(game->get_active_shield() == true){
                    shieldTime = shieldClock.getElapsedTime().asSeconds();
                    if(shieldTime > 10){
                        game->set_active_shield(false);
                    }
                } else {
                    shieldClock.restart();
                }
                
                if(game->get_active_wall() == true){
                    wallTime = wallClock.getElapsedTime().asSeconds();
                    if(wallTime > 10){
                        game->set_active_wall(false);
                    }
                } else {
                    wallClock.restart();
                }
                
                if(game->get_active_level_up_mb() == true){
                    game->inc_level();
                    game->set_level_up(true);
                    game->set_active_level_up_mb(false);
                }
                
                if(game->get_active_poison() == true){
                    snake->remove_snake_tail();
                    game->set_active_poison(false);
                }
                
                if(game->get_active_bomb() == true){
                    snake->remove_snake_tail();
                    superFood->eat_food();
                    food->eat_food();
                    mysteryBox->eat_mystery_box();
                    for(bot * bot : *bots){
                        bot->get_snake()->remove_snake_tail();
                    }
                    game->set_active_bomb(false);
                }
                
                if(superFood->get_eaten() == true && game->get_level() >= 2){
                    superFood->spawn_food();
                }
                
                if(mysteryBox->get_eaten() == true && game->get_level() >= 4){
                    mysteryBox->spawn_mystery_box();
                }
                
                if(snake->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(food->get_sprite().getGlobalBounds())){
                    food->eat_food();
                    snake->add_snake_part();
                    score->set_string("Score: " + std::to_string(snake->get_snake_parts().size() - 5));
                    am->play_ping();
                }
                
                if(snake->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(superFood->get_sprite().getGlobalBounds())){
                    superFood->eat_food();
                    snake->add_snake_part();
                    snake->add_snake_part();
                    score->set_string("Score: " + std::to_string(snake->get_snake_parts().size() - 5));
                    am->play_ping();
                }
                
                if(snake->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(mysteryBox->get_sprite().getGlobalBounds())){
                    mysteryBox->eat_mystery_box();
                    game->go_opening_mystery_box();
                    am->play_level_up();
                    break;
                }
                
                if(snake->get_snake_parts().size() - 5 >= 10 + game->get_level()){
                    game->inc_level();
                    game->set_level_up(true);
                    level->set_string("Level: " + std::to_string(game->get_level()));
                    snake->remove_snake_tail();
                    score->set_string("Score: " + std::to_string(snake->get_snake_parts().size() - 5));
                }
                
                if(game->get_level_up() == true){
                    level_up_method(levelUp1, levelUp2, game, am);
                }
                
                snake->update_snake_movement();
                if(game->get_active_freeze() == false){
                    mysteryBox->movement(mysteryBox->get_movement());
                }
                for(int i = 0; i < bots->size(); i++){
                    if(bots->at(i)->get_dead() == true){
                        delete bots->at(i);
                        bots->erase(bots->begin() + i);
                        game->inc_bot_kill();
                    }
                }
                window->clear();
                window->draw(inventorySprite);
                if(game->get_active_wall() == true){
                    window->draw(wallSprite);
                }
                window->draw(level->getText());
                window->draw(score->getText());
                for(int n = 0; n < snake->get_snake_parts().size(); n++){
                    snake_part * snakePart = snake->get_snake_parts()[n];
                    if(game->get_active_shield() == true){
                        snakePart->set_color(138, 232, 255);
                    } else {
                        snakePart->set_color(255, 255, 255);
                    }
                    for(bot * bot : *bots){
                        if(bot->get_snake()->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(snakePart->get_sprite().getGlobalBounds()) && n != 0){
                            bot->kill_bot();
                        }
                    }
                    if(n != 0 && n != 1 && n != 2){
                        if(snake->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(snakePart->get_sprite().getGlobalBounds()) && snake->get_snake_parts()[0]->get_movement() != snakePart->get_movement()){
                            breakLoop = true;
                            game->go_end_screen();
                        }
                    }
                    if(snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0 && game->get_active_wall() == false){
                        snakePart->set_pos(1010, snakePart->get_sprite().getPosition().y);
                    } else if(snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0 && game->get_active_wall() == false){
                        snakePart->set_pos(-10, snakePart->get_sprite().getPosition().y);
                    } else if (snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0 && game->get_active_wall() == true){
                        game->go_end_screen();
                        breakLoop = true;
                    } else if (snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0 && game->get_active_wall() == false){
                        game->go_end_screen();
                        breakLoop = true;
                    }
                    
                    if(snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0 && game->get_active_wall() == false){
                        snakePart->set_pos(snakePart->get_sprite().getPosition().x, 1010);
                    } else if(snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0 && game->get_active_wall() == false){
                        snakePart->set_pos(snakePart->get_sprite().getPosition().x, -10);
                    } else if (snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0 && game->get_active_wall() == true){
                        game->go_end_screen();
                        breakLoop = true;
                    } else if (snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0 && game->get_active_wall() == true){
                        game->go_end_screen();
                        breakLoop = true;
                    }
                    window->draw(snakePart->get_sprite());
                    snakePart->movement(snakePart->get_movement());
                }
                if(bots->size() > 0){
                    for(bot * bot : *bots){
                        if(bot->get_snake()->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(food->get_sprite().getGlobalBounds())){
                            bot->get_snake()->add_snake_part();
                            food->eat_food();
                        }
                        if(bot->get_snake()->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(superFood->get_sprite().getGlobalBounds())){
                            bot->get_snake()->add_snake_part();
                            bot->get_snake()->add_snake_part();
                            superFood->eat_food();
                        }
                        if(game->get_active_freeze() == false){
                            bot->update();
                        }
                        for(int n = 0; n < bot->get_snake()->get_snake_parts().size(); n++){
                            snake_part * snakePart = bot->get_snake()->get_snake_parts()[n];
                            if(snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0 && game->get_active_wall() == false){
                                snakePart->set_pos(1010, snakePart->get_sprite().getPosition().y);
                            } else if(snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0 && game->get_active_wall() == false){
                                snakePart->set_pos(-10, snakePart->get_sprite().getPosition().y);
                            } else if (snakePart->get_sprite().getPosition().x <= -10 && snakePart->get_movement().x < 0 && game->get_active_wall() == true){
                                bot->kill_bot();
                            } else if (snakePart->get_sprite().getPosition().x >= 1010 && snakePart->get_movement().x > 0 && game->get_active_wall() == false){
                                bot->kill_bot();
                            }
                            
                            if(snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0 && game->get_active_wall() == false){
                                snakePart->set_pos(snakePart->get_sprite().getPosition().x, 1010);
                            } else if(snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0 && game->get_active_wall() == false){
                                snakePart->set_pos(snakePart->get_sprite().getPosition().x, -10);
                            } else if (snakePart->get_sprite().getPosition().y <= -10 && snakePart->get_movement().y < 0 && game->get_active_wall() == true){
                                bot->kill_bot();
                            } else if (snakePart->get_sprite().getPosition().y >= 1010 && snakePart->get_movement().y > 0 && game->get_active_wall() == true){
                                bot->kill_bot();
                            }
                            window->draw(snakePart->get_sprite());
                            if(game->get_active_freeze() == false){
                                snakePart->movement(snakePart->get_movement());
                            }
                            if(snake->get_snake_parts()[0]->get_sprite().getGlobalBounds().intersects(snakePart->get_sprite().getGlobalBounds()) && game->get_active_shield() == false && n != 0){
                                game->go_end_screen();
                                breakLoop = true;
                            }
                        }
                    }
                }
                window->draw(food->get_sprite());
                if(superFood->get_eaten() == false){
                    if(game->get_active_freeze() == false){
                        superFood->update_food();
                    }
                    window->draw(superFood->get_sprite());
                }
                if(mysteryBox->get_eaten() == false){
                    mysteryBox->update_mystery_box();
                    window->draw(mysteryBox->get_sprite());
                }
                if(game->get_level_up() == true){
                    window->draw(levelUp1->getText());
                    window->draw(levelUp2->getText());
                }
                window->display();
            } else {
                clock.restart();
            }
        }
    }
}

#endif /* gameplay_hpp */
