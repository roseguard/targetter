#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDesktopWidget>


class mainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    mainMenuScene(QWidget *parent = 0);
private:
    QGraphicsPixmapItem     *background;
    QGraphicsPixmapItem     *start;
    bool                    startAct = false;
    QGraphicsPixmapItem     *options;
    bool                    optionsAct = false;
    QGraphicsPixmapItem     *exit;
    bool                    exitAct = false;

public:
    void scenePress(int x, int y);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void startClicked();
    void optionsClicked();
    void exitClicked();
};


#endif // MAINMENUSCENE_H
