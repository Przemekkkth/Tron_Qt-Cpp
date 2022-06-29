#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "gamescene.h"
class View : public QGraphicsView
{
    Q_OBJECT
public:
    View();
private:
    GameScene* m_gameScene;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
