#include "hostacceptdeny.h"
#include <QDebug>

hostAcceptDeny::hostAcceptDeny(QWidget *parent)  : QGraphicsScene(parent)
{

    QDesktopWidget desk;
    int lastHeight = desk.height()/5;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;
    int defPos = desk.width()/2.5;
    int posHeight = desk.height()-(0.025*desk.height());
    int posWidth = desk.width()-(0.025*desk.width());

    QPixmap backPix(":img/gui/background.jpg");
    backPix = backPix.scaled(desk.width()-(0.025*desk.width()), desk.height()-(0.025*desk.height()));
    background = new QGraphicsPixmapItem(backPix);
    background->setData(0, "background");
    this->setBackgroundBrush(QColor("black"));

    textInfo = new QGraphicsTextItem;
    QFont textFont("Times", defHeight/4, QFont::Bold,true);
    textInfo->setFont(textFont);
    QString textHtml = "<div style='background-color:#b77600;'>Some one try to connect to you</div>";
    textHtml.append("<div style='background-color:#b77600;'>Waiting for his name</div>");
    textInfo->setHtml(textHtml);
    textInfo->setPos((posWidth/2)-(textInfo->boundingRect().width()/2),
                     (posHeight/2)-(textInfo->boundingRect().height()/2));

    QPixmap pix(":img/gui/acceptOff.png");
    pix = pix.scaled(defWidth, defHeight);
    accept = new QGraphicsPixmapItem(pix);
    accept->setPos(0, posHeight*0.7);
    lastHeight+=defHeight*2;
    accept->setData(0, "accept");

    pix = QPixmap(":img/gui/startOff.png");
    pix = pix.scaled(defWidth, defHeight);
    deny = new QGraphicsPixmapItem(pix);
    deny->setPos(posWidth-defWidth, posHeight*0.7);
    lastHeight+=defHeight*2;
    deny->setData(0, "deny");

    this->addItem(background);
    this->addItem(accept);
    this->addItem(deny);
    this->addItem(textInfo);
}

void hostAcceptDeny::scenePress(int x, int y)
{
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="accept")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/acceptOn.png");
            pix = pix.scaled(defWidth, defHeight);
            accept->setPixmap(pix);
            acceptAct = true;
        }
        else if(datas=="deny")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 8;
            QPixmap pix(":img/gui/startOn.png");
            pix = pix.scaled(defWidth, defHeight);
            deny->setPixmap(pix);
            denyAct = true;
        }
    }
}

void hostAcceptDeny::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="accept")
        {
            if(acceptAct)
            {
                emit this->acceptClicked();
                return;
            }
        }
        else if(datas=="deny")
        {
            if(denyAct)
            {
                emit this->denyClicked();
                return;
            }
        }
    }
    acceptAct = false;
    denyAct = false;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 8;

    QPixmap pix(":img/gui/acceptOff.png");
    pix = pix.scaled(defWidth, defHeight);
    accept->setPixmap(pix);

    pix = QPixmap(":img/gui/startOff.png");
    pix = pix.scaled(defWidth, defHeight);
    deny->setPixmap(pix);
}
