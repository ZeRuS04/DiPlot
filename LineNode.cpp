#include "LineNode.h"
#include <QtQuick/qsgflatcolormaterial.h>

LineNode::LineNode(float size, const QColor &color)
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setLineWidth(size);
    m_geometry.setDrawingMode(GL_LINE_STRIP);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
}

QList<Point *> *LineNode::points()
{
    return &m_points;
}

void LineNode::updateGeometry(const QRectF &bounds, const QList<qreal> &samples, QList<QPointF> *points)
{
    int segmentsCount = samples.size();
    if(segmentsCount > 0){
        m_geometry.allocate(segmentsCount);
        qreal min = 0;
        qreal max = 0;
        QSGGeometry::Point2D *vertices = m_geometry.vertexDataAsPoint2D();
        qreal dh, dw;
        if(segmentsCount == 1){
            dh = bounds.height()/2;
            dw = bounds.width()/2;
        }else{
            QList<qreal> list = samples;
            if(!list.isEmpty()){
                qSort(list.begin(), list.end());
                min = list.first();
                max = list.last();
            }
            qreal h = max - min;
            dh = (bounds.height()-bounds.height()/5)/h;

            dw = (bounds.width()-bounds.width()/10)/qreal(segmentsCount);
        }
//        vertices[0].set(0, bounds.height());
        for (int i = 0; i < samples.size(); ++i) {
            QPointF pos = QPointF((i)*dw+dw, bounds.height() - dh*(samples.at(i) - min) - bounds.height()/10);
            vertices[i].set(pos.x(), pos.y());
            points->append(pos);

        }
        markDirty(QSGNode::DirtyGeometry);
    }
}


