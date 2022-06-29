#include "view.h"
#include <QGraphicsBlurEffect>
#include <QApplication>
#include <QKeyEvent>

View::View() : QGraphicsView(), m_gameScene(new GameScene(this))
{
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width() + 2, m_gameScene->sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setGraphicsEffect(new QGraphicsBlurEffect());
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
    {
        QApplication::instance()->quit();
    }
        break;
    }

    QGraphicsView::keyPressEvent(event);
}
