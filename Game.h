#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <random>
#include <ncurses.h>
#include "snek.h"

enum class GameMode
{
    EAT_APPLES,
    EAT_NUMBERS
};


// singleton struct for holding global game data
// JBOD
struct Game
{


    Snek*       snek;

    int         score;

    int         terminal_h;
    int         terminal_w;

    WINDOW*     gameWindow;
    WINDOW*     scoreWindow;

    char        snakeHead;

    bool        bordersDisabled;


    void        init();

    void        createWindows();
    void        deleteWindows();

    void        draw(int x, int y, const char* c);
    void        updateGameWindow();
    void        printLoseMessage();
    int         getchar();
    void        clear();
    void        updateScoreWindow();

    void        renderSnek(const char* snekBody, const char* snekHead);
    
    void        resetSnek();

    static int  getRandomNumber(int min, int max);
    static Game& get()
    {
        static Game gd;
        return gd;
    }

private:
    // private constructor
    Game(){}
    // get rid of copy-assignment
    void operator=(const Game&) = delete;
    // get rid of copy constructor
    Game(const Game& ) = delete;


};  


#endif // GAMEDATA_H_