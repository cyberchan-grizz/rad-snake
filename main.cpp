//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.

#include "snake.hpp"
#include "gameplay.hpp"
#include "food.hpp"
#include "mystery_box.hpp"
#include "open_mystery_box.hpp"
#include "game.hpp"
#include "bots.hpp"
#include "selecting_power_up.hpp"
#include "start_screen.hpp"
#include "game_over.hpp"
#include "audio_manager.hpp"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    snake * snake;
    food * food;
    super_food * superFood;
    mystery_box * mysteryBox;
    game * game = new class game();
    std::vector<bot*> * bots;
    audio_manager * audioManager = new audio_manager();
    sf::Sprite inventorySprite;
    sf::Texture inventoryTexture;
    inventoryTexture.loadFromFile("Textures/inventory.png");
    inventorySprite.setTexture(inventoryTexture);
    inventorySprite.setOrigin(16, 16);
    inventorySprite.setScale(2.5, 2.5);
    inventorySprite.setPosition(50, 950);
    text_box * level;
    text_box * score;
    text_box * levelUp1;
    text_box * levelUp2;
    sf::Clock clock;
    double time;
    
    sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SNAKE (Version 1.0)");
    while(window->isOpen()){
        time = 0;
        if(time == 0){
            if(game->get_title_screen() == true){
                snake = new class snake(500, 500);
                food = new class food();
                superFood = new class super_food();
                mysteryBox = new class mystery_box();
                game = new class game();
                bots = new std::vector<bot*>;
                score = new class text_box("Score: " + std::to_string(snake->get_snake_parts().size() - 5));
                score->set_pos(0, 30);
                score->set_size(1.25);
                level = new class text_box("Level: " + std::to_string(game->get_level()));
                level->set_pos(0, 0);
                level->set_size(1.25);
                levelUp1 = new class text_box("LEVEL");
                levelUp1->set_pos(-300, 375);
                levelUp1->set_size(3);
                levelUp1->movement(sf::Vector2f(1.2, 0));
                levelUp2 = new class text_box("UP");
                levelUp2->set_pos(1300, 450);
                levelUp2->set_size(3);
                levelUp2->movement(sf::Vector2f(-1.2, 0));
                if(audioManager->is_music_playing() == false){
                    audioManager->play_start_track();
                }
                start_screen(game, window, audioManager);
                audioManager->play_level_up();
            } else if (game->get_playing() == true){
                if(audioManager->is_music_playing() == false){
                    audioManager->play_gameplay_track();
                }
                gameplay(game, window, snake, food, superFood, mysteryBox, level, score, levelUp1, levelUp2, bots, inventorySprite, audioManager);
            } else if (game->get_selecting_power_up() == true){
                selecting_power_up(window, snake, food, superFood, game, inventorySprite, mysteryBox, level, score, levelUp1, levelUp2, bots);
            } else if (game->get_opening_mystery_box() == true){
                open_mystery_box(window, game, snake, mysteryBox, food, superFood, level, score, bots, inventorySprite);
            } else if (game->get_end_screen() == true){
                audioManager->play_start_track();
                game_over(game, window, snake, food, superFood, mysteryBox, level, score, levelUp1, levelUp2, bots, inventorySprite, audioManager);
                delete snake;
                delete food;
                delete superFood;
                delete mysteryBox;
                delete game;
                delete bots;
                delete score;
                delete level;
                delete levelUp1;
                delete levelUp2;
            }
        }
    }
    return 0;
}
