#include <stdio.h>
#include <stdlib.h>
#include <random>

#include "GameData.h"

// Returns false if the player lost, true if exitting
bool rungame();

int main(int argc, char** argv)
{
    
    GameData::get().init();
    rungame();

    GameData::get().deleteWindows();
    
    return 0;
}

bool rungame()
{
    
    GameData& snekGame = GameData::get();

    Snek& snek = *snekGame.snek;


    int apple_x = GameData::getRandomNumber(1, snekGame.terminal_w-1);
    int apple_y = GameData::getRandomNumber(1, snekGame.terminal_h-1);

    while(true)
    {
        snekGame.updateGameWindow();

        snekGame.draw(apple_x, apple_y, "@");
        
        int ch = snekGame.getchar();

        snekGame.clear();

        switch(ch)
        {
            case KEY_UP:
            case 'w':
                snek.move(Snek::DIR_UP);
                break;
            case KEY_DOWN:
            case 's':
                snek.move(Snek::DIR_DOWN);
                break;
            case KEY_LEFT:
            case 'a':
                snek.move(Snek::DIR_LEFT);
                break;
            case KEY_RIGHT:
            case 'd':
                snek.move(Snek::DIR_RIGHT);
                break;
            default:    
                continue;
        }

        snek.updatePositions();


        SnekNode* head = snek.getHead();
        
        if(snek.checkCollision(head->x, head->y))
        {
            break;
        }
        if(head->x == 0 || head->x == snekGame.terminal_w-1 ||
           head->y == 0 || head->y == snekGame.terminal_h-1)
            break;

        if(head->x == apple_x && head->y == apple_y)
        {
        
            apple_x = GameData::getRandomNumber(1, snekGame.terminal_w-1);
            apple_y = GameData::getRandomNumber(1, snekGame.terminal_h-1);

            snek.addSegment(snek.getTail()->x,snek.getTail()->y);

        
        }


        while(head != nullptr)
        {

            snekGame.draw(head->x, head->y, "O");

            head = head->next;
        }    

    }
    return false;
}