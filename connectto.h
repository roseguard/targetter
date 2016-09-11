#ifndef CONNECTTO_H
#define CONNECTTO_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QSlider>

#include "foropt.h"

class connectTo
{
public:
    connectTo();
};

class connectToScene : public QGraphicsScene
{
    Q_OBJECT
public:
    connectToScene(optSaver *optionsAddr, QWidget *parent = 0);
private:
    optSaver *options;

    QGraphicsPixmapItem     *background;
    QGraphicsPixmapItem     *header;

    QGraphicsTextItem       *addrText;
    QLineEdit               *addrWidget;
    QGraphicsProxyWidget    *addrProxy;

    QGraphicsTextItem       *portText;
    QLineEdit               *portWidget;
    QGraphicsProxyWidget    *portProxy;


    QGraphicsPixmapItem     *connectButt;
    bool                    connectButtAct = false;
    QGraphicsPixmapItem     *backButt;
    bool                    backButtAct = false;

public:
    void scenePress(int x, int y);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void connectClicked(QHostAddress addr, int port);
    void backClicked();
};

#endif // CONNECTTO_H
