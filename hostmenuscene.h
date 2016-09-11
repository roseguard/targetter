#ifndef HOSTMENUSCENE_H
#define HOSTMENUSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QGraphicsTextItem>
#include "foropt.h"

class hostMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    hostMenuScene(optSaver *options , QWidget *parent = 0);
private:
    QGraphicsPixmapItem     *background;
    QGraphicsPixmapItem     *header;

    QGraphicsPixmapItem     *hostButt;
    bool                    hostButtAct = false;
    QGraphicsPixmapItem     *optionsButt;
    bool                    optionsButtAct = false;
    QGraphicsPixmapItem     *backButt;
    bool                    backButtAct = false;
    QGraphicsTextItem       *hostInfo;

    optSaver                *_options;
    bool                    isHosted = false;
public:
    void scenePress(int x, int y);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void hostClicked();
    void hostClose();
    void optionsClicked();
    void backClicked();
};

#endif // HOSTMENUSCENE_H
