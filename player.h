#ifndef PLAYER_H
#define PLAYER_H
#include <QColor>
#include "game.h"

struct Player
{
    int x,y,dir;
    QColor color;
    Player(QColor c)
    {
        x = rand() % Game::RESOLUTION.width();
        y = rand() % Game::RESOLUTION.height();
        color = c;
        dir = rand() % 4;
    }
    void init()
    {
        x = rand() % Game::RESOLUTION.width();
        y = rand() % Game::RESOLUTION.height();
        dir = rand() % 4;
    }

    void tick()
    {
        if (dir == 0) y+=1;
        if (dir == 1) x-=1;
        if (dir == 2) x+=1;
        if (dir == 3) y-=1;

        if ( x >= Game::RESOLUTION.width() ) x = 0;  if ( x<0 ) x = Game::RESOLUTION.width()-1;
        if (y >= Game::RESOLUTION.height())  y = 0;  if ( y<0)  y = Game::RESOLUTION.height()-1;
    }

    QColor getColor()
    {
        return color;
    }
};

#endif // PLAYER_H
