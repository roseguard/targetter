#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPalette>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneEvent>

#include <QMouseEvent>

#include <QNetworkInterface>

#include <QMediaPlayer>
#include <QCursor>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QTime>

#include "foropt.h"
#include "mainmenuscene.h"
#include "optionsmenu.h"
#include "multiplayermenu.h"
#include "hostmenuscene.h"
#include "hostacceptdeny.h"
#include "connectto.h"
#include "gamescene.h"

class baseWindow;

class baseWindow : public QGraphicsView
{
    Q_OBJECT
public:
    baseWindow(QWidget *parent = 0);
    ~baseWindow();

    QMediaPlayer            *music;
    QMediaPlayer            *guiSound;

    QVBoxLayout             *lay;
    QGraphicsView           *viewer;

    QString                 curretScene = "mainMenu";
    mainMenuScene           *mainMenu;
    optionsMenuScene        *optionsMenu;
    multiplayerMenuScene    *multiplayerMenu;
    hostMenuScene           *multiplayerHostMenu;
    hostAcceptDeny          *multiplayerHostAcceptDeny;
    connectToScene          *multiplayerConnectMenu;
    gameScene               *game;


    optSaver                *options;
    QSqlDatabase            *database;
    QSqlQuery               *dbQuery;

    QTcpServer              *server;
    QTcpSocket              *socket;
    QTime                   *waitForAnswer;

public:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void showOpt();
    void optionsCancel();
    void optionsAccept();
    void showStart();
    void backMenu();
    void showHostMenu();
    void showConnectMenu();
    void backToStart();
    void optionsFromMultiplayer();
    void optionsAcceptFromMultiplayer();
    void optionsCancelFromMultiplayer();
    void hostServer();
    void closeServer();
    void connectedToHost();
    void messageFromConnected();
    void hostAccepted();
    void hostDenyed();
    void tryConnect(QHostAddress addr, int port);
    void hostAnswer();
    void backFromConnectMenu();
    void sendPositionTargetting(int x, int y);
    void sendPositionPlayer(int x, int y);
    void backFromGameToMenu();
    void backFromGameToMenuW();

    void pressed();

    void showOptions();
};

#endif // BASEWINDOW_H
