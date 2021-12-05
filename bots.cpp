//
//  bots.cpp
//  Snake
//
//  Created by Channing Christian on 3/24/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "bots.hpp"

bot::bot(){
    this->dead = false;
    this->die = false;
    int x;
    int y;
    if((rand() % 2 + 1) == 1){ // this chooses whether the snake comes from the top/bottom or left/right
        y = 1005;
        x = rand() % 900 + 50;
    } else {
        if((rand() % 2 + 1) == 1){ // this chooses whether the snake comes from the left or right
            x = -5;
        } else {
            x = 1005;
        }
        y = rand() % 900 + 50;
    }
    this->snake = new class snake(x, y);
    int r = rand() % 255 + 1;
    int g = rand() % 255 + 1;
    int b = rand() % 255 + 1;
    this->snake->change_color(r, g, b);
    for(snake_part * snakePart : this->snake->get_snake_parts()){
        snakePart->set_color(r, g, b);
    }
    if(x < 0){
        this->snake->move_right();
    } else if (x > 1000){
        this->snake->move_left();
    }
    
    if(y < 0){
        snake->move_left();
        snake->move_left();
    }
}

void bot::kill_bot(){
    this->die = true;
}

void bot::update(){
    if(this->die == false){
        if(this->get_snake()->get_snake_parts()[0]->get_sprite().getPosition().x > 0 && this->get_snake()->get_snake_parts()[0]->get_sprite().getPosition().x < 1000 && this->get_snake()->get_snake_parts()[0]->get_sprite().getPosition().y > 0 && this->get_snake()->get_snake_parts()[0]->get_sprite().getPosition().y < 1000){
            if(rand() % 7500 == 0){
                if(rand() % 2 == 0){
                    this->snake->move_left();
                } else {
                    this->snake->move_right();
                }
            }
        }
        this->snake->update_snake_movement();
    } else {
        snake->die();
        this->snake->update_snake_movement();
        if(this->snake->get_snake_parts().size() == 0){
            this->dead = true;
            delete this->snake;
        }
    }
}

bool bot::get_dead(){
    return this->dead;
}

snake * bot::get_snake(){
    return this->snake;
}
