//
//  snake.hpp
//  Snake
//
//  Created by Channing Christian on 3/17/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef snake_hpp
#define snake_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

using namespace std;

class turning_point{
private:
    double xCord;
    double yCord;
    std::string turnDirection;
public:
    turning_point(double xCord, double yCord);
    void left_turn();
    void right_turn();
    double get_x_cord();
    double get_y_cord();
    std::string get_turn_direction();
};

class snake_part{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f movementVector;
    int xCord;
    int yCord;
    std::vector<turning_point> turningPoints;
public:
    snake_part(int xCord, int yCord);
    void set_orig(double x, double y);
    void set_scale(double x, double y);
    void set_pos(double x, double y);
    void movement(sf::Vector2f movementVector);
    sf::Vector2f get_movement();
    sf::Sprite get_sprite();
    void add_turning_point(turning_point);
    void delete_first_turning_point();
    std::vector<turning_point> get_turning_points();
    void set_color(int num1, int num2, int num3);
};

class snake{
private:
    std::vector<snake_part*> snakeParts;
    double snakeSpeed;
    int xCord;
    int yCord;
    sf::Clock clock;
    double time;
    bool dead;
    int colorR = 255;
    int colorG = 255;
    int colorB = 255;
public:
    snake(int xCord, int yCord);
    void move_left();
    void move_right();
    void update_snake_movement();
    void add_snake_part();
    void remove_snake_tail();
    void die();
    std::vector<snake_part*> get_snake_parts();
    void change_color(int r, int g, int b);
};


#endif /* snake_hpp */
