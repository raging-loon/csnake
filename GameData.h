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
struct GameData
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
    void        updateScoreWindow();
    int         getchar();
    void        clear();


    static int  getRandomNumber(int min, int max);
    static GameData& get()
    {
        static GameData gd;
        return gd;
    }

private:
    // private constructor
    GameData(){}
    // get rid of copy-assignment
    void operator=(const GameData&) = delete;
    // get rid of copy constructor
    GameData(const GameData& ) = delete;


};  


#endif // GAMEDATA_H_