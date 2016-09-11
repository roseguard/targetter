#include "gamescene.h"
#include <QDebug>

gameScene::gameScene(QGraphicsView *parView, bool isHost, QWidget *parent) : QGraphicsScene(parent)
{
    QDesktopWidget desk;
    int defWidth = desk.height() / 10;
    int defHeight = desk.width() / 10;
    int posHeight = desk.height()-(0.025*desk.height());
    int posWidth = desk.width()-(0.025*desk.width());

    iHost = isHost;

    QPixmap pix;

    pix = QPixmap(":/img/game/fields/fieldSteel.png").scaled(defWidth, defHeight);
    for(int i = 0; i < posHeight-defHeight; i+=defHeight)
    {
        for(int j = 0; j < posWidth-defWidth; j+=defWidth)
        {
            fieldCell *oneCell = new fieldCell(0, pix);
            oneCell->setPos(j, i);
            cellsVector.append(oneCell);
            addItem(oneCell);
        }
    }

    pix = QPixmap(":/img/game/actors/canadian.png").scaled(defWidth, defHeight);
    player = new QGraphicsPixmapItem(pix);
    addItem(player);
    viewer = parView;
    if(iHost)
        player->setPos(0,0);
    else
        player->setPos(cellsVector.last()->pos());

    pix = QPixmap(":/img/game/actors/hipster.png").scaled(defWidth, defHeight);
    enemy = new QGraphicsPixmapItem(pix);
    enemy->setPos(cellsVector.last()->pos());
    addItem(enemy);

    qsrand(time(NULL));

    timeForTarget = new QTimer(this);
    connect(timeForTarget, SIGNAL(timeout()), this, SLOT(createRandomTarget()));
    timeForTarget->start(100);
}


void gameScene::keyPressEvent(QKeyEvent *event)
{
    if(isGameEnded)
    {
        if(event->text()=="e")
        {
            for(int i = 0; i < targetExpl.length(); i++)
                targetExpl.at(i)->stop();
            for(int i = 0; i < timersToClean.length(); i++)
            {
                timersToClean.at(i)->stop();
                timersToClean.at(i)->setSingleShot(false);
                timersToClean.at(i)->blockSignals(true);
            }
            timeForTarget->stop();
            emit this->gameEnded();
            return;
        }
    }

    QDesktopWidget desk;
    int defWidth = desk.height() / 10;
    int defHeight = desk.width() / 10;
    int posHeight = desk.height()-(0.025*desk.height());
    int posWidth = desk.width()-(0.025*desk.width());

    if(event->text()      == "w")
    {
        int x = 0;
        int y = -defHeight;
        if(player->x() + x < posWidth-defWidth && player->x() + x >= 0 &&
           player->y() + y < posHeight-defHeight && player->y() + y >= 0)
        {
            player->moveBy(x, y);
            emit this->playerMoved(player->x(), player->y());
        }
    }
    else if(event->text() == "s")
    {
        int x = 0;
        int y = defHeight;
        if(player->x() + x < posWidth-defWidth && player->x() + x >= 0 &&
           player->y() + y < posHeight-defHeight && player->y() + y >= 0)
        {
            player->moveBy(x, y);
            emit this->playerMoved(player->x(), player->y());
        }
    }
    else if(event->text() == "a")
    {
        int x = -defWidth;
        int y = 0;
        if(player->x() + x < posWidth-defWidth && player->x() + x >= 0 &&
           player->y() + y < posHeight-defHeight && player->y() + y >= 0)
        {
            player->moveBy(x, y);
            emit this->playerMoved(player->x(), player->y());
        }
    }
    else if(event->text() == "d")
    {
        int x = defWidth;
        int y = 0;
        if(player->x() + x < posWidth-defWidth && player->x() + x >= 0 &&
           player->y() + y < posHeight-defHeight && player->y() + y >= 0)
        {
            player->moveBy(x, y);
            emit this->playerMoved(player->x(), player->y());
        }
    }
}

void gameScene::setEnemyPos(int x, int y)
{
    enemy->setPos(x, y);
}



