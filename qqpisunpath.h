#ifndef QQPISUNPATH_H
#define QQPISUNPATH_H
#include <QQuickPaintedItem>
#include <QMovie>

class QQPISunPath : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int value
               READ value WRITE setValue
               NOTIFY valueChanged)
public:
    QQPISunPath();

    void setValue(const int& v);
    int value() const;

    virtual void paint(QPainter * painter);
    //QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
    void valueChanged();

public slots:
    void movieFrameChanged(int frameNumber);

private:
    int m_value;
    QString t1;
    QString t2;
    QMovie* m_movie;
    int m_margin;
};

#endif // QQPISUNPATH_H
