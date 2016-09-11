#include "basewindow.h"
#include "redeclare.h"
#include <QSqlError>

baseWindow::baseWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    this->showFullScreen();

    QCursor curs = QCursor(QPixmap("/home/arhcitect/myWork/img/gui/cursor.png"));
    this->setCursor(curs);

    options = new optSaver;

    QList<QHostAddress> addrList = QNetworkInterface::allAddresses();
    while(1)
    {
        if(addrList.first().isLoopback())
            addrList.removeFirst();
        else if(addrList.first().isInSubnet(QHostAddress("0.0.0.0"), 0))
        {
            break;
        }
    }

    database = new QSqlDatabase;
    *database = QSqlDatabase::addDatabase("QSQLITE");
    database->setDatabaseName("./data/options");
    database->open();
    dbQuery = new QSqlQuery;
    if(database->tables().isEmpty())
    {
        dbQuery->exec("CREATE TABLE options(name VARCHAR PRIMARY KEY, addr VARCHAR, port INT, music INT,  effects INT);");
        QString forRequest = "insert into options(name, addr, port, music, effects) values('player','";
        forRequest.append(addrList.first().toString() + "', 21034, 70, 70);");
        dbQuery->exec(forRequest);
        options->name    =  "player";
        options->addr    =  addrList.first();
        options->port    =  21034;
        options->music   =  70;
        options->effects =  70;
    }
    else
    {
        dbQuery->exec("select * from options;");
        if(dbQuery->next())
        {
            options->name    =  dbQuery->value(0).toString();
            options->addr    =  dbQuery->value(1).toString();
            options->port    =  dbQuery->value(2).toInt();
            options->music   =  dbQuery->value(3).toInt();
            options->effects =  dbQuery->value(4).toInt();
        }
        else
        {
            QString forRequest = "insert into options(name, addr, port, music, effects) values('player','";
            forRequest.append(addrList.first().toString() + "'', 21034, 70, 70);");
            dbQuery->exec(forRequest);
            options->name    =  "player";
            options->addr    =  addrList.first();
            options->port    =  21034;
            options->music   =  70;
            options->effects =  70;
        }
    }



    lay = new QVBoxLayout(this);

    music = new QMediaPlayer(this);
    QDir().mkdir("./audio");
    QFile::copy(":/audio/main.mp3", "./audio/main.mp3");                                          // с файлами ресурсов юрл не работает.
    music->setMedia(QMediaContent(QUrl::fromLocalFile(QDir::currentPath() + "/audio/main.mp3"))); // абсолютный путь почему-то не работает с этим.
    music->setVolume(options->music);
    music->play();
    guiSound = new QMediaPlayer(this);
    guiSound->setMedia(QMediaContent(QUrl::fromLocalFile(QDir::currentPath() + "/audio/click.wav")));
    guiSound->setVolume(options->effects);

    server = new QTcpServer(this);
    socket = new QTcpSocket(this);

    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    connect(mainMenu, SIGNAL(startClicked()), this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()), this, SLOT(close()));


    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    multiplayerHostMenu = Q_NULLPTR;
}


void baseWindow::mousePressEvent(QMouseEvent *event)
{
    pressed();
    if(curretScene==        "mainMenu")
        mainMenu->scenePress(event->x(), event->y());
    else if(curretScene==   "optionsMenu")
        optionsMenu->scenePress(event->x(), event->y());
    else if(curretScene==   "multiplayerMenu")
        multiplayerMenu->scenePress(event->x(), event->y());
    else if(curretScene==   "multiplayerHostMenu")
        multiplayerHostMenu->scenePress(event->x(), event->y());
    else if(curretScene==   "multiplayerHostAcceptDeny")
        multiplayerHostAcceptDeny->scenePress(event->x(), event->y());
    else if(curretScene==   "multiplayerConnectMenu")
        multiplayerConnectMenu->scenePress(event->x(), event->y());
}

baseWindow::~baseWindow()
{

}