void gameScene::createNewTargeting(int x, int y)
{
    QDesktopWidget desk;
    int defWidth = desk.height() / 10;
    int defHeight = desk.width() / 10;

    if(iHost)
    {
        QPixmap pix = QPixmap(":img/game/effects/targeting.png").scaled(defWidth, defHeight);
        QGraphicsPixmapItem *danger = new QGraphicsPixmapItem(pix);
        targets.append(danger);
        QTimer *timer = new QTimer(this);
        timer->singleShot(200, this, SLOT(blowTarget()));
        targetExpl.append(timer);
        QPointF tempPos = cellsVector.at(qrand()%cellsVector.length())->pos();
        danger->setPos(tempPos);
        addItem(danger);
        emit newTargetting(tempPos.x(), tempPos.y());
    }
    else
    {
        QPixmap pix = QPixmap(":img/game/effects/targeting.png").scaled(defWidth, defHeight);
        QGraphicsPixmapItem *danger = new QGraphicsPixmapItem(pix);
        targets.append(danger);
        QTimer *timer = new QTimer(this);
        timer->singleShot(300, this, SLOT(blowTarget()));
        targetExpl.append(timer);
        danger->setPos(x, y);
        addItem(danger);
    }
}

void gameScene::blowTarget()
{
    QDesktopWidget desk;
    int defWidth = desk.height() / 10;
    int defHeight = desk.width() / 10;

    QPixmap pix = QPixmap(":img/game/effects/explosion.png").scaled(defWidth, defHeight);
    QTimer *timeToClean = new QTimer(this);
    timeToClean->singleShot(200, this, SLOT(clearTarget()));
    timersToClean.append(timeToClean);
    int i = 0;
    for(; targets.at(i)->data(i).toString()=="blowed"; i++);
    targets.at(i)->setPixmap(pix);
    targets.at(i)->setData(0, "blowed");
    if(player->x() == targets.first()->x() &&
       player->y() == targets.first()->y())
    {
        endGame();
    }
}

void gameScene::createRandomTarget()
{
    createNewTargeting(0,0);
}

void gameScene::clearTarget()
{
    qDebug() << "start clean";
    delete targets.first();
    this->removeItem(targets.first());
    targets.removeFirst();
    qDebug() << "target removed";
    targetExpl.first()->stop();
    delete targetExpl.first();
    targetExpl.removeFirst();
    qDebug() << "expl removed";
    timersToClean.first()->stop();
    delete timersToClean.first();
    timersToClean.removeFirst();
    qDebug() << "timer removed";
}

bool gameScene::isHost()
{
    return iHost;
}

void gameScene::endGame()
{
    for(int i = 0; i < targetExpl.length(); i++)
        targetExpl.at(i)->stop();
    for(int i = 0; i < timersToClean.length(); i++)
    {
        timersToClean.at(i)->stop();
        timersToClean.at(i)->setSingleShot(false);
        timersToClean.at(i)->blockSignals(true);
    }
    timeForTarget->stop();

    QDesktopWidget desk;
    int defWidth = desk.height() / 10;
    int defHeight = desk.width() / 10;
    int posHeight = desk.height()-(0.025*desk.height());
    int posWidth = desk.width()-(0.025*desk.width());

    isGameEnded = true;
    QFont textFont("Times", defHeight/6, QFont::Bold,true);

    QGraphicsTextItem *addrText = new QGraphicsTextItem("Game ended, press any key key to back to main menu");
    addrText->setDefaultTextColor(QColor("white"));
    addrText->setFont(textFont);
    addrText->setPos((posWidth/4)-defWidth, (posHeight/2));

    addItem(addrText);
}

void gameScene::otherPlayerLoosed()
{
    for(int i = 0; i < targetExpl.length(); i++)
        targetExpl.at(i)->stop();
    for(int i = 0; i < timersToClean.length(); i++)
    {
        timersToClean.at(i)->stop();
        timersToClean.at(i)->setSingleShot(false);
        timersToClean.at(i)->blockSignals(true);
    }
    timeForTarget->stop();

    QDesktopWidget desk;
    int defWidth = desk.height() / 10;
    int defHeight = desk.width() / 10;
    int posHeight = desk.height()-(0.025*desk.height());
    int posWidth = desk.width()-(0.025*desk.width());

    isGameEnded = true;
    QFont textFont("Times", defHeight/6, QFont::Bold,true);

    QGraphicsTextItem *addrText = new QGraphicsTextItem("Other player loosed, press any key key to back to main menu");
    addrText->setDefaultTextColor(QColor("white"));
    addrText->setFont(textFont);
    addrText->setPos((posWidth/4)-defWidth, (posHeight/2));

    addItem(addrText);
}

void gameScene::emitNetworkMessage(QString message)
{
    emit itemNetworkMessage(message);
}
