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
    Q_PROPERTY(bool selected READ selected NOTIFY selectedChanged)
    qreal px() const;
    qreal py() const;

    bool selected() const
    {
        return m_selected;
    }

    void setSelected(bool s) {
        m_selected = s;
        emit selectedChanged();
    }

public slots:
    void setX(qreal x);
    void setY(qreal y);

    void clearFlags() {
        setSelected(false);
    }

signals:
    void xChanged();
    void yChanged();
    void selectedChanged();


private:
    qreal m_x;
    qreal m_y;

    bool m_selected;
};

#endif // POINT_H
