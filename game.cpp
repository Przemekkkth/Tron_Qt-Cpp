#include "game.h"

const QSize Game::RESOLUTION = QSize(600, 480);
const float Game::ITERATION_VALUE = 1000.0f/60.0f;
const QString Game::PATH_TO_BACKGROUND_PIXMAP = ":/images/background.jpg";

Game::Game()
    : m_speed(4)
{
    for(int i = 0; i < RESOLUTION.width(); ++i)
    {
        for(int j = 0; j < RESOLUTION.height(); ++j)
        {
            m_field[i][j] = false;
        }
    }
}
