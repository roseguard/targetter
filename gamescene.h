#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QVector>
#include <QTimer>
#include <time.h>

#include "fieldcell.h"

class fieldCell;

class gameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    gameScene(QGraphicsView *parView, bool isHost ,QWidget *parent = 0);

    QGraphicsView                 *viewer;
    QGraphicsPixmapItem           *player;
    QGraphicsPixmapItem           *enemy;
    QVector<fieldCell*>           cellsVector;
    bool                          iHost;
    QVector<QGraphicsPixmapItem*> targets;
    QVector<QTimer*>              targetExpl;
    QVector<QTimer*>              timersToClean;
    QTimer                        *timeForTarget;
    bool                          isGameEnded = false;


    void keyPressEvent(QKeyEvent *event);
    void setEnemyPos(int x, int y);
    bool isHost();

signals:
    void playerMoved(int newX, int newY);
    void newTargetting(int x, int y);
    void gameEnded();
    void itemNetworkMessage(QString message);
public slots:
    void createNewTargeting(int x, int y);
    void createRandomTarget();
    void blowTarget();
    void clearTarget();
    void endGame();
    void otherPlayerLoosed();
    void emitNetworkMessage(QString message);
};

#endif // GAMESCENE_H
