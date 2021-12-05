//
//  bots.hpp
//  Snake
//
//  Created by Channing Christian on 3/24/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef bots_hpp
#define bots_hpp

#include <stdio.h>
#include <random>
#include <SFML/Graphics.hpp>

#include "snake.hpp"

class bot {
private:
    snake * snake;
    bool die;
    bool dead;
public:
    bot();
    void kill_bot();
    void update();
    bool get_dead();
    class snake * get_snake();
};

#endif /* bots_hpp */
