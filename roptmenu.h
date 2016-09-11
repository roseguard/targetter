#ifndef ROPTMENU_H
#define ROPTMENU_H

#include <QObject>
#include <QHostAddress>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLineEdit>
#include <QGraphicsTextItem>

#include "foropt.h"

class roptmenu : public QGraphicsScene
{
public:
    roptmenu(optSaver *_options);

    optSaver *options;
};

#endif // ROPTMENU_H
