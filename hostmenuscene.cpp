#include "hostmenuscene.h"
#include "foropt.h"
#include <QDebug>
#include <QGraphicsWidget>

hostMenuScene::hostMenuScene(optSaver *options , QWidget *parent)  : QGraphicsScene(parent)
{
    _options = options;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;

    int tempWidth = desk.width()- (0.025*desk.width());
    int tempHeight = desk.height()-(0.025*desk.height());

    QPixmap backPix(":img/gui/background.jpg");
    backPix = backPix.scaled(tempWidth, tempHeight);
    background = new QGraphicsPixmapItem(backPix);
    background->setData(0, "background");
    this->setBackgroundBrush(QColor("black"));

    QPixmap pix(":img/gui/hostOff.png");
    pix = pix.scaled(defWidth, defHeight);
    hostButt = new QGraphicsPixmapItem(pix);
    hostButt->setPos(0, tempHeight/2 + tempHeight*0.2);
    hostButt->setData(0, "host");

    pix = QPixmap(":img/gui/optionOff.png");
    pix = pix.scaled(defWidth, defHeight);
    optionsButt = new QGraphicsPixmapItem(pix);
    optionsButt->setPos(tempWidth-pix.width(), 0.2*tempHeight);
    optionsButt->setData(0, "options");

    pix = QPixmap(":img/gui/backOff.png");
    pix = pix.scaled(defWidth, defHeight);
    backButt = new QGraphicsPixmapItem(pix);
    backButt->setPos(tempWidth-pix.width(), tempHeight - 0.3*tempHeight);
    backButt->setData(0, "back");

    QString forHostInfo("<div style='background-color:#b77600;'>Will start on addr : " + _options->addr.toString() + "</div>");
    forHostInfo.append("<div style='background-color:#b77600;'>Will start on port : " + QString::number(_options->port) + "</div>");
    hostInfo = new QGraphicsTextItem;
    hostInfo->setHtml(forHostInfo);
    QFont textFont("Times", defHeight/4, QFont::Bold,true);
    hostInfo->setFont(textFont);
    hostInfo->setPos(0, tempHeight*0.2);

    this->addItem(background);
    this->addItem(hostButt);
    this->addItem(optionsButt);
    this->addItem(backButt);
    this->addItem(hostInfo);
}

void hostMenuScene::scenePress(int x, int y)
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
            hostButt->setPixmap(pix);
            hostButtAct = true;
        }
        else if(datas=="options")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/optionOn.png");
            pix = pix.scaled(defWidth, defHeight);
            optionsButt->setPixmap(pix);
            optionsButtAct = true;
        }
        else if(datas=="back")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/backOn.png");
            pix = pix.scaled(defWidth, defHeight);
            backButt->setPixmap(pix);
            backButtAct = true;
        }
    }
}

void hostMenuScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="host")
        {
            if(hostButtAct)
            {
                if(!isHosted)
                {
                    emit this->hostClicked();
                    QString forHostInfo("<div style='background-color:#ffff00;'>Started on addr : " + _options->addr.toString() + "</div>");
                    forHostInfo.append("<div style='background-color:#ffff00;'>Started on port : " + QString::number(_options->port) + "</div>");
                    forHostInfo.append("<div style='background-color:#ffff00;'>Waiting for connect</div>");
                    hostInfo->setHtml(forHostInfo);
                    isHosted = true;
                }
                else
                {
                    emit this->hostClose();
                    QString forHostInfo("<div style='background-color:#b77600;'>Will start on addr : " + _options->addr.toString() + "</div>");
                    forHostInfo.append("<div style='background-color:#b77600;'>Will start on port : " + QString::number(_options->port) + "</div>");
                    hostInfo->setHtml(forHostInfo);
                    isHosted = false;
                }
            }
        }
        else if(datas=="options")
        {
            if(optionsButtAct)
            {
                emit this->optionsClicked();
                return;
            }
        }
        else if(datas=="back")
        {
            if(backButtAct)
            {
                emit this->backClicked();
                return;
            }
        }
    }
    hostButtAct = false;
    optionsButtAct = false;
    backButtAct = false;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;

    QPixmap pix(":img/gui/hostOff.png");
    pix = pix.scaled(defWidth, defHeight);
    hostButt->setPixmap(pix);

    pix = QPixmap(":img/gui/optionOff.png");
    pix = pix.scaled(defWidth, defHeight);
    optionsButt->setPixmap(pix);

    pix = QPixmap(":img/gui/backOff.png");
    pix = pix.scaled(defWidth, defHeight);
    backButt->setPixmap(pix);
}
