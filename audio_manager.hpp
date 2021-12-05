//
//  audio_manager.hpp
//  Snake
//
//  Created by Channing Christian on 3/31/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef audio_manager_hpp
#define audio_manager_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Audio.hpp>

class audio_manager{
private:
    sf::Music startTrack;
    sf::Music playingTrack;
    sf::Music endTrack;
    
    sf::Sound gameOver;
    sf::SoundBuffer gameOverBuffer;
    
    sf::Sound ping;
    sf::SoundBuffer pingBuffer;
    
    sf::Sound levelUp;
    sf::SoundBuffer levelUpBuffer;
    
public:
    audio_manager();
    void play_start_track();
    void play_gameplay_track();
    void play_end_track();
    void stop_music();
    bool is_music_playing();
    
    void play_game_over();
    void play_ping();
    void play_level_up();
};

#endif /* audio_manager_hpp */
