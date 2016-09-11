#ifndef OBJECTITEM_H
#define OBJECTITEM_H

#include <QGraphicsPixmapItem>
#include "gamescene.h"
#include "fieldcell.h"

class gameScene;
class fieldCell;

class objectItem : public QGraphicsPixmapItem
{
public:
    objectItem(const QPixmap &pix, gameScene *parentScene, fieldCell *parentCell);

private:
    gameScene *_parentScene;
    fieldCell *_parentCell;
    QPixmap   pix;
};

#endif // OBJECTITEM_H
