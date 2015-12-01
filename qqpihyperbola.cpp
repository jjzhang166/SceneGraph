#include "qqpihyperbola.h"
#include "QtMath"

QQPIHyperbola::QQPIHyperbola() :
    bezierCurve(true)
{
    m_list.append(qMakePair(10, -1));
    m_list.append(qMakePair(8, 5));
    m_list.append(qMakePair(7, -5));
    m_list.append(qMakePair(4, -10));
    m_list.append(qMakePair(9, -8));
    m_list.append(qMakePair(8, -18));
    m_list.append(qMakePair(19, -8));
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void QQPIHyperbola::setList(const QList< QPair<int, int> > &l)
{
    m_list = l;
    update();
}

void QQPIHyperbola::paint(QPainter *painter)
{
    if (bezierCurve)
        drawBezier(painter);
    else
        draw(painter);
}

void QQPIHyperbola::draw(QPainter *painter)
{
    int padding = 40;
    int width = contentsBoundingRect().width();
    int height = contentsBoundingRect().height();
    // 边框
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(0, 0, width-1, height-1);

    int count = m_list.count();
    double itemWidth = (double)width / count;

    int maxValue = 0;
    int minValue = 0;
    for (int i=0; i<count; ++i)
    {
        maxValue = qMax(m_list.at(i).first, maxValue);
        maxValue = qMax(m_list.at(i).second, maxValue);

        minValue = qMin(m_list.at(i).first, minValue);
        minValue = qMin(m_list.at(i).second, minValue);
    }

    int difValue = maxValue - minValue;
    int h = height - padding*2;
    double unit = (double)h / difValue;
    painter->drawRect(0, padding, width, h);

    QPolygon hPoints;
    QPolygon lPoints;
    for (int i=0; i<count; ++i)
    {
        //m_list.at(i).first;
        //m_list.at(i).second;
        //painter->drawRect(itemWidth*i, padding, itemWidth, h);

        int hx = itemWidth/2 + itemWidth*i;
        int hy = padding + unit*(maxValue-m_list.at(i).first);
        //painter->drawPoint(hx, hy);
        hPoints.push_back(QPoint(hx, hy));

        painter->drawText(itemWidth*i, hy - 20, itemWidth, 20,
                          Qt::AlignHCenter | Qt::AlignVCenter, QString("%1°").arg(m_list.at(i).first));

        int lx = itemWidth/2 + itemWidth*i;
        int ly = padding + unit*(maxValue-m_list.at(i).second);
        //painter->drawPoint(lx, ly);
        lPoints.push_back(QPoint(lx, ly));

        painter->drawText(itemWidth*i, ly, itemWidth, 20,
                          Qt::AlignHCenter | Qt::AlignVCenter, QString("%1°").arg(m_list.at(i).second));
    }

    painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolyline(hPoints);
    painter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPoints(hPoints);

    painter->setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolyline(lPoints);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPoints(lPoints);
}

void QQPIHyperbola::drawBezier(QPainter *painter)
{
    int padding = 40;
    int width = contentsBoundingRect().width();
    int height = contentsBoundingRect().height();
    // 边框
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(0, 0, width-1, height-1);

    int count = m_list.count();
    double itemWidth = (double)width / count;


    int maxValue = 0;
    int minValue = 0;
    for (int i=0; i<count; ++i)
    {
        maxValue = qMax(m_list.at(i).first, maxValue);
        maxValue = qMax(m_list.at(i).second, maxValue);

        minValue = qMin(m_list.at(i).first, minValue);
        minValue = qMin(m_list.at(i).second, minValue);
    }

    int difValue = maxValue - minValue;
    int h = height - padding*2;
    double unit = (double)h / difValue;
    //painter->drawRect(0, padding, width, h);

    /*QPainterPath path(start_pos);
    QPoint c1((start_pos+end_pos).x()/2,start_pos.y());
    QPoint c2((start_pos+end_pos).x()/2,end_pos.y());
    path.cubicTo(c1 ,c2 ,end_pos );
    painter.drawPath(path)*/

    QPainterPath hPath;
    QPainterPath lPath;
    QPolygon hPoints;
    QPolygon lPoints;
    for (int i=0; i<count-1; ++i)
    {
        {
            int hx1 = itemWidth/2 + itemWidth*i;
            int hy1 = padding + unit*(maxValue-m_list.at(i).first);

            int hx2 = itemWidth/2 + itemWidth*(i+1);
            int hy2 = padding + unit*(maxValue-m_list.at(i+1).first);

            QPainterPath path(QPoint(hx1, hy1));
            path.cubicTo((hx1+ hx2) / 2, hy1, (hx1+ hx2) / 2, hy2, hx2, hy2);
            hPath.addPath(path);

            hPoints.push_back(QPoint(hx1, hy1));
            if (i == (count-2))
                hPoints.push_back(QPoint(hx2, hy2));

            // 温度
            painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
            painter->drawText(itemWidth*i, hy1 - 20, itemWidth, 20,
                              Qt::AlignHCenter | Qt::AlignVCenter, QString("%1°").arg(m_list.at(i).first));
            if (i == (count-2))
            {
                painter->drawText(itemWidth*(i+1), hy2 - 20, itemWidth, 20,
                                  Qt::AlignHCenter | Qt::AlignVCenter, QString("%1°").arg(m_list.at(i+1).first));
            }
        }

        {
            int lx1 = itemWidth/2 + itemWidth*i;
            int ly1 = padding + unit*(maxValue-m_list.at(i).second);

            int lx2 = itemWidth/2 + itemWidth*(i+1);
            int ly2 = padding + unit*(maxValue-m_list.at(i+1).second);

            QPainterPath path(QPoint(lx1, ly1));
            path.cubicTo((lx1+ lx2) / 2, ly1, (lx1+ lx2) / 2, ly2, lx2, ly2);
            lPath.addPath(path);

            lPoints.push_back(QPoint(lx1, ly1));
            if (i == (count-2))
                lPoints.push_back(QPoint(lx2, ly2));

            // 温度
            painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
            painter->drawText(itemWidth*i, ly1, itemWidth, 20,
                              Qt::AlignHCenter | Qt::AlignVCenter, QString("%1°").arg(m_list.at(i).second));
            if (i == (count-2))
            {
                painter->drawText(itemWidth*(i+1), ly2, itemWidth, 20,
                                  Qt::AlignHCenter | Qt::AlignVCenter, QString("%1°").arg(m_list.at(i+1).second));
            }
        }
    }

    painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPath(hPath);
    painter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPoints(hPoints);

    painter->setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPath(lPath);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPoints(lPoints);

    m_hPath = hPath;

    /*{
        QPoint p0 = QPoint(20, 20);
        QPoint p1 = QPoint(120, 20);
        QPoint p2 = QPoint(120, 200);
        QPoint p3 = QPoint(200, 200);
        painter->setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for (double t=0; t<=1.0; t+=0.01)
        {
            double t1 = 1-t;
            int x = p0.x()*pow(t1, 3) + 3*p1.x()*t*pow(t1, 2) + 3*p2.x()*pow(t, 2)*t1 + p3.x()*pow(t, 3);
            int y = p0.y()*pow(t1, 3) + 3*p1.y()*t*pow(t1, 2) + 3*p2.y()*pow(t, 2)*t1 + p3.y()*pow(t, 3);
            painter->drawPoint(x, y);
        }
    }*/
}

void QQPIHyperbola::mouseMoveEvent(QMouseEvent *event)
{
    if (m_hPath.contains(event->pos()))
        qDebug() << event->pos();
}

void QQPIHyperbola::mousePressEvent(QMouseEvent *event)
{

}




