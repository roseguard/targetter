#include "multiplayermenu.h"

#include "mainmenuscene.h"
#include <QDebug>

multiplayerMenuScene::multiplayerMenuScene(QWidget *parent)  : QGraphicsScene(parent)
{
    QDesktopWidget desk;
    int lastHeight = desk.height()/5;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;
    int defPos = desk.width()/2.5;

    QPixmap backPix(":img/gui/background.jpg");
    backPix = backPix.scaled(desk.width()-(0.025*desk.width()), desk.height()-(0.025*desk.height()));
    background = new QGraphicsPixmapItem(backPix);
    background->setData(0, "background");
    this->setBackgroundBrush(QColor("black"));

    QPixmap pix(":img/gui/hostOff.png");
    pix = pix.scaled(defWidth, defHeight);
    host = new QGraphicsPixmapItem(pix);
    host->setPos(defPos, lastHeight);
    lastHeight+=defHeight*2;
    host->setData(0, "host");

    pix = QPixmap(":img/gui/connectToOff.png");
    pix = pix.scaled(defWidth, defHeight);
    connectTo = new QGraphicsPixmapItem(pix);
    connectTo->setPos(defPos, lastHeight);
    lastHeight+=defHeight*2;
    connectTo->setData(0, "connectTo");

    pix = QPixmap(":img/gui/backOff.png");
    pix = pix.scaled(defWidth, defHeight);
    back = new QGraphicsPixmapItem(pix);
    back->setPos(defPos, lastHeight);
    lastHeight+=defHeight;
    back->setData(0, "back");

    this->addItem(background);
    this->addItem(host);
    this->addItem(connectTo);
    this->addItem(back);
}

void multiplayerMenuScene::scenePress(int x, int y)
{
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="host")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/hostOn.png");
            pix = pix.scaled(defWidth, defHeight);
            host->setPixmap(pix);
            hostAct = true;
        }
        else if(datas=="connectTo")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/connectToOn.png");
            pix = pix.scaled(defWidth, defHeight);
            connectTo->setPixmap(pix);
            connectToAct = true;
        }
        else if(datas=="back")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/backOn.png");
            pix = pix.scaled(defWidth, defHeight);
            back->setPixmap(pix);
            backAct = true;
        }
    }
}

void multiplayerMenuScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="host")
        {
            if(hostAct)
            {
                emit this->hostClicked();
                return;
            }
        }
        else if(datas=="connectTo")
        {
            if(connectToAct)
            {
                emit this->connectToClicked();
                return;
            }
        }
        else if(datas=="back")
        {
            if(backAct)
            {
                emit this->backClicked();
                return;
            }
        }
    }
    hostAct = false;
    connectToAct = false;
    backAct = false;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;

    QPixmap pix(":img/gui/hostOff.png");
    pix = pix.scaled(defWidth, defHeight);
    host->setPixmap(pix);

    pix = QPixmap(":img/gui/connectToOff.png");
    pix = pix.scaled(defWidth, defHeight);
    connectTo->setPixmap(pix);

    pix = QPixmap(":img/gui/backOff.png");
    pix = pix.scaled(defWidth, defHeight);
    back->setPixmap(pix);
}

