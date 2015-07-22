#ifndef BACKGROUNDNODE_H
#define BACKGROUNDNODE_H

#include <QSGGeometryNode>

/*
 * Класс: геометрическое описание фона графика
 *
 * */
class BackgroundNode : public QSGGeometryNode
{
public:
    BackgroundNode(const QColor &color);

    void updateGeometry(const QRectF &bounds, const QList<qreal> &samples);

private:
    QSGGeometry m_geometry;
};

#endif // BACKGROUNDNODE_H
