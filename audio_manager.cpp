//
//  audio_manager.cpp
//  Snake
//
//  Created by Channing Christian on 3/31/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "audio_manager.hpp"

audio_manager::audio_manager(){
    this->startTrack.openFromFile("Audio/butterfly_effect.ogg");
    this->startTrack.setLoop(true);
    this->startTrack.setVolume(50);

    this->playingTrack.openFromFile("Audio/disk_wars.ogg");
    this->playingTrack.setLoop(true);
    this->playingTrack.setVolume(50);
    
    this->gameOverBuffer.loadFromFile("Audio/game_over.ogg");
    this->gameOver.setBuffer(this->gameOverBuffer);
    this->gameOver.setVolume(50);
    
    this->levelUpBuffer.loadFromFile("Audio/level_up.ogg");
    this->levelUp.setBuffer(this->levelUpBuffer);
    this->levelUp.setVolume(50);
    
    this->pingBuffer.loadFromFile("Audio/ping.ogg");
    this->ping.setBuffer(this->pingBuffer);
    this->ping.setVolume(10);
}

void audio_manager::play_start_track(){
    this->playingTrack.stop();
    this->endTrack.stop();
    this->startTrack.play();
}

void audio_manager::play_gameplay_track(){
    this->startTrack.stop();
    this->endTrack.stop();
    this->playingTrack.play();
}

void audio_manager::stop_music(){
    this->startTrack.stop();
    this->endTrack.stop();
    this->playingTrack.stop();
}

bool audio_manager::is_music_playing(){
    if(this->startTrack.getStatus() == sf::SoundSource::Status::Stopped && this->playingTrack.getStatus() == sf::SoundSource::Status::Stopped && this->endTrack.getStatus() == sf::SoundSource::Status::Stopped){
        return false;
    }
    return true;
}

void audio_manager::play_game_over(){
    this->gameOver.play();
}

void audio_manager::play_ping(){
    this->ping.play();
}

void audio_manager::play_level_up(){
    this->levelUp.play();
}
