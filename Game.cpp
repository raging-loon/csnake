#include "Game.h"

#include <sys/ioctl.h>
#include <unistd.h>

void Game::init()
{
    createWindows();

    resetSnek();

    
}

void Game::createWindows()
{

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    terminal_h = w.ws_row;
    terminal_w = w.ws_col;

    printf("%d,%d\n",terminal_w, terminal_h);

    // enable wide characters
    // specifically used for "DIR_UP" snake head
    setlocale(LC_ALL, ""); 

    initscr();      // initialize ncurses
    noecho();       // disable output on input
    cbreak();
    curs_set(0);    // disable cursor

    gameWindow = newwin(terminal_h-3, terminal_w, 3, 0);
    scoreWindow = newwin(2, terminal_w, 1,0);

    terminal_h -= 3;

    keypad(gameWindow, TRUE);   // enable arrow keys



    

}

void Game::deleteWindows()
{
    if(gameWindow)
        delwin(gameWindow);
    if(scoreWindow)
        delwin(scoreWindow);

    endwin();
}

int Game::getRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}



void Game::draw(int x, int y, const char* c)
{
    
    wmove(gameWindow, y, x);
    wprintw(gameWindow, c);
    
} 
void Game::clear()
{
    assert(gameWindow != nullptr);
    
    ::clear();
    werase(gameWindow);
    werase(scoreWindow);
}

void Game::updateGameWindow()
{
    assert(gameWindow != nullptr);
    
    wborder(gameWindow, '|','|','-','-',0,0,0,0);
    wrefresh(gameWindow);

}

void Game::updateScoreWindow()
{
    wprintw(scoreWindow, "Score: %d", snek->getSize());
    wrefresh(scoreWindow);

}

void Game::printLoseMessage()
{
    werase(scoreWindow);
    wprintw(scoreWindow, "Press Y to restart or N to exist");
    wrefresh(scoreWindow);
}

int Game::getchar()
{
    assert(gameWindow != nullptr);
    return wgetch(gameWindow);
}

void Game::resetSnek()
{
    if(snek)
        delete snek;
    snek = new Snek;

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

void Game::renderSnek(const char* snekBody, const char* snekHead)
{
    SnekNode* head = snek->getHead();
    draw(head->x, head->y, snekHead);
   
    head = head->next;
    while(head != nullptr)
    {
        draw(head->x, head->y, snekBody);
        head = head->next;
    }    
}
