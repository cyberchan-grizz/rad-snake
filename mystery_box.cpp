//
//  mystery_box.cpp
//  Snake
//
//  Created by Channing Christian on 3/20/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "mystery_box.hpp"

//Mystery Box
mystery_box::mystery_box(){
    this->texture.loadFromFile("Textures/mystery_box.png");
    this->openTexture.loadFromFile("Textures/open_mystery_box.png");
    this->sprite.setTexture(this->texture);
    this->anamation = new Anamation(11, 32, 32, 128, 96);
    this->openAnamation = new Anamation(36, 64, 64, 384, 384);
    this->sprite.setTextureRect(this->anamation->getFrame(0));
    this->set_orig(16, 16);
    this->set_scale(2.25, 2.25);
    this->set_pos(-100, -100);
    this->mysteryBoxSpeed = 0.05;
    this->spawn_mystery_box();
}

void mystery_box::set_orig(double x, double y){
    this->sprite.setOrigin(x, y);
}

void mystery_box::set_scale(double x, double y){
    this->sprite.setScale(x, y);
}

void mystery_box::set_pos(double x, double y){
    this->sprite.setPosition(x , y);
}

void mystery_box::eat_mystery_box(){
    this->movement(sf::Vector2f(0, 0));
    this->eaten = true;
}

bool mystery_box::get_eaten(){
    return this->eaten;
}

void mystery_box::spawn_mystery_box(){
    if(rand() % 500000 + 1 == 1){
        this->eaten = false;
        int x;
        int y;
        if((rand() % 2 + 1) == 1){// this chooses whether the box comes from the top/bottom or left/right
            if((rand() % 2 + 1) == 1){ // this chooses whether the box comes from the top or the bottom
                y = -70;
                this->movement(sf::Vector2f(0, this->mysteryBoxSpeed));
            } else {
                y = 1070;
                this->movement(sf::Vector2f(0, -this->mysteryBoxSpeed));
            }
            x = rand() % 900 + 50;
        } else {
            if((rand() % 2 + 1) == 1){ // this chooses whether the box comes from the left or right
                x = -70;
                this->movement(sf::Vector2f(this->mysteryBoxSpeed, 0));
            } else {
                x = 1070;
                this->movement(sf::Vector2f(-this->mysteryBoxSpeed, 0));
            }
            y = rand() % 900 + 50;
        }
        this->set_pos(x, y);
        this->count = 0;
        this->clock.restart();
        this->time = 0;
    }
}

sf::Sprite mystery_box::get_sprite(){
    return this->sprite;
}

std::string mystery_box::get_contents(){
    std::vector<std::string> possibleContents = {"bomb", "level up", "poison", "freeze", "shield", "wall"};
    this->contents = possibleContents[rand() % possibleContents.size()];
    return this->contents;
}

void mystery_box::movement(sf::Vector2f movementVector){
    this->movementVector = movementVector;
    this->sprite.move(this->movementVector);
}

sf::Vector2f mystery_box::get_movement(){
    return this->movementVector;
}

Anamation * mystery_box::get_anamation(){
    return this->anamation;
}

Anamation * mystery_box::get_open_anamation(){
    return this->openAnamation;
}

void mystery_box::update_mystery_box(){
    this->time = this->clock.getElapsedTime().asSeconds();
    if(this->time >= 0.2){
        if(this->count < this->get_anamation()->getAnamationLength() - 1){
            this->count++;
        } else {
            this->count = 0;
        }
        this->clock.restart();
    }
    this->set_frame(this->get_anamation()->getFrame(count));
    if(this->get_sprite().getPosition().x < -200 || this->get_sprite().getPosition().x > 1200){
        this->eaten = true;
        this->set_pos(-100, -100);
    }
    if(this->get_sprite().getPosition().y < -200 || this->get_sprite().getPosition().y > 1200){
        this->eaten = true;
        this->set_pos(-100, -100);
    }
}

void mystery_box::reset_anamation(){
    this->clock.restart();
    this->time = NULL;
    this->count = 0;
}

void mystery_box::open_box(){
    this->time = this->clock.getElapsedTime().asSeconds();
    if(this->time >= 0.05){
        if(this->count < this->get_open_anamation()->getAnamationLength() - 1){
            this->count++;
        } else {
            this->count = 0;
            this->eaten = true;
            this->sprite.setTexture(texture);
            this->set_scale(2.25, 2.25);
            this->set_orig(16, 16);
            this->set_pos(-100, -100);
        }
        this->clock.restart();
    }
    this->set_frame(this->get_open_anamation()->getFrame(count));
}

void mystery_box::set_open_texture(){
    this->sprite.setTexture(this->openTexture);
    this->sprite.setTextureRect(this->get_open_anamation()->getFrame(0));
    this->set_scale(20, 20);
    this->set_orig(32, 32);
}

void mystery_box::set_frame(sf::IntRect frame){
    this->sprite.setTextureRect(frame);
}

//Mystery Box Item
void mystery_box_item::set_scale(double x, double y){
    this->sprite.setScale(x, y);
}

void mystery_box_item::set_orig(double x, double y){
    this->sprite.setOrigin(x, y);
}

void mystery_box_item::set_pos(double x, double y){
    this->sprite.setPosition(x, y);
}

void mystery_box_item::set_color(int num1, int num2, int num3){
    this->sprite.setColor(sf::Color(num1, num2, num3));
}

void mystery_box_item::movement(sf::Vector2f movementVector){
    this->movementVector = movementVector;
    this->sprite.move(movementVector);
}

sf::Vector2f mystery_box_item::get_movement(){
    return this->movementVector;
}

sf::Sprite mystery_box_item::get_sprite(){
    return this->sprite;
}

//bomb
bomb::bomb(){
    this->texture.loadFromFile("Textures/bomb.png");
    this->sprite.setTexture(this->texture);
}

void bomb::go_boom(std::vector<bot *> *bots, food *food, super_food *superFood, mystery_box *mysteryBox){
    NULL;
}

bool bomb::get_done(){
    return this->done;
}

//shield
shield::shield(){
    this->texture.loadFromFile("Textures/shield.png");
    this->sprite.setTexture(this->texture);
}

double shield::get_time(){
    this->time = this->clock.getElapsedTime().asSeconds();
    return this->time;
}

void shield::reset_clock(){
    this->clock.restart();
}

//level up
level_up::level_up(){
    this->texture.loadFromFile("Textures/level_up.png");
    this->sprite.setTexture(this->texture);
}

void level_up::increment_level(snake * snake, game * game){
    snake->remove_snake_tail();
    game->inc_level();
    game->set_level_up(true);
}

//wall 
wall::wall(){
    this->texture.loadFromFile("Textures/wall.png");
    this->sprite.setTexture(this->texture);
}

double wall::get_time(){
    this->time = this->clock.getElapsedTime().asSeconds();
    return this->time;
}

void wall::reset_clock(){
    this->clock.restart();
}

//poison
poison::poison(){
    this->texture.loadFromFile("Textures/poison.png");
    this->sprite.setTexture(this->texture);
}

void poison::poison_snake(snake *snake){
    snake->remove_snake_tail();
}

//freeze
freeze::freeze(){
    this->texture.loadFromFile("Textures/freeze.png");
    this->sprite.setTexture(this->texture);
}

double freeze::get_time(){
    this->time = this->clock.getElapsedTime().asSeconds();
    return this->time;
}

void freeze::reset_clock(){
    this->clock.restart();
}
