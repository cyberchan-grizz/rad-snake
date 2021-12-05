//
//  game.cpp
//  Snake
//
//  Created by Channing Christian on 3/23/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "game.hpp"

game::game(){
    this->level = 0;
    this->titleScreen = true;
    this->playing = false;
    this->openingMysteryBox = false;
    this->selectingPowerUp = false;
    this->endScreen = false;
    this->levelup = false;
    
    this->poison = false;
    this->shield = false;
    this->freeze = false;
    this->bomb = false;
    this->wall = false;
    this->levelUpMB = false;
    
    this->poisonActive = false;
    this->shieldActive = false;
    this->freezeActive = false;
    this->bombActive = false;
    this->wallActive = false;
    this->levelUpMBActive = false;
    
    this->numOfBots = 0;
}

void game::go_title_screen(){
    this->titleScreen = true;
    this->playing = false;
    this->openingMysteryBox = false;
    this->selectingPowerUp = false;
    this->endScreen = false;
}

void game::go_playing(){
    this->titleScreen = false;
    this->playing = true;
    this->openingMysteryBox = false;
    this->selectingPowerUp = false;
    this->endScreen = false;
}

void game::go_opening_mystery_box(){
    this->titleScreen = false;
    this->playing = false;
    this->openingMysteryBox = true;
    this->selectingPowerUp = false;
    this->endScreen = false;
}

void game::go_selecting_power_up(){
    this->titleScreen = false;
    this->playing = false;
    this->openingMysteryBox = false;
    this->selectingPowerUp = true;
    this->endScreen = false;
}

void game::go_end_screen(){
    this->titleScreen = false;
    this->playing = false;
    this->openingMysteryBox = false;
    this->selectingPowerUp = false;
    this->endScreen = true;
}

void game::inc_level(){
    this->level++;
}

bool game::get_title_screen(){
    return this->titleScreen;
}

bool game::get_playing(){
    return this->playing;
}

bool game::get_opening_mystery_box(){
    return this->openingMysteryBox;
}

bool game::get_selecting_power_up(){
    return this->selectingPowerUp;
}

bool game::get_end_screen(){
    return this->endScreen;
}

int game::get_level(){
    return this->level;
}

void game::set_level_up(bool tf){
    this->levelup = tf;
}

bool game::get_level_up(){
    return this->levelup;
}

void game::set_wall(bool tf){
    this->wall = tf;
}

void game::set_shield(bool tf){
    this->shield = tf;
}

void game::set_freeze(bool tf){
    this->freeze = tf;
}

void game::set_bomb(bool tf){
    this->bomb = tf;
}

void game::set_poison(bool tf){
    this->poison = tf;
}

void game::set_level_up_mb(bool tf){
    this->levelUpMB = tf;
}

bool game::get_wall(){
    return this->wall;
}

bool game::get_shield(){
    return this->shield;
}

bool game::get_freeze(){
    return this->freeze;
}

bool game::get_bomb(){
    return this->bomb;
}

bool game::get_poison(){
    return this->poison;
}

bool game::get_level_up_mb(){
    return this->levelUpMB;
}

void game::set_active_shield(bool tf){
    this->shieldActive = tf;
}

void game::set_active_freeze(bool tf){
    this->freezeActive = tf;
}

void game::set_active_wall(bool tf){
    this->wallActive = tf;
}

void game::set_active_bomb(bool tf){
    this->bombActive = tf;
}

void game::set_active_poison(bool tf){
    this->poisonActive = tf;
}

void game::set_active_level_up_mb(bool tf){
    this->levelUpMBActive = tf;
}

bool game::get_active_shield(){
    return this->shieldActive;
}

bool game::get_active_bomb(){
    return this->bombActive;
}

bool game::get_active_freeze(){
    return this->freezeActive;
}

bool game::get_active_wall(){
    return this->wallActive;
}

bool game::get_active_poison(){
    return this->poisonActive;
}

bool game::get_active_level_up_mb(){
    return this->levelUpMBActive;
}

void game::inc_bot_kill(){
    this->numOfBots = this->numOfBots + 1;
}

void game::dec_bot_kill(){
    this->numOfBots = this->numOfBots - 1;
}

int game::get_bot_kill(){
    return this->numOfBots;
}

