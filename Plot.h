#ifndef PLOT_H
#define PLOT_H

#include <QtQuick/QQuickItem>

#include "Point.h"

class Plot : public QQuickItem
{
    Q_OBJECT
public:
    Plot();
    ~Plot();

    /*
     * Список полученых кординат точек на экраене
     * **********************************************/
    Q_PROPERTY(QList<QObject *> points READ pointsAsObject NOTIFY pointsChanged)
    QList<Point *> points() const;
    QList<QObject *> pointsAsObject() const;
    //==============================================//


    /*
     * Элементы выобрки
     * **********************************************/
    Q_PROPERTY(QList<qreal> samples READ samples WRITE setSamples NOTIFY samplesChanged)
    QList<qreal> samples() const;
    //==============================================//


    void deleteAllPoints();     // Удаление всех кординат точек с очищением памяти

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *); // Событие отрисовки нод
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry); // Событие изменения геометрии окна

public slots:
    void appendSample(qreal value);                 // Добавление  значения к выборке
    void removeFirstSample();                       // Удаление первого значения выборки
    void setSamples(QList<qreal> samples);          // Установка значений выборки
    void pointsUpdated(QList<QPointF> *points);     // Установка значений кординат точек
signals:
    void samplesChanged(QList<qreal> samples);
    void pointsChanged();
    void pointsUpdatedSig(QList<QPointF> *points);
private:
    QList<qreal> m_samples;
    QList<Point *> m_points;

    bool m_samplesChanged;
    bool m_geometryChanged;
};

#endif // PLOT_H