void baseWindow::showOpt()
{
    optionsMenu = new optionsMenuScene(options, this);
    this->setScene(optionsMenu);
    curretScene = "optionsMenu";
    connect(optionsMenu, SIGNAL(acceptClicked()), this, SLOT(optionsAccept()));
    connect(optionsMenu, SIGNAL(cancelClicked()), this, SLOT(optionsCancel()));

    if(mainMenu)
    {
        delete mainMenu;
        mainMenu = Q_NULLPTR;
    }
}

void baseWindow::optionsCancel()
{
    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    curretScene="mainMenu";

    connect(mainMenu, SIGNAL(startClicked()),   this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()),    this, SLOT(close()));

    if(optionsMenu)
    {
        delete optionsMenu;
        optionsMenu = Q_NULLPTR;
    }
}

void baseWindow::optionsAccept()
{
    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    curretScene = "mainMenu";

    connect(mainMenu, SIGNAL(startClicked()),   this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()),    this, SLOT(close()));

    // костыль, знаю.
    optSaver tempOpt =  optionsMenu->getOptions();
    options->addr =     tempOpt.addr;
    options->effects =  tempOpt.effects;
    options->music =    tempOpt.music;
    options->name =     tempOpt.name;
    options->port =     tempOpt.port;

    dbQuery->clear();
    QString forRequest = "UPDATE options SET name='";
    forRequest.append(options->name +                       "', addr='");
    forRequest.append(options->addr.toString() +            "', port=");
    forRequest.append(QString::number(options->port) +      ", music=");
    forRequest.append(QString::number(options->music) +     ", effects=");
    forRequest.append(QString::number(options->effects) +   ";");
    qDebug() << forRequest;
    dbQuery->exec(forRequest);
    qDebug() << dbQuery->lastError();

    music->setVolume(options->music);
    guiSound->setVolume(options->effects);

    if(optionsMenu)
    {
        delete optionsMenu;
        optionsMenu = Q_NULLPTR;
    }
}

void baseWindow::showStart()
{
    multiplayerMenu = new multiplayerMenuScene(this);
    this->setScene(multiplayerMenu);
    curretScene = "multiplayerMenu";

    connect(multiplayerMenu, SIGNAL(backClicked()),     this ,SLOT(backToStart()));
    connect(multiplayerMenu, SIGNAL(hostClicked()),     this, SLOT(showHostMenu()));
    connect(multiplayerMenu, SIGNAL(connectToClicked()),this, SLOT(showConnectMenu()));

    if(mainMenu)
    {
        delete mainMenu;
        mainMenu = Q_NULLPTR;
    }
}

void baseWindow::backMenu()
{
    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    curretScene = "mainMenu";

    connect(mainMenu, SIGNAL(startClicked()),   this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()),    this, SLOT(close()));

    if(multiplayerMenu)
    {
        delete multiplayerMenu;
        multiplayerMenu = Q_NULLPTR;
    }
}

void baseWindow::showHostMenu()
{
    multiplayerHostMenu = new hostMenuScene(options ,this);
    this->setScene(multiplayerHostMenu);
    curretScene = "multiplayerHostMenu";

    connect(multiplayerHostMenu, SIGNAL(optionsClicked()), this, SLOT(optionsFromMultiplayer()));
    connect(multiplayerHostMenu, SIGNAL(backClicked()),    this, SLOT(backToStart()));
    connect(multiplayerHostMenu, SIGNAL(hostClicked()),    this, SLOT(hostServer()));
    connect(multiplayerHostMenu, SIGNAL(hostClose()),      this, SLOT(closeServer()));

    if(multiplayerMenu)
    {
        delete multiplayerMenu;
        multiplayerMenu = Q_NULLPTR;
    }
}

void baseWindow::optionsFromMultiplayer()
{
    optionsMenu = new optionsMenuScene(options ,this);
    this->setScene(optionsMenu);
    curretScene = "optionsMenu";

    connect(optionsMenu, SIGNAL(acceptClicked()), this, SLOT(optionsAcceptFromMultiplayer()));
    connect(optionsMenu, SIGNAL(cancelClicked()), this, SLOT(optionsCancelFromMultiplayer()));

    closeServer();
    if(multiplayerHostMenu)
    {
        delete multiplayerHostMenu;
        multiplayerHostMenu = Q_NULLPTR;
    }
}

