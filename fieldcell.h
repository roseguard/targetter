#ifndef FIELDCELL_H
#define FIELDCELL_H


#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QDesktopWidget>

#include "creatureitem.h"
#include "objectitem.h"

class objectItem;

class fieldCell : public QGraphicsPixmapItem
{
public:
    fieldCell(int fieldType ,const QPixmap &pixmap, objectItem *obj = 0, creatureItem *actor = 0);
public:
    objectItem*     hasObject();
    creatureItem*   hasActor();
    int             getFieldType();
    void            setFieldType();

private:
    int             *fieldType;
    creatureItem    *creature;
    objectItem      *cellObject;
};

#endif // FIELDCELL_H
