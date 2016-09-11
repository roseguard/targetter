#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

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

#include <QHostAddress>
#include <QNetworkInterface>

#include "foropt.h"

class optionsMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    optionsMenuScene(optSaver *optionsAddr, QWidget *parent = 0);
private:
    optSaver *options;

    QGraphicsPixmapItem     *background;
    QGraphicsPixmapItem     *header;

    QGraphicsTextItem       *addrText;
    QLineEdit               *addrWidget;
    QGraphicsProxyWidget    *addrProxy;
    QGraphicsPixmapItem     *addrButt;
    bool                    addrButtAct = false;

    QGraphicsTextItem       *portText;
    QLineEdit               *portWidget;
    QGraphicsProxyWidget    *portProxy;
    QGraphicsPixmapItem     *portButt;
    bool                    portButtAct = false;

    QGraphicsTextItem       *musicText;
    QSlider                 *musicWidget;
    QGraphicsProxyWidget    *musicProxy;

    QGraphicsTextItem       *effectsText;
    QSlider                 *effectsWidget;
    QGraphicsProxyWidget    *effectsProxy;

    QGraphicsTextItem       *nickText;
    QLineEdit               *nickWidget;
    QGraphicsProxyWidget    *nickProxy;

    QGraphicsPixmapItem     *acceptButt;
    bool                    acceptButtAct = false;
    QGraphicsPixmapItem     *cancelButt;
    bool                    cancelButtAct = false;

public:
    void scenePress(int x, int y);
    void setDefaultAddr();
    void setDefaultPort();
    optSaver getOptions();

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void acceptClicked();
    void cancelClicked();
};

#endif // OPTIONSMENU_H
