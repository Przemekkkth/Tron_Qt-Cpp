#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_p1UpMove(false), m_p1RightMove(false), m_p1DownMove(false), m_p1LeftMove(false),
      m_p2UpMove(false), m_p2RightMove(false), m_p2DownMove(false),
      m_p2LeftMove(false), m_loopSpeed(20.0f), m_deltaTime(0.0f), m_loopTime(0.0f),
      m_p1(Qt::yellow), m_p2(Qt::blue), m_isGame(true)
{
    loadPixmap();
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    clear();
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
    bgItem->setTransformationMode(Qt::SmoothTransformation);
    addItem(bgItem);


    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(Game::ITERATION_VALUE);
    m_elapsedTimer.start();
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    switch (event->key()) {

    case Qt::Key_Up:
    {
        m_p1UpMove = true;
    }
        break;
    case Qt::Key_Right:
    {
        m_p1RightMove = true;
    }
        break;
    case Qt::Key_Down:
    {
        m_p1DownMove = true;
    }
        break;
        case Qt::Key_Left:
    {
        m_p1LeftMove = true;
    }
        break;

    case Qt::Key_W:
    {
        m_p2UpMove = true;
    }
        break;
    case Qt::Key_D:
    {
        m_p2RightMove = true;
    }
        break;
    case Qt::Key_S:
    {
        m_p2DownMove = true;
    }
        break;
    case Qt::Key_A:
    {
        m_p2LeftMove = true;
    }
        break;
    case Qt::Key_R:
    {
        reset();
    }
    case Qt::Key_Z:
    {
        //renderScene();
    }
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    switch (event->key()) {

    case Qt::Key_Up:
    {
        m_p1UpMove = false;
    }
        break;
    case Qt::Key_Right:
    {
        m_p1RightMove = false;
    }
        break;
    case Qt::Key_Down:
    {
        m_p1DownMove = false;
    }
        break;
        case Qt::Key_Left:
    {
        m_p1LeftMove = false;
    }
        break;

    case Qt::Key_W:
    {
        m_p2UpMove = false;
    }
        break;
    case Qt::Key_D:
    {
        m_p2RightMove = false;
    }
        break;
    case Qt::Key_S:
    {
        m_p2DownMove = false;
    }
        break;
    case Qt::Key_A:
    {
        m_p2LeftMove = false;
    }
        break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed )
    {
        m_loopTime -= m_loopSpeed;

        move();
        if(!m_isGame)
        {
            return;
        }

        for(int i=0;i < m_game.m_speed;i++)
        {
            m_p1.tick();
            m_p2.tick();
            if (m_game.m_field[m_p1.x][m_p1.y] == true)
            {
                QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem("P2 Win");
                textItem->setFont(QFont("Arial", 20, 50));
                textItem->setPos(Game::RESOLUTION.width()/2 - textItem->boundingRect().width()/2, 0);
                textItem->setBrush(Qt::white);
                textItem->setPen(QPen(Qt::white));
                addItem(textItem);
                m_isGame = false;
            }
            if (m_game.m_field[m_p2.x][m_p2.y] == true)
            {
                QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem("P1 Win");
                textItem->setPos(Game::RESOLUTION.width()/2 - textItem->boundingRect().width()/2, 0);
                textItem->setFont(QFont("Arial", 20, 50));
                addItem(textItem);
                textItem->setBrush(Qt::white);
                textItem->setPen(QPen(Qt::white));
                m_isGame = false;
            }

            m_game.m_field[m_p1.x][m_p1.y] = true;
            m_game.m_field[m_p2.x][m_p2.y] = true;


            QGraphicsEllipseItem *p1Item = new QGraphicsEllipseItem(0,0,6,6);
            p1Item->setPos(m_p1.x, m_p1.y);
            p1Item->setBrush(m_p1.getColor());
            p1Item->setPen(m_p1.getColor());
            addItem(p1Item);


            QGraphicsEllipseItem *p2Item = new QGraphicsEllipseItem(0,0,6,6);
            p2Item->setPos(m_p2.x, m_p2.y);
            p2Item->setBrush(m_p2.getColor());
            p2Item->setPen(m_p2.getColor());
            addItem(p2Item);
        }
    }
}

void GameScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BACKGROUND_PIXMAP))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }
}

void GameScene::move()
{
    if(m_p1UpMove)
    {
        if (m_p1.dir!=0)
        {
            m_p1.dir=3;
        }
    }
    if(m_p1RightMove)
    {
        if (m_p1.dir!=1)
        {
            m_p1.dir=2;
        }
    }
    if(m_p1DownMove)
    {
        if (m_p1.dir!=3)
        {
            m_p1.dir=0;
        }
    }
    if(m_p1LeftMove)
    {
        if (m_p1.dir!=2)
        {
            m_p1.dir=1;
        }
    }

    if(m_p2UpMove)
    {
        if (m_p2.dir!=0)
        {
            m_p2.dir=3;
        }
    }
    if(m_p2RightMove)
    {
        if (m_p2.dir!=1)
        {
            m_p2.dir=2;
        }
    }
    if(m_p2DownMove)
    {
        if (m_p2.dir!=3)
        {
            m_p2.dir=0;
        }
    }
    if(m_p2LeftMove)
    {
        if (m_p2.dir!=2)
        {
            m_p2.dir=1;
        }
    }
}

void GameScene::reset()
{
    m_p1UpMove = m_p1RightMove = m_p1DownMove = m_p1LeftMove = false;
    m_p2UpMove = m_p2RightMove = m_p2DownMove = m_p2LeftMove = false;
    clear();
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
    bgItem->setTransformationMode(Qt::SmoothTransformation);
    addItem(bgItem);
    m_game.init();
    m_p1.init();
    m_p2.init();
    m_isGame = true;
}


void GameScene::renderScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}