void baseWindow::optionsAcceptFromMultiplayer()
{
    multiplayerHostMenu = new hostMenuScene(options, this);
    this->setScene(multiplayerHostMenu);
    curretScene="multiplayerHostMenu";

    connect(multiplayerHostMenu, SIGNAL(optionsClicked()), this, SLOT(optionsFromMultiplayer()));
    connect(multiplayerHostMenu, SIGNAL(backClicked()),    this, SLOT(backToStart()));
    connect(multiplayerHostMenu, SIGNAL(hostClicked()),    this, SLOT(hostServer()));
    connect(multiplayerHostMenu, SIGNAL(hostClose()),      this, SLOT(closeServer()));

    // костыль, знаю.
    optSaver tempOpt =  optionsMenu->getOptions();
    options->addr =     tempOpt.addr;
    options->effects =  tempOpt.effects;
    options->music =    tempOpt.music;
    options->name =     tempOpt.name;
    options->port =     tempOpt.port;

    dbQuery->clear();
    QString forRequest =                                    "UPDATE options SET name='";
    forRequest.append(options->name +                       "', addr='");
    forRequest.append(options->addr.toString() +            "', port=");
    forRequest.append(QString::number(options->port) +      ", music=");
    forRequest.append(QString::number(options->music) +     ", effects=");
    forRequest.append(QString::number(options->effects) +   ";");
    qDebug() << forRequest;
    dbQuery->exec(forRequest);
    qDebug() << dbQuery->lastError();

    music->setVolume(options->music);
    guiSound->setVolume(options->effects);

    closeServer();

    if(optionsMenu)
    {
        delete optionsMenu;
        optionsMenu = Q_NULLPTR;
    }
}

void baseWindow::optionsCancelFromMultiplayer()
{
    multiplayerHostMenu = new hostMenuScene(options, this);
    this->setScene(multiplayerHostMenu);
    curretScene="multiplayerHostMenu";

    connect(multiplayerHostMenu, SIGNAL(optionsClicked()), this, SLOT(optionsFromMultiplayer()));
    connect(multiplayerHostMenu, SIGNAL(backClicked()),    this, SLOT(backMenu()));
    connect(multiplayerHostMenu, SIGNAL(hostClicked()),    this, SLOT(hostServer()));
    connect(multiplayerHostMenu, SIGNAL(hostClose()),      this, SLOT(closeServer()));

    if(optionsMenu)
    {
        delete optionsMenu;
        optionsMenu = Q_NULLPTR;
    }
}

void baseWindow::backToStart()
{
    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    curretScene="mainMenu";

    connect(mainMenu, SIGNAL(startClicked()),   this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()),    this, SLOT(close()));

    closeServer();
    if(multiplayerMenu)
    {
        delete multiplayerMenu;
        multiplayerMenu = Q_NULLPTR;
    }
    if(multiplayerHostMenu)
    {
        delete multiplayerHostMenu;
        multiplayerHostMenu = Q_NULLPTR;
    }
}

void baseWindow::hostServer()
{
    if(server)
    {
        delete server;
        server = Q_NULLPTR;
    }
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(connectedToHost()));
    server->listen(options->addr, options->port);
}

void baseWindow::closeServer()
{
    if(socket)
    {
        delete socket;
        socket = Q_NULLPTR;
    }
    if(server)
    {
        delete server;
        server = Q_NULLPTR;
    }
}

void baseWindow::connectedToHost()
{
    socket = server->nextPendingConnection();
    waitForAnswer = new QTime();
    waitForAnswer->start();
    connect(socket, SIGNAL(readyRead()), this, SLOT(messageFromConnected()));
    server->close();
    multiplayerHostAcceptDeny = new hostAcceptDeny(this);
    this->setScene(multiplayerHostAcceptDeny);
    curretScene = "multiplayerHostAcceptDeny";

    connect(multiplayerHostAcceptDeny, SIGNAL(acceptClicked()), this, SLOT(hostAccepted()));
    connect(multiplayerHostAcceptDeny, SIGNAL(denyClicked()),   this, SLOT(hostDenyed()));
}

