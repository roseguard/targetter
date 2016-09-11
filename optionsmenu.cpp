#include "optionsmenu.h"

optionsMenuScene::optionsMenuScene(optSaver *optionAddr, QWidget *parent) : QGraphicsScene(parent)
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
    this->addItem(background);
    this->setBackgroundBrush(QColor("black"));

    pix = QPixmap(":img/gui/header.png"); // NO IMAGE!!!!!!!!!!!!!
    pix = pix.scaled(defWidth, defHeight);
    header = new QGraphicsPixmapItem(pix);
    header->setPos(0,0);
    this->addItem(header);

    QFont textFont("Times", defHeight/2, QFont::Bold,true);

    addrText = new QGraphicsTextItem("Address");
    addrText->setDefaultTextColor(QColor("white"));
    addrText->setFont(textFont);
    addrText->setPos(defPos, lastHeight);

    addrWidget = new QLineEdit("");
    addrWidget->setFont(textFont);
    addrProxy = new QGraphicsProxyWidget;
    addrProxy->setWidget(addrWidget);
    addrProxy->setPos(defPos*2.5, lastHeight);

    pix = QPixmap(":img/gui/defaultOff.png");
    pix = pix.scaled(defWidth, defHeight);
    addrButt = new QGraphicsPixmapItem(pix);
    addrButt->setData(0, "addrButt");
    addrButt->setPos(defPos*5.5, lastHeight);

    this->addItem(addrText);
    this->addItem(addrProxy);
    this->addItem(addrButt);

    lastHeight+=defHeight*1.2;

    portText = new QGraphicsTextItem("Port");
    portText->setDefaultTextColor(QColor("white"));
    portText->setFont(textFont);
    portText->setPos(defPos, lastHeight);

    portWidget = new QLineEdit("");
    portWidget->setFont(textFont);
    portProxy = new QGraphicsProxyWidget;
    portProxy->setWidget(portWidget);
    portProxy->setPos(defPos*2.5, lastHeight);

    pix = QPixmap(":img/gui/defaultOff.png");
    pix = pix.scaled(defWidth, defHeight);
    portButt = new QGraphicsPixmapItem(pix);
    portButt->setData(0, "portButt");
    portButt->setPos(defPos*5.5, lastHeight);

    this->addItem(portText);
    this->addItem(portProxy);
    this->addItem(portButt);

    lastHeight+=defHeight*1.2;

    musicText = new QGraphicsTextItem("Music");
    musicText->setDefaultTextColor(QColor("white"));
    musicText->setFont(textFont);
    musicText->setPos(defPos, lastHeight);

    musicWidget = new QSlider(Qt::Horizontal);
    musicWidget->setFixedSize(defWidth, defHeight/2);
    musicProxy = new QGraphicsProxyWidget;
    musicProxy->setWidget(musicWidget);
    musicProxy->setPos(defPos*2.5, lastHeight);
    musicProxy->setScale(2);

    this->addItem(musicText);
    this->addItem(musicProxy);

    lastHeight+=defHeight*1.2;

    effectsText = new QGraphicsTextItem("Effects");
    effectsText->setDefaultTextColor(QColor("white"));
    effectsText->setFont(textFont);
    effectsText->setPos(defPos, lastHeight);

    effectsWidget = new QSlider(Qt::Horizontal);
    effectsWidget->setFixedSize(defWidth, defHeight/2);
    effectsProxy = new QGraphicsProxyWidget;
    effectsProxy->setWidget(effectsWidget);
    effectsProxy->setPos(defPos*2.5, lastHeight);
    effectsProxy->setScale(2);

    this->addItem(effectsText);
    this->addItem(effectsProxy);

    lastHeight+=defHeight*1.2;

    nickText = new QGraphicsTextItem("Nick");
    nickText->setDefaultTextColor(QColor("white"));
    nickText->setFont(textFont);
    nickText->setPos(defPos, lastHeight);

    nickWidget = new QLineEdit("");
    nickWidget->setFont(textFont);
    nickProxy = new QGraphicsProxyWidget;
    nickProxy->setWidget(nickWidget);
    nickProxy->setPos(defPos*2.5, lastHeight);

    this->addItem(nickText);
    this->addItem(nickProxy);

    lastHeight+=defHeight*1.2;

    pix = QPixmap(":img/gui/acceptOff.png").scaled(defWidth, defHeight);
    acceptButt = new QGraphicsPixmapItem(pix);
    acceptButt->setPos(defPos, lastHeight);
    acceptButt->setData(0, "acceptButt");

    pix = QPixmap(":img/gui/cancelOff.png").scaled(defWidth, defHeight);
    cancelButt = new QGraphicsPixmapItem(pix);
    cancelButt->setPos(defPos*2+defWidth, lastHeight);
    cancelButt->setData(0, "cancelButt");

    this->addItem(acceptButt);
    this->addItem(cancelButt);

    addrWidget->setText(options->addr.toString());
    portWidget->setText(QString::number(options->port));
    effectsWidget->setValue(options->effects);
    musicWidget->setValue(options->music);
    nickWidget->setText(options->name);
}

void optionsMenuScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="addrButt")
        {
            if(addrButtAct)
            {
                setDefaultAddr();
            }
        }
        else if(datas=="portButt")
        {
            if(portButtAct)
            {
                setDefaultPort();
            }
        }
        else if(datas=="acceptButt")
        {
            if(acceptButtAct)
            {
                options->addr = QHostAddress(addrWidget->text());
                options->port = portWidget->text().toInt();
                options->effects = effectsWidget->value();
                options->music = musicWidget->value();
                options->name = nickWidget->text();
                emit this->acceptClicked();
                return;
            }
        }
        else if(datas=="cancelButt")
        {
            if(cancelButtAct)
            {
                emit this->cancelClicked();
                return;
            }
        }
    }
    addrButtAct =   false;
    portButtAct =   false;
    acceptButtAct = false;
    cancelButtAct = false;

    QDesktopWidget desk;
    int defWidth = desk.width() / 4;
    int defHeight = desk.height() / 10;

    QPixmap pix(":img/gui/defaultOff.png");
    pix = pix.scaled(defWidth, defHeight);
    addrButt->setPixmap(pix);

    pix = QPixmap(":img/gui/defaultOff.png");
    pix = pix.scaled(defWidth, defHeight);
    portButt->setPixmap(pix);

    pix = QPixmap(":img/gui/acceptOff.png");
    pix = pix.scaled(defWidth, defHeight);
    acceptButt->setPixmap(pix);

    pix = QPixmap(":img/gui/cancelOff.png");
    pix = pix.scaled(defWidth, defHeight);
    cancelButt->setPixmap(pix);
}

void optionsMenuScene::scenePress(int x, int y)
{
    QGraphicsItem *item = itemAt(x,y, QTransform());
    if(item)
    {
        QString datas = item->data(0).toString();
        if(datas=="addrButt")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 10;
            QPixmap pix(":img/gui/defaultOn.png");
            pix = pix.scaled(defWidth, defHeight);
            addrButt->setPixmap(pix);
            addrButtAct = true;
        }
        else if(datas=="portButt")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 10;
            QPixmap pix(":img/gui/defaultOn.png");
            pix = pix.scaled(defWidth, defHeight);
            portButt->setPixmap(pix);
            portButtAct = true;
        }
        else if(datas=="acceptButt")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 10;
            QPixmap pix(":img/gui/acceptOn.png");
            pix = pix.scaled(defWidth, defHeight);
            acceptButt->setPixmap(pix);
            acceptButtAct = true;
        }
        else if(datas=="cancelButt")
        {
            QDesktopWidget desk;
            int defWidth = desk.width() / 4;
            int defHeight = desk.height() / 10;
            QPixmap pix(":img/gui/cancelOn.png");
            pix = pix.scaled(defWidth, defHeight);
            cancelButt->setPixmap(pix);
            cancelButtAct = true;
        }
    }
}

void optionsMenuScene::setDefaultAddr()
{
    QString locIP;
    QList<QHostAddress> addr = QNetworkInterface::allAddresses();
    for(int i = 0; i < addr.length(); i++)
    {
        if(addr.at(i).isInSubnet(QHostAddress("0.0.0.0"),0))
        {
            if(addr.at(i).isLoopback())
                continue;
            addrWidget->setText(addr.at(i).toString());
            return;
        }
    }
    addrWidget->setText("127.0.0.1");
}

void optionsMenuScene::setDefaultPort()
{
    this->portWidget->setText("21034");
}

optSaver optionsMenuScene::getOptions()
{
    return *options;
}

