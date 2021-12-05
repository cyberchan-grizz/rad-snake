//
//  mystery_box.hpp
//  Snake
//
//  Created by Channing Christian on 3/20/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef mystery_box_hpp
#define mystery_box_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

#include "snake.hpp"
#include "food.hpp"
#include "anamation.hpp"
#include "bots.hpp"
#include "game.hpp"

using namespace std;

class mystery_box{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture openTexture;
    sf::Clock clock;
    double time;
    int count;
    Anamation * anamation;
    Anamation * openAnamation;
    bool eaten = true;
    std::string contents = "shield";
    sf::Vector2f movementVector;
    double mysteryBoxSpeed;
public:
    mystery_box();
    void set_scale(double x, double y);
    void set_orig(double x, double y);
    void set_pos(double x, double y);
    void eat_mystery_box();
    bool get_eaten();
    void spawn_mystery_box();
    sf::Sprite get_sprite();
    std::string get_contents();
    void movement(sf::Vector2f movementVector);
    sf::Vector2f get_movement();
    Anamation * get_anamation();
    Anamation * get_open_anamation();
    void update_mystery_box();
    void reset_anamation();
    void open_box();
    void reset_box();
    void set_open_texture();
    void set_frame(sf::IntRect frame);
};

class mystery_box_item {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f movementVector;
    void set_scale(double x, double y);
    void set_orig(double x, double y);
    void set_pos(double x, double y);
    void set_color(int num1, int num2, int num3);
    void movement(sf::Vector2f movementVector);
    sf::Vector2f get_movement();
    sf::Sprite get_sprite();
};

class bomb : public mystery_box_item {
private:
    sf::Clock clock;
    double time;
    bool done = false;
public:
    bomb();
    void go_boom(std::vector<bot*> * bots, food * food, super_food * superFood, mystery_box * mysteryBox);
    bool get_done();
    
};

class shield : public mystery_box_item {
private:
    sf::Clock clock;
    double time;
    bool protection = false;
public:
    shield();
    double get_time();
    void reset_clock();
};

class level_up : public mystery_box_item {
public:
    level_up();
    void increment_level(snake * snake, game * game);
};

class wall : public mystery_box_item {
private:
    sf::Clock clock;
    double time;
public:
    wall();
    double get_time();
    void reset_clock();
};

class poison : public mystery_box_item {
public:
    poison();
    void poison_snake(snake * snake);
};

class freeze : public mystery_box_item {
private:
    sf::Clock clock;
    double time;
public:
    freeze();
    double get_time();
    void reset_clock();
};
#endif /* mystery_box_hpp */
