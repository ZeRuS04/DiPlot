#ifndef LINENODE_H
#define LINENODE_H

#include <QSGGeometryNode>

#include "Point.h"

/*
 * Класс: геометрическое описание линии графика
 *
 * */
class LineNode : public QSGGeometryNode
{
public:
    LineNode(float size, const QColor &color);

    void updateGeometry(const QRectF &bounds, const QList<qreal> &samples, QList<QPointF> *points);

    QList<Point *> *points();

private:
    QSGGeometry m_geometry;
    QList<Point*> m_points;
};

#endif // LINENODE_H
