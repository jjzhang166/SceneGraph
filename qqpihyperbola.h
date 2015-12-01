#ifndef QQPIHYPERBOLA_H
#define QQPIHYPERBOLA_H
#include <QQuickPaintedItem>
#include <QPainter>

class QQPIHyperbola : public QQuickPaintedItem
{
public:
    QQPIHyperbola();

    void setList(const QList< QPair<int, int> >& l);

    void paint(QPainter* painter);
    void draw(QPainter* painter);
    void drawBezier(QPainter* painter);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent * event);


private:
    QList< QPair<int, int> > m_list;
    bool bezierCurve;
    QPainterPath m_hPath;
};

#endif // QQPIHYPERBOLA_H
