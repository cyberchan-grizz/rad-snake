//
//  anamation.cpp
//  anamation files
//
//  Created by Channing Christian on 12/6/19.
//  Copyright © 2019 Channing Christian. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "anamation.hpp"
using namespace std;

Anamation::Anamation(int arrayLen, int frameLength, int frameHeight, int sheetHeight, int sheetLength){
    int x = 0;
    int y = 0;
    for(int i = 0; i < arrayLen; i++){
        addFrame(sf::IntRect {x, y, frameLength, frameHeight});
        if(x + frameLength == sheetLength){
            x = 0;
            y += frameHeight;
        } else {
            x+= frameLength;
        }
    }
}

void Anamation::addFrame(sf::IntRect frame){
    mainFrames.push_back(frame);
}

sf::IntRect Anamation::getFrame(int frame){
    return mainFrames[frame];
}

int Anamation::getAnamationLength(){
    return mainFrames.size();
}