void baseWindow::messageFromConnected()
{
    QTextStream stream(socket);
    QString mess;
    stream >> mess;
    QVector<QString> messages;
    messages.append(mess);
    while(mess!="end")
    {
        stream >> mess;
        messages.append(mess);
        qDebug() << "recv : " << mess;
        if(mess.isEmpty())
            return;
    }
    if(!mess.isNull())
    {
        if(messages.at(0)=="playerName")
        {
            if(messages.count()>2)
            {
                QString textHtml = "<div style='background-color:#b77600;'>Some one try to connect to you</div>";
                textHtml.append("<div style='background-color:#b77600;'>His name is : " + messages.at(1) + "</div>");
                multiplayerHostAcceptDeny->textInfo->setHtml(textHtml);
            }
        }
        else if(messages.at(0)=="playerPos")
        {
            if(messages.count()>3)
            {
                if(messages.at(1).at(0).isNumber() && messages.at(2).at(0).isNumber())
                {
                    game->setEnemyPos(messages.at(1).toInt(), messages.at(2).toInt());
                }
            }
        }
        else if(messages.at(0)=="targetPos")
        {
            if(messages.count()>3)
            {
                game->createNewTargeting(messages.at(1).toInt(), messages.at(2).toInt());
            }
        }
        else if(messages.at(0)=="iTargetted")
        {
            game->otherPlayerLoosed();
        }
    }
}

void baseWindow::hostAccepted()
{
    game = new gameScene(this, true, this);
    this->setScene(game);
    curretScene = "game";

    connect(game, SIGNAL(newTargetting(int,int)), this, SLOT(sendPositionTargetting(int,int)));
    connect(game, SIGNAL(playerMoved(int,int)),   this, SLOT(sendPositionPlayer(int,int)));
    connect(game, SIGNAL(gameEnded()),            this, SLOT(backFromGameToMenu()));


    QTextStream stream(socket);
    stream << "ok end \n";

    if(multiplayerHostAcceptDeny)
    {
        delete multiplayerHostAcceptDeny;
        multiplayerHostAcceptDeny = Q_NULLPTR;
    }
    if(multiplayerHostMenu)
    {
        delete multiplayerHostMenu;
        multiplayerHostMenu = Q_NULLPTR;
    }
}

void baseWindow::hostDenyed()
{
    this->setScene(multiplayerHostMenu);
    curretScene="multiplayerHostMenu";

    connect(multiplayerHostMenu, SIGNAL(optionsClicked()), this, SLOT(optionsFromMultiplayer()));
    connect(multiplayerHostMenu, SIGNAL(backClicked()),    this, SLOT(backMenu()));
    connect(multiplayerHostMenu, SIGNAL(hostClicked()),    this, SLOT(hostServer()));
    connect(multiplayerHostMenu, SIGNAL(hostClose()),      this, SLOT(closeServer()));

    closeServer();
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(connectedToHost()));
    server->listen(options->addr, options->port);
    if(multiplayerHostAcceptDeny)
    {
        delete multiplayerHostAcceptDeny;
        multiplayerHostAcceptDeny = Q_NULLPTR;
    }
}

void baseWindow::showConnectMenu()
{
    multiplayerConnectMenu = new connectToScene(options, this);
    this->setScene(multiplayerConnectMenu);
    curretScene = "multiplayerConnectMenu";

    connect(multiplayerConnectMenu, SIGNAL(connectClicked(QHostAddress,int)), this, SLOT(tryConnect(QHostAddress,int)));
    connect(multiplayerConnectMenu, SIGNAL(backClicked()),                    this, SLOT(backFromConnectMenu()));

    if(multiplayerMenu)
    {
        delete multiplayerMenu;
        multiplayerMenu = Q_NULLPTR;
    }
}

