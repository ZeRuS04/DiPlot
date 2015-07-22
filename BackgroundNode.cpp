#include "BackgroundNode.h"

#include <QtQuick/qsgflatcolormaterial.h>

BackgroundNode::BackgroundNode(const QColor &color)
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    setGeometry(&m_geometry);
    m_geometry.setLineWidth(1);
    m_geometry.setDrawingMode(GL_TRIANGLE_STRIP);
//    setFlag(QSGNode::OwnsGeometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);
    setMaterial(material);
    setFlag(QSGNode::OwnsMaterial);
}



void BackgroundNode::updateGeometry(const QRectF &bounds, const QList<qreal> &samples)
{
    int segmentsCount = samples.size()*2  + 2;
    m_geometry.allocate(segmentsCount);

    QSGGeometry::Point2D *vertices = m_geometry.vertexDataAsPoint2D();

    QList<qreal> list = samples;
    qreal min = 0;
    qreal max = 0;
    if(!list.isEmpty()){
        qSort(list.begin(), list.end());
        min = list.first();
        max = list.last();
    }
    qreal h = max - min;
    qreal dh = (bounds.height()-bounds.height()/5)/h;

    qreal dw = (bounds.width()-bounds.width()/10)/qreal((segmentsCount-2)/2);

    vertices[0].set(0, bounds.height());

    for (int i = 0; i < samples.size(); ++i) {
        int k = i*2;
        QPointF pos = QPointF((i+1)*dw, bounds.height() - dh*(samples.at(i) - min) - bounds.height()/10);

        vertices[k+1].set(pos.x(), pos.y());
        vertices[k+2].set(pos.x(), bounds.height());

    }
    vertices[segmentsCount-1].set(bounds.width(), bounds.height());

    markDirty(QSGNode::DirtyGeometry);
}
