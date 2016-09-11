#include "mainmenuscene.h"
#include <QDebug>

mainMenuScene::mainMenuScene(QWidget *parent)  : QGraphicsScene(parent)
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

    QPixmap pix(":img/gui/startOff.png");
    pix = pix.scaled(defWidth, defHeight);
    start = new QGraphicsPixmapItem(pix);
    start->setPos(defPos, lastHeight);
    lastHeight+=defHeight*2;
    start->setData(0, "start");

    pix = QPixmap(":img/gui/optionOff.png");
    pix = pix.scaled(defWidth, defHeight);
    options = new QGraphicsPixmapItem(pix);
    options->setPos(defPos, lastHeight);
    lastHeight+=defHeight*2;
    options->setData(0, "options");

    pix = QPixmap(":img/gui/exitOff.png");
    pix = pix.scaled(defWidth, defHeight);
    exit = new QGraphicsPixmapItem(pix);
    exit->setPos(defPos, lastHeight);
    lastHeight+=defHeight;
    exit->setData(0, "exit");

    this->addItem(background);
    this->addItem(start);
    this->addItem(options);
    this->addItem(exit);
}

void mainMenuScene::scenePress(int x, int y)
{
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="start")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/startOn.png");
            pix = pix.scaled(defWidth, defHeight);
            start->setPixmap(pix);
            startAct = true;
        }
        else if(datas=="options")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/optionOn.png");
            pix = pix.scaled(defWidth, defHeight);
            options->setPixmap(pix);
            optionsAct = true;
        }
        else if(datas=="exit")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/exitOn.png");
            pix = pix.scaled(defWidth, defHeight);
            exit->setPixmap(pix);
            exitAct = true;
        }
    }
}

void mainMenuScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="start")
        {
            if(startAct)
            {
                emit this->startClicked();
                return;
            }
        }
        else if(datas=="options")
        {
            if(optionsAct)
            {
                emit this->optionsClicked();
                return;
            }
        }
        else if(datas=="exit")
        {
            if(exitAct)
            {
                emit this->exitClicked();
                return;
            }
        }
    }
    startAct = false;
    optionsAct = false;
    exitAct = false;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;

    QPixmap pix(":img/gui/startOff.png");
    pix = pix.scaled(defWidth, defHeight);
    start->setPixmap(pix);

    pix = QPixmap(":img/gui/optionOff.png");
    pix = pix.scaled(defWidth, defHeight);
    options->setPixmap(pix);

    pix = QPixmap(":img/gui/exitOff.png");
    pix = pix.scaled(defWidth, defHeight);
    exit->setPixmap(pix);
}