void baseWindow::backFromConnectMenu()
{
    multiplayerMenu = new multiplayerMenuScene(this);
    this->setScene(multiplayerMenu);
    curretScene = "multiplayerMenu";

    connect(multiplayerMenu, SIGNAL(backClicked()),     this ,SLOT(backMenu()));
    connect(multiplayerMenu, SIGNAL(hostClicked()),     this, SLOT(showHostMenu()));
    connect(multiplayerMenu, SIGNAL(connectToClicked()),this, SLOT(showConnectMenu()));

    if(multiplayerConnectMenu)
    {
        delete multiplayerConnectMenu;
        multiplayerConnectMenu = Q_NULLPTR;
    }
}

void baseWindow::tryConnect(QHostAddress addr, int port)
{
    if(socket)
        delete socket;
    socket = new QTcpSocket(this);
    socket->connectToHost(addr, port);
    QTextStream stream(socket);
    QString mess = "playerName ";
    mess.append(options->name + " ");
    mess.append("end \n");
    stream << mess;
    qDebug() << mess;

    connect(socket, SIGNAL(readyRead()), this, SLOT(hostAnswer()));
}

void baseWindow::hostAnswer()
{
    QTextStream stream(socket);
    QString mess;
    stream >> mess;
    QVector<QString> messages;
    messages.append(mess);
    while(mess!="end")
    {
        stream >> mess;
        messages.append(mess);
        qDebug() << "recv : " << mess;
        if(mess.isEmpty())
            return;
    }
    if(messages.at(0) == "ok")
    {
        game = new gameScene(this, false, this);
        curretScene = "game";

        connect(   game,   SIGNAL(newTargetting(int,int)), this, SLOT(sendPositionTargetting(int,int)));
        connect(   game,   SIGNAL(playerMoved(int,int)),   this, SLOT(sendPositionPlayer(int,int)));
        connect(  game,    SIGNAL(gameEnded()),            this, SLOT(backFromGameToMenu()));

        disconnect(socket, SIGNAL(readyRead()),            this, SLOT(hostAnswer()));
        connect(   socket, SIGNAL(readyRead()),            this, SLOT(messageFromConnected()));

        this->setScene(game);
        if(multiplayerConnectMenu)
        {
            delete multiplayerConnectMenu;
            multiplayerConnectMenu = Q_NULLPTR;
        }
    }
}

void baseWindow::sendPositionPlayer(int x, int y)
{
    QString message = "playerPos ";
    message.append(QString::number(x) + " ");
    message.append(QString::number(y));
    message.append(" end \n");
    QTextStream stream(socket);
    stream << message;
    qDebug() << message;
}

void baseWindow::sendPositionTargetting(int x, int y)
{
    QString message = "targetPos ";
    message.append(QString::number(x) + " ");
    message.append(QString::number(y));
    message.append(" end \n");
    QTextStream stream(socket);
    stream << message;
    qDebug() << message;
}

void baseWindow::showOptions()
{
    qDebug() << options->addr;
    qDebug() << options->port;
    qDebug() << options->effects;
    qDebug() << options->music;
    qDebug() << options->name;
}

void baseWindow::pressed()
{
    guiSound->stop();
    guiSound->play();
}

void baseWindow::backFromGameToMenu()
{
    closeServer();

    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    curretScene = "mainMenu";

    connect(mainMenu, SIGNAL(startClicked()),   this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()),    this, SLOT(close()));

    QString message = "iTargetted ";
    message.append(" end \n");
    QTextStream stream(socket);
    stream << message;
    qDebug() << message;

    if(game)
    {
        delete game;
        game = Q_NULLPTR;
    }

    QTimer * forclose = new QTimer(this);
    forclose->singleShot(1000, this, SLOT(closeServer()));
//    socket->close();
//    delete socket;
//    server->close();
//    delete server;
}

void baseWindow::backFromGameToMenuW()
{
    mainMenu = new mainMenuScene(this);
    this->setScene(mainMenu);
    curretScene = "mainMenu";
    if(game)
    {
        delete game;
        game = Q_NULLPTR;
    }

    connect(mainMenu, SIGNAL(startClicked()),   this, SLOT(showStart()));
    connect(mainMenu, SIGNAL(optionsClicked()), this, SLOT(showOpt()));
    connect(mainMenu, SIGNAL(exitClicked()),    this, SLOT(close()));

    closeServer();
}
