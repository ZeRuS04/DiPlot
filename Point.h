#ifndef POINT_H
#define POINT_H

#include <QObject>
/*
 *  Класс описание точки с qml интерфейсом
 *
 * */
class Point : public QObject
{
    Q_OBJECT
public:
    explicit Point(qreal x, qreal y, QObject *parent = 0);

    Q_PROPERTY(qreal px READ px NOTIFY xChanged)
    Q_PROPERTY(qreal py READ py NOTIFY yChanged)

    qreal px() const;
    qreal py() const;

public slots:
    void setX(qreal x);
    void setY(qreal y);

signals:
    void xChanged();
    void yChanged();
private:
    qreal m_x;
    qreal m_y;
};

#endif // POINT_H
