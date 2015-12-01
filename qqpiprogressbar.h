#ifndef QQPIPROGRESSBAR_H
#define QQPIPROGRESSBAR_H
#include <QQuickPaintedItem>

class QQPIProgressBar : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(double value
               READ value WRITE setValue
               NOTIFY valueChanged)
public:
    QQPIProgressBar();

    void setValue(const double& v);
    double value() const;

    virtual void paint(QPainter * painter);

signals:
    void valueChanged();

private:
    double m_value;
};

#endif // QQPIPROGRESSBAR_H
