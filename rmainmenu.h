#ifndef RMAINMENU_H
#define RMAINMENU_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QGraphicsTextItem>

class RMainMenu;
class multButt;
class optButt;
class exitButt;

class RMainMenu : public QGraphicsScene
{
    Q_OBJECT
public:
    RMainMenu(QWidget *parent = 0);

    QGraphicsPixmapItem *back;

    QGraphicsTextItem *sceneName;
    multButt *multObj;
    optButt *optObj;
    exitButt *exitObj;

signals:
    void multSig();
    void optSig();
    void exitSig();
};

class multButt : public QGraphicsPixmapItem
{
public:
    RMainMenu *scene;
    multButt(RMainMenu *_scene , QString img, QWidget *parent = 0) : QGraphicsPixmapItem(QPixmap(img)){scene = _scene;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        emit scene->multSig();
    }
};

class optButt : public QGraphicsPixmapItem
{
public:
    RMainMenu *scene;
    optButt(RMainMenu *_scene , QString img, QWidget *parent = 0) : QGraphicsPixmapItem(QPixmap(img)){scene = _scene;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        emit scene->optSig();
    }
};

class exitButt : public QGraphicsPixmapItem
{
public:
    RMainMenu *scene;
    exitButt(RMainMenu *_scene , QString img, QWidget *parent = 0) : QGraphicsPixmapItem(QPixmap(img)){scene = _scene;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        emit scene->exitSig();
    }
};

#endif // RMAINMENU_H
