//
//  food.cpp
//  Snake
//
//  Created by Channing Christian on 3/20/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "food.hpp"

//Food Class
food::food(){
    this->texture.loadFromFile("Textures/snake_part.png");
    this->sprite.setTexture(this->texture);
    this->set_orig(100, 100);
    this->set_scale(0.2, 0.2);
    this->set_pos(rand() % 1000 + 1, rand() % 1000 + 1);
}

void food::set_pos(double x, double y){
    this->sprite.setPosition(x, y);
}

void food::set_orig(double x, double y){
    this->sprite.setOrigin(x, y);
}

void food::set_scale(double x, double y){
    this->sprite.setScale(x, y);
}

void food::eat_food(){
    this->set_pos(rand() % 900 + 50, rand() % 900 + 50);
}

void food::movement(sf::Vector2f movementVector){
    this->movementVector = movementVector;
    this->sprite.move(this->movementVector);
    
    if(this->sprite.getPosition().y > 1020){
        this->movementVector = sf::Vector2f(0, 0);
        this->sprite.move(this->movementVector);
        this->eat_food();
    }
}

sf::Vector2f food::get_movement(){
    return this->movementVector;
}

sf::Sprite food::get_sprite(){
    return this->sprite;
}

super_food::super_food() {
    this->anamation = new Anamation(10, 32, 32, 128, 96);
    this->texture.loadFromFile("Textures/super_food.png");
    this->sprite.setTexture(this->texture);
    this->set_orig(16, 16);
    this->set_scale(2, 2);
    this->set_pos(-200, -200);
    this->spawn_food();
    this->set_frame(this->anamation->getFrame(0));
    this->count = 0;
}

void super_food::set_pos(double x, double y){
    this->sprite.setPosition(x, y);
}

void super_food::set_orig(double x, double y){
    this->sprite.setOrigin(x, y);
}

void super_food::set_scale(double x, double y){
    this->sprite.setScale(x, y);
}

void super_food::movement(sf::Vector2f movementVector){
    this->movementVector = movementVector;
    this->sprite.move(movementVector);
}

sf::Vector2f super_food::get_movement(){
    return this->movementVector;
}

void super_food::set_frame(sf::IntRect frame){
    this->sprite.setTextureRect(frame);
}

sf::Sprite super_food::get_sprite(){
    return this->sprite;
}

Anamation * super_food::get_anamation(){
    return this->anamation;
}

void super_food::update_food(){
    this->time = this->clock.getElapsedTime().asSeconds();
    if(this->time >= 1){
        if(this->count < this->get_anamation()->getAnamationLength() - 1){
            this->count++;
            this->set_scale(this->sprite.getScale().x - 0.2, this->sprite.getScale().y - 0.2);
        } else {
            this->count = 0;
            this->eaten = true;
        }
        this->clock.restart();
    }
    this->set_frame(this->get_anamation()->getFrame(count));
}

void super_food::eat_food(){
    this->eaten = true;;
    this->set_pos(-200, -200);
}

bool super_food::get_eaten(){
    return this->eaten;
}

void super_food::spawn_food(){
    if((rand() % 10000 + 1) == 1){
        this->eaten = false;
        this->set_scale(2, 2);
        this->set_pos(rand() % 1000 + 1, rand() % 1000 + 1);
        this->count = 0;
        this->clock.restart();
        this->time = 0;
    }
}


