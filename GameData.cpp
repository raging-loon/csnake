#include "GameData.h"
#include <sys/ioctl.h>
#include <unistd.h>

void GameData::init()
{
    createWindows();

    int startXloc = getRandomNumber(1, terminal_w-1);
    int startYloc = getRandomNumber(1, terminal_h-1);

    snek = new Snek(
        startXloc,
        startYloc
    );

    snek->addSegment(startXloc--, startYloc);
    snek->addSegment(startXloc--, startYloc);
    snek->addSegment(startXloc--, startYloc);
    snek->addSegment(startXloc--, startYloc);
    
    
}

void GameData::createWindows()
{

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    terminal_h = w.ws_row;
    terminal_w = w.ws_col;

    printf("%d,%d\n",terminal_w, terminal_h);

    initscr();      // initialize ncurses
    noecho();       // disable output on input
    cbreak();
    curs_set(0);    // disable cursor

    gameWindow = newwin(terminal_h-3, terminal_w, 3, 0);
    scoreWindow = newwin(2, terminal_w/2, 1,terminal_w/2);

    terminal_h -= 3;

    keypad(gameWindow, TRUE);   // enable arrow keys


    

}

void GameData::deleteWindows()
{
    if(gameWindow)
        delwin(gameWindow);
    if(scoreWindow)
        delwin(scoreWindow);

    endwin();
}

int GameData::getRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}



void GameData::draw(int x, int y, const char* c)
{
    
    wmove(gameWindow, y, x);
    wprintw(gameWindow, c);
    
} 
void GameData::clear()
{
    assert(gameWindow != nullptr);
    
    ::clear();
    wclear(gameWindow);
    wclear(scoreWindow);
}

void GameData::updateGameWindow()
{
    assert(gameWindow != nullptr);
    
    wprintw(scoreWindow, "Score: %d", snek->getSize());
    wborder(gameWindow, '|','|','-','-',0,0,0,0);
    refresh();
    wrefresh(gameWindow);
    wrefresh(scoreWindow);

}

void GameData::updateScoreWindow()
{

}

int GameData::getchar()
{
    assert(gameWindow != nullptr);
    return wgetch(gameWindow);
}