//
//  snake.cpp
//  Snake
//
//  Created by Channing Christian on 3/17/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "snake.hpp"


//Turning Point Class
turning_point::turning_point(double xCord, double yCord){
    this->xCord = xCord;
    this->yCord = yCord;
    this->turnDirection = "right";
}

void turning_point::left_turn(){
    this->turnDirection = "left";
}

void turning_point::right_turn(){
    this->turnDirection = "right";
}

double turning_point::get_x_cord(){
    return this->xCord;
}

double turning_point::get_y_cord(){
    return this->yCord;
}

std::string turning_point::get_turn_direction(){
    return this->turnDirection;
}


//Snake Part Class
snake_part::snake_part(int xCord, int yCord){
    this->xCord = xCord;
    this->yCord = yCord;
    
    this->texture.loadFromFile("Textures/snake_part.png");
    this->sprite.setTexture(texture);
    
    this->set_pos(this->xCord, this->yCord);
    this->set_orig(100, 100);
    this->set_scale(0.2, 0.2);
}

void snake_part::set_orig(double x, double y){
    this->sprite.setOrigin(x, y);
}

void snake_part::set_scale(double x, double y){
    this->sprite.setScale(x, y);
}

void snake_part::set_pos(double x, double y){
    this->sprite.setPosition(x, y);
}

void snake_part::movement(sf::Vector2f movementVector){
    this->movementVector = movementVector;
    this->sprite.move(this->movementVector);
}

sf::Vector2f snake_part::get_movement(){
    return this->movementVector;
}

sf::Sprite snake_part::get_sprite(){
    return sprite;
}

void snake_part::add_turning_point(turning_point tp){
    this->turningPoints.push_back(tp);
}

void snake_part::delete_first_turning_point(){
    this->turningPoints.erase(this->turningPoints.begin());
}

std::vector<turning_point> snake_part::get_turning_points(){
    return turningPoints;
}

void snake_part::set_color(int num1, int num2, int num3){
    this->sprite.setColor(sf::Color(num1, num2, num3));
}

//Snake Class
snake::snake(int xCord, int yCord){
    this->xCord = xCord;
    this->yCord = yCord;
    this->snakeSpeed = 0.25f;
    snake_part * newSnakePart = new snake_part(this->xCord, this->yCord);
    newSnakePart->movement(sf::Vector2f(0, -this->snakeSpeed));
    this->snakeParts.push_back(newSnakePart);
    for(int i = 0; i < 4; i++){
        this->add_snake_part();
    }
    this->dead = false;
}

void snake::move_left(){
    turning_point tp(this->get_snake_parts()[0]->get_sprite().getPosition().x, this->get_snake_parts()[0]->get_sprite().getPosition().y);
    tp.left_turn();
    for(snake_part * sp : this->snakeParts){
        sp->add_turning_point(tp);
    }
}

void snake::move_right(){
    turning_point tp(this->get_snake_parts()[0]->get_sprite().getPosition().x, this->get_snake_parts()[0]->get_sprite().getPosition().y);
    tp.right_turn();
    for(snake_part * sp : this->snakeParts){
        sp->add_turning_point(tp);
    }
}

