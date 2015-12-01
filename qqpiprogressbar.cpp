#include "qqpiprogressbar.h"
#include <QPainter>

QQPIProgressBar::QQPIProgressBar() :
    m_value(0)
{

}

void QQPIProgressBar::setValue(const double &v)
{
    m_value = v;
    update();
    emit valueChanged();
}

double QQPIProgressBar::value() const
{
    return m_value;
}

void QQPIProgressBar::paint(QPainter *painter)
{
    //painter->fillRect(contentsBoundingRect(), fillColor());
    QRectF r(0, 0, contentsBoundingRect().width()-1, contentsBoundingRect().height()-1);
    painter->drawRect(r);

    int i = (double)(contentsBoundingRect().height()) / 100 * m_value;

    QRect rv(0, contentsBoundingRect().height()-1 - i, contentsBoundingRect().width()-1, contentsBoundingRect().height()-1);
    painter->fillRect(rv, QColor(255, 0, 0));
}

