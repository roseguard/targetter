#ifndef HOSTACCEPTDENY_H
#define HOSTACCEPTDENY_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QDesktopWidget>

class hostAcceptDeny : public QGraphicsScene
{
    Q_OBJECT
public:
    hostAcceptDeny(QWidget *parent = 0);
private:
    QGraphicsPixmapItem     *background;
    QGraphicsPixmapItem     *accept;
    bool                    acceptAct = false;
    QGraphicsPixmapItem     *deny;
    bool                    denyAct = false;
public:
    QGraphicsTextItem       *textInfo;

public:
    void scenePress(int x, int y);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void acceptClicked();
    void denyClicked();
};
#endif // HOSTACCEPTDENY_H
