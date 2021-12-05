//
//  anamation.hpp
//  anamation files
//
//  Created by Channing Christian on 12/6/19.
//  Copyright © 2019 Channing Christian. All rights reserved.
//

#ifndef anamation_hpp
#define anamation_hpp

#include <stdio.h>

class Anamation{
private:
    std::vector<sf::IntRect> mainFrames;
    void addFrame(sf::IntRect frame);
public:
    Anamation(int arrayLen, int frameLength, int frameHeight, int sheetHeight, int sheetLength);
    sf::IntRect getFrame(int frame);
    int getAnamationLength();
};

#endif /* anamation_hpp */
