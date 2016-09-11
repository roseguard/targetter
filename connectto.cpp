#include "connectto.h"

connectToScene::connectToScene(optSaver *optionAddr, QWidget *parent) : QGraphicsScene(parent)
{
    options = optionAddr;

    QDesktopWidget desk;
    int lastHeight = desk.height()/7;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 10;
    int defPos = desk.width()/8;

    QPixmap pix(":img/gui/background.jpg");
    pix = pix.scaled(desk.width()-(0.025*desk.width()), desk.height()-(0.025*desk.height()));
    background = new QGraphicsPixmapItem(pix);
    background->setData(0, "background");
    addItem(background);
    setBackgroundBrush(QColor("black"));

    pix = QPixmap(":img/gui/header.png"); // NO IMAGE!!!!!!!!!!!!!
    pix = pix.scaled(defWidth, defHeight);
    header = new QGraphicsPixmapItem(pix);
    header->setPos(0,0);
    addItem(header);

    QFont textFont("Times", defHeight/2, QFont::Bold,true);

    addrText = new QGraphicsTextItem("Address");
    addrText->setDefaultTextColor(QColor("white"));
    addrText->setFont(textFont);
    addrText->setPos(defPos, lastHeight);

    addrWidget = new QLineEdit("192.168.0.105");
    addrWidget->setFont(textFont);
    addrProxy = new QGraphicsProxyWidget;
    addrProxy->setWidget(addrWidget);
    addrProxy->setPos(defPos*2.5, lastHeight);

    addItem(addrText);
    addItem(addrProxy);

    lastHeight+=defHeight*2;

    portText = new QGraphicsTextItem("Port");
    portText->setDefaultTextColor(QColor("white"));
    portText->setFont(textFont);
    portText->setPos(defPos, lastHeight);

    portWidget = new QLineEdit("");
    portWidget->setFont(textFont);
    portProxy = new QGraphicsProxyWidget;
    portProxy->setWidget(portWidget);
    portProxy->setPos(defPos*2.5, lastHeight);


    addItem(portText);
    addItem(portProxy);

    lastHeight+=defHeight*2;

    pix = QPixmap(":img/gui/connectToOff.png").scaled(defWidth, defHeight);
    connectButt = new QGraphicsPixmapItem(pix);
    connectButt->setPos(defPos, lastHeight);
    connectButt->setData(0, "connectButt");

    pix = QPixmap(":img/gui/backOff.png").scaled(defWidth, defHeight);
    backButt = new QGraphicsPixmapItem(pix);
    backButt->setPos(defPos*2+defWidth, lastHeight);
    backButt->setData(0, "backButt");

    addItem(connectButt);
    addItem(backButt);

    portWidget->setText(QString::number(options->port));
}

void connectToScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        qDebug() << datas;
        if(datas=="connectButt")
        {
            if(connectButtAct)
            {
                emit this->connectClicked(QHostAddress(addrWidget->text()), portWidget->text().toInt());
                return;
            }
        }
        else if(datas=="backButt")
        {
            if(backButtAct)
            {
                emit this->backClicked();
                return;
            }
        }
    }
    connectButtAct =   false;
    backButtAct =   false;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 10;

    QPixmap pix(":img/gui/connectToOff.png");
    pix = pix.scaled(defWidth, defHeight);
    connectButt->setPixmap(pix);

    pix = QPixmap(":img/gui/backOff.png");
    pix = pix.scaled(defWidth, defHeight);
    backButt->setPixmap(pix);
}

void connectToScene::scenePress(int x, int y)
{
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="connectButt")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 10;
            QPixmap pix(":img/gui/connectToOn.png");
            pix = pix.scaled(defWidth, defHeight);
            connectButt->setPixmap(pix);
            connectButtAct = true;
        }
        else if(datas=="backButt")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 10;
            QPixmap pix(":img/gui/backOn.png");
            pix = pix.scaled(defWidth, defHeight);
            backButt->setPixmap(pix);
            backButtAct = true;
        }
    }
}