void snake::update_snake_movement(){
    if(this->dead == false){
        for(int i = 0; i < this->snakeParts.size(); i++){
            if (this->snakeParts[i]->get_turning_points().size() != 0) {
                if(this->snakeParts[i]->get_movement().x > 0 && this->snakeParts[i]->get_sprite().getPosition().x >= this->snakeParts[i]->get_turning_points()[0].get_x_cord() && this->snakeParts[i]->get_sprite().getPosition().x <= this->snakeParts[i]->get_turning_points()[0].get_x_cord() + 5){ // if the snake part is moving to the right
                    if(this->snakeParts[i]->get_turning_points()[0].get_turn_direction() == "right"){
                        this->snakeParts[i]->movement(sf::Vector2f(0, this->snakeSpeed));
                    } else {
                        this->snakeParts[i]->movement(sf::Vector2f(0, -this->snakeSpeed));
                    }
                    this->snakeParts[i]->delete_first_turning_point();
                } else if (this->snakeParts[i]->get_movement().x < 0 && this->snakeParts[i]->get_sprite().getPosition().x <= this->snakeParts[i]->get_turning_points()[0].get_x_cord() && this->snakeParts[i]->get_sprite().getPosition().x >= this->snakeParts[i]->get_turning_points()[0].get_x_cord() - 5){ // if the snake part is moving to the left
                    if(this->snakeParts[i]->get_turning_points()[0].get_turn_direction() == "right"){
                        this->snakeParts[i]->movement(sf::Vector2f(0, -this->snakeSpeed));
                    } else {
                        this->snakeParts[i]->movement(sf::Vector2f(0, this->snakeSpeed));
                    }
                    this->snakeParts[i]->delete_first_turning_point();
                } else if (this->snakeParts[i]->get_movement().y > 0 && this->snakeParts[i]->get_sprite().getPosition().y >= this->snakeParts[i]->get_turning_points()[0].get_y_cord() && this->snakeParts[i]->get_sprite().getPosition().y <= this->snakeParts[i]->get_turning_points()[0].get_y_cord() + 5){ // if the snake part is moving down
                    if(this->snakeParts[i]->get_turning_points()[0].get_turn_direction() == "right"){
                        this->snakeParts[i]->movement(sf::Vector2f(-this->snakeSpeed, 0));
                    } else {
                        this->snakeParts[i]->movement(sf::Vector2f(this->snakeSpeed, 0));
                    }
                    this->snakeParts[i]->delete_first_turning_point();
                } else if (this->snakeParts[i]->get_movement().y < 0 && this->snakeParts[i]->get_sprite().getPosition().y <= this->snakeParts[i]->get_turning_points()[0].get_y_cord() && this->snakeParts[i]->get_sprite().getPosition().y >= this->snakeParts[i]->get_turning_points()[0].get_y_cord() - 5){ // if the snake part is moving up
                    if(this->snakeParts[i]->get_turning_points()[0].get_turn_direction() == "right"){
                        this->snakeParts[i]->movement(sf::Vector2f(this->snakeSpeed, 0));
                    } else {
                        this->snakeParts[i]->movement(sf::Vector2f(-this->snakeSpeed, 0));
                    }
                    this->snakeParts[i]->delete_first_turning_point();
                }
            }
        }
    } else {
        for(int i = 0; i < this->snakeParts.size(); i++){
            snake_part * snakePart = this->snakeParts[i];
            snakePart->movement(sf::Vector2f(0, 0));
            snakePart->set_scale(snakePart->get_sprite().getScale().x - 0.001, snakePart->get_sprite().getScale().y - 0.001);
        }
        if(snakeParts[snakeParts.size() - 1]->get_sprite().getScale().x <= 0 && snakeParts[snakeParts.size() - 1]->get_sprite().getScale().y <= 0){
            while(snakeParts.size() > 0){
                delete snakeParts[0];
                snakeParts.erase(snakeParts.begin());
            }
        }
    }
}

void snake::add_snake_part(){
    int x;
    int y;
    if(this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_movement().x > 0){ // if the snake is moving to the right
        x = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().x - (200 * 0.2);
        y = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().y;
    } else if (this->get_snake_parts()[this->get_snake_parts().size()-1]->get_movement().x < 0){ // if the snake is moving to the left
        x = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().x + (200 * 0.2);
        y = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().y;
    } else if (this->get_snake_parts()[this->get_snake_parts().size() -1]->get_movement().y > 0){ // if the snake is moving down
        x = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().x;
        y = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().y - (200 * 0.2);
    } else if (this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_movement().y < 0){ // if the snaks is moving up
        x = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().x;
        y = this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_sprite().getPosition().y + (200 * 0.2);
        
    }
    snake_part * sp = new snake_part(x, y);
    sp->set_color(this->colorR, this->colorG, this->colorB);
    sp->movement(this->get_snake_parts()[this->get_snake_parts().size() - 1]->get_movement());
    for(turning_point tp : this->snakeParts[this->snakeParts.size() - 1]->get_turning_points()){
        sp->add_turning_point(tp);
    }
    this->snakeParts.push_back(sp);
}

void snake::remove_snake_tail(){
    while(this->snakeParts.size() > 5){
        delete this->snakeParts[5];
        this->snakeParts.erase(this->snakeParts.begin() + 5);
    }
}

void snake::die(){
    this->dead = true;
}

std::vector<snake_part*> snake::get_snake_parts(){
    return this->snakeParts;
}

void snake::change_color(int r, int g, int b){
    this->colorR = r;
    this->colorG = g;
    this->colorB = b;
}

