//
//  food.hpp
//  Snake
//
//  Created by Channing Christian on 3/20/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef food_hpp
#define food_hpp

#include <stdio.h>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "anamation.hpp"

using namespace std;

class food{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f movementVector;
public:
    food();
    void set_orig(double x, double y);
    void set_scale(double x, double y);
    void set_pos(double x, double y);
    void eat_food();
    void movement(sf::Vector2f movementVector);
    sf::Vector2f get_movement();
    bool get_eaten();
    sf::Sprite get_sprite();
};

class super_food {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f movementVector;
    sf::Clock clock;
    double time;
    int count;
    bool eaten = true;
    Anamation * anamation;
public:
    super_food();
    void set_orig(double x, double y);
    void set_scale(double x, double y);
    void set_pos(double x, double y);
    void movement(sf::Vector2f movementVector);
    sf::Vector2f get_movement();
    void set_frame(sf::IntRect frame);
    sf::Sprite get_sprite();
    Anamation* get_anamation();
    void update_food();
    void eat_food();
    bool get_eaten();
    void spawn_food();
};

#endif /* food_hpp */
