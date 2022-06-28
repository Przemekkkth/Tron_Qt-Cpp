#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QElapsedTimer>
#include "game.h"
#include "player.h"
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void loop();
private:
    Game m_game;
    void loadPixmap();
    void move();
    bool m_p1UpMove, m_p1RightMove, m_p1DownMove, m_p1LeftMove;
    bool m_p2UpMove, m_p2RightMove, m_p2DownMove, m_p2LeftMove;
    QPixmap m_bgPixmap;
    QElapsedTimer m_elapsedTimer;
    QTimer m_timer;
    const float m_loopSpeed;
    float m_deltaTime, m_loopTime;
    Player m_p1, m_p2;
    bool m_isGame;
};

#endif // GAMESCENE_H
