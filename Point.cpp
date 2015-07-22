#include "Point.h"

Point::Point(qreal x, qreal y, QObject *parent)
  : QObject(parent)
  , m_x(x)
  , m_y(y)
{}



qreal Point::px() const
{
    return m_x;
}

qreal Point::py() const
{
    return m_y;
}

void Point::setX(qreal x)
{
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged();
}

void Point::setY(qreal y)
{
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged();
}
