#include "qqpisunpath.h"
#include <QPainter>
#include <QtMath>
#include <QSGSimpleRectNode>
#include <QSGSimpleTextureNode>

QQPISunPath::QQPISunPath() :
    m_value(0),
    m_margin(40)
{
    t1 = "06:30";
    t2 = "16:45";
    m_movie = new QMovie("C:/Users/Administrator/Desktop/1.gif", "", this);
    if (m_movie->isValid())
    {
        connect(m_movie, SIGNAL(frameChanged(int)), this, SLOT(movieFrameChanged(int)));
        m_movie->start();
    }
}

void QQPISunPath::setValue(const int &v)
{
    if (v != m_value)
    {
        if (v < 0)
            m_value = 0;
        else if (v > 100)
            m_value = 100;
        else
            m_value = v;

        update();
        emit valueChanged();
    }
}

int QQPISunPath::value() const
{
    return m_value;
}

void QQPISunPath::paint(QPainter *painter)
{
    //painter->fillRect(contentsBoundingRect(), QColor("red"));
    painter->setRenderHint(QPainter::Antialiasing);


    // center
    int x0 = width() / 2;
    int y0 = height() - m_margin;
    // radius
    int r = width() / 2 - m_margin;

    painter->setPen(Qt::DashLine);
    painter->drawArc(x0-r, y0-r, r*2, r*2, 0, 180*16);
    painter->setPen(Qt::SolidLine);
    painter->drawLine(x0-r, y0, x0+r, y0);

    double i = (double)180 / 100 * m_value;
    double angle = 180 + i;
    float x = r*cos(qDegreesToRadians(angle)) + x0;
    float y = r*sin(qDegreesToRadians(angle)) + y0;
    painter->drawPoint(x, y);

    painter->save();
    QPainterPath path;
    path.moveTo(x0, y0);
    path.arcTo(x0-r, y0-r, r*2, r*2, 0, 180);
    //painter->fillPath(path, QColor("yellow"));
    painter->setClipPath(path);
    painter->fillRect(x0-r, y0-r, x-(x0-r), r-1, QColor("yellow"));
    painter->restore();

    QRect rect1 = painter->boundingRect(x0-r, y0+10, 0, 0, Qt::AlignHCenter, t1);
    painter->drawText(rect1, Qt::AlignHCenter, t1);
    QRect rect2 = painter->boundingRect(x0+r, y0+10, 0, 0, Qt::AlignHCenter, t2);
    painter->drawText(rect2, Qt::AlignHCenter, t2);

    if (m_movie->isValid() && m_value > 0 && m_value < 100)
    {
        QPixmap	pix = m_movie->currentPixmap();
        if (!pix.isNull())
        {
            // 占整个窗体1/10
            int rp =  r / 5;
            painter->drawPixmap(x-rp, y-rp, rp*2, rp*2, pix);
        }
    }
}

//QSGNode *QQPISunPath::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
//{
//    QSGGeometryNode *node = static_cast<QSGGeometryNode*>(oldNode);
//    QSGGeometryNode *node1;
//    if (!node)
//    {
//        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
//        material->setColor(QColor(255, 0, 0));

//        node = new QSGGeometryNode;
//        node1 = new QSGGeometryNode;
//        //node->appendChildNode(node1);

//        node->setMaterial(material);
//        node->setFlag(QSGNode::OwnsMaterial);

//        QSGFlatColorMaterial *material1 = new QSGFlatColorMaterial;
//        material1->setColor(QColor(255, 0, 0));
//        node1->setMaterial(material1);
//        node1->setFlag(QSGNode::OwnsMaterial);
//    }

//    // center
//    int x0 = width() / 2;
//    int y0 = height() - m_margin;
//    // radius
//    int r = width() / 2 - m_margin;

//    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 180);
//    geometry->setDrawingMode(GL_LINES);
//    for (int i=180; i<360; i++)
//    {
//        float x = r*cos(qDegreesToRadians(double(i))) + x0;
//        float y = r*sin(qDegreesToRadians(double(i))) + y0;
//        geometry->vertexDataAsPoint2D()[i-180].set(x, y);
//    }
//    //geometry->vertexDataAsPoint2D()[0].set(x0, y0);
//    node->setGeometry(geometry);
//    node->setFlag(QSGNode::OwnsGeometry);


//     QSGGeometry *geometry1 = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
//     geometry1->setDrawingMode(GL_LINES);
//     geometry1->vertexDataAsPoint2D()[0].set(x0, y0);
//     geometry1->vertexDataAsPoint2D()[0].set(100, 100);

//     node1->setGeometry(geometry1);
//     node1->setFlag(QSGNode::OwnsGeometry);

//    return node;
//}

void QQPISunPath::movieFrameChanged(int frameNumber)
{
    //qDebug() << frameNumber;
    if (m_value > 0 && m_value < 100)
    {
//        int width = contentsBoundingRect().width();
//        int height = contentsBoundingRect().height();
//        int margin = 40;
//        // center
//        int x0 = width / 2;
//        int y0 = height - margin;
//        // radius
//        int r = width / 2 - margin;
//        int rp =  r / 5;

//        double i = (double)180 / 100 * m_value;
//        double angle = 180 + i;
//        float x = r*cos(qDegreesToRadians(angle)) + x0;
//        float y = r*sin(qDegreesToRadians(angle)) + y0;

//        QRect rect(x-rp, y-rp, rp*2, rp*2);

        update(/*rect*/);
    }
}

