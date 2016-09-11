#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class multiplayerMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    multiplayerMenuScene(QWidget *parent = 0);
private:
    QGraphicsPixmapItem     *background;
    QGraphicsPixmapItem     *header;
    QGraphicsPixmapItem     *host;
    bool                    hostAct = false;
    QGraphicsPixmapItem     *connectTo;
    bool                    connectToAct = false;
    QGraphicsPixmapItem     *back;
    bool                    backAct = false;
public:
    void scenePress(int x, int y);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void hostClicked();
    void connectToClicked();
    void backClicked();
};

#endif // MULTIPLAYERMENU_H
