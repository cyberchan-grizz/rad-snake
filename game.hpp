//
//  game.hpp
//  Snake
//
//  Created by Channing Christian on 3/23/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class game{
private:
    bool titleScreen;
    bool playing;
    bool openingMysteryBox;
    bool selectingPowerUp;
    bool endScreen;
    
    bool poison;
    bool shield;
    bool freeze;
    bool bomb;
    bool wall;
    bool levelUpMB;
    
    bool shieldActive;
    bool freezeActive;
    bool wallActive;
    bool bombActive;
    bool poisonActive;
    bool levelUpMBActive;
    
    bool levelup;
    int level;
    
    int numOfBots;
public:
    game();
    void go_title_screen();
    void go_playing();
    void go_opening_mystery_box();
    void go_selecting_power_up();
    void go_end_screen();
    void inc_level();
    bool get_title_screen();
    bool get_playing();
    bool get_opening_mystery_box();
    bool get_selecting_power_up();
    bool get_end_screen();
    int get_level();
    void set_level_up(bool tf);
    bool get_level_up();
    
    void set_wall(bool tf);
    void set_shield(bool tf);
    void set_freeze(bool tf);
    void set_bomb(bool tf);
    void set_poison(bool tf);
    void set_level_up_mb(bool tf);
    
    bool get_wall();
    bool get_shield();
    bool get_freeze();
    bool get_bomb();
    bool get_poison();
    bool get_level_up_mb();
    
    void set_active_shield(bool tf);
    void set_active_freeze(bool tf);
    void set_active_wall(bool tf);
    void set_active_bomb(bool tf);
    void set_active_poison(bool tf);
    void set_active_level_up_mb(bool tf);
    
    bool get_active_shield();
    bool get_active_freeze();
    bool get_active_wall();
    bool get_active_bomb();
    bool get_active_poison();
    bool get_active_level_up_mb();
    
    void inc_bot_kill();
    void dec_bot_kill();
    int get_bot_kill();
};


#endif /* game_hpp */
