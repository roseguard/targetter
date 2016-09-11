#ifndef LINEPROXY_H
#define LINEPROXY_H

#include <QGraphicsProxyWidget>
#include <QMouseEvent>

class lineProxy : public QGraphicsProxyWidget
{
public:
    lineProxy();

    void mousePressEvent(QMouseEvent *event);
};

#endif // LINEPROXY_H
