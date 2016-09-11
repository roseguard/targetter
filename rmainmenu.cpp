#include "rmainmenu.h"

RMainMenu::RMainMenu(QWidget *parent) : QGraphicsScene()
{
    QDesktopWidget desk;
    QGraphicsScene(desk.x(), desk.y(), desk.width()-25, desk.height()-25);
    back = new QGraphicsPixmapItem(QPixmap("./data/img/gui/background.jpg").scaled(desk.width()-25, desk.height()-25));
    this->addItem(back);
    back->setPos(desk.x(),desk.y());

    sceneName = new QGraphicsTextItem("Main menu");
    sceneName->setScale(20);
    sceneName->setDefaultTextColor(QColor("purple"));
    QFont sceneFont = sceneName->font();
    //sceneFont.setOverline(1);
    sceneFont.setItalic(1);
    sceneFont.setBold(1);
    sceneName->setFont(sceneFont);

    multObj = new multButt(this, "./data/img/gui/multiplayer_button.png");
    optObj = new optButt(this, "./data/img/gui/multiplayer_button.png");
    exitObj = new exitButt(this,"./data/img/gui/multiplayer_button.png");

    this->addItem(sceneName);
    sceneName->setPos(0,0);
    this->addItem(multObj);
    multObj->setPos(400,400);
    this->addItem(optObj);
    optObj->setPos(500,500);
    this->addItem(exitObj);
    exitObj->setPos(600,600);
}
