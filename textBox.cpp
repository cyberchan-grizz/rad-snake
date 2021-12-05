//
//  textBox.cpp
//  theMotherFuckers
//
//  Created by Channing Christian on 12/22/19.
//  Copyright © 2019 Channing Christian. All rights reserved.
//

#include "textBox.hpp"

text_box::text_box(std::string msg){
    font.loadFromFile("Fonts/upheavtt.ttf");
    text.setFont(font);
    text.setString(msg);
    text.setColor(sf::Color::White);
}

void text_box::set_string(std::string string){
    text.setString(string);
}

void text_box::set_pos(double x, double y){
    text.setPosition(x, y);
}

void text_box::set_size(double size){
    text.setScale(size, size);
}

void text_box::movement(sf::Vector2f movement){
    this->movementVector = movement;
    text.move(movement);
}

sf::Vector2f text_box::get_movement(){
    return this->movementVector;
}

sf::Text text_box::getText(){
    return text;
}
