#include <stdio.h>
#include <stdlib.h>
#include <random>

#include "Game.h"

// Returns false if the player lost, true if exitting
bool rungame();

int main(int argc, char** argv)
{
    Game::get().init();

    bool gameShouldRun = true;
    while(gameShouldRun)
    {

        if(rungame() == false)
        {
            int ch;
            while(true)
            {
                
                Game::get().renderSnek("x","x");
                Game::get().updateGameWindow();
                Game::get().printLoseMessage();


                ch = Game::get().getchar();
                if(ch == 'Y' || ch == 'y')
                {
                    Game::get().resetSnek();
                    break;
                }
                else if(ch == 'N' || ch == 'n')
                {
                    gameShouldRun = false;
                    break;
                }
            }

        }
    }

    Game::get().deleteWindows();
    
    return 0;
}

bool rungame()
{
    
    Game& snekGame = Game::get();

    Snek& snek = *snekGame.snek;


    int apple_x = Game::getRandomNumber(1, snekGame.terminal_w-1);
    int apple_y = Game::getRandomNumber(1, snekGame.terminal_h-1);
    const char* snekHead = ">";
    
    snekGame.clear();
    snekGame.renderSnek("o", snekHead);
    
    while(true)
    {
        snekGame.updateGameWindow();
        snekGame.updateScoreWindow();

        snekGame.draw(apple_x, apple_y, "@");
        
        int ch = snekGame.getchar();

        snekGame.clear();
        
        switch(ch)
        {
            case KEY_UP:
            case 'w':
                snekHead = "∧";
                snek.move(Snek::DIR_UP);
                break;
            case KEY_DOWN:
            case 's':
                snekHead = "v";
                snek.move(Snek::DIR_DOWN);
                break;
            case KEY_LEFT:
            case 'a':
                snekHead = "<";
                snek.move(Snek::DIR_LEFT);
                break;
            case KEY_RIGHT:
            case 'd':
                snekHead = ">";
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
        
            apple_x = Game::getRandomNumber(1, snekGame.terminal_w-1);
            apple_y = Game::getRandomNumber(1, snekGame.terminal_h-1);

            snek.addSegment(snek.getTail()->x,snek.getTail()->y);

        
        }

        snekGame.renderSnek("o", snekHead);
        // snekGame.draw(head->x, head->y, snekHead);
        // head = head->next;
        // while(head != nullptr)
        // {

        //     snekGame.draw(head->x, head->y, "o");

        //     head = head->next;
        // }    

    }
    return false;
}