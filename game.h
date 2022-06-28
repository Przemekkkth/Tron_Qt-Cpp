#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>

class Game
{
public:
    Game();
    static const QSize RESOLUTION;
    static const float ITERATION_VALUE;
    static const QString PATH_TO_BACKGROUND_PIXMAP;
    int m_speed = 4;
    bool m_field[600][480];
};

#endif // GAME_H
