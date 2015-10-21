#ifndef PLOT_H
#define PLOT_H

#include <QtQuick/QQuickItem>
#include "GeneticAlgorithm.h"
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
     * Список полученых кординат точек на экраене
     * **********************************************/
    Q_PROPERTY(QList<int> gaPoints READ gaPoints NOTIFY gaPointsChanged)

    //==============================================//

    /*
     * Элементы выобрки
     * **********************************************/
    Q_PROPERTY(QList<qreal> samples READ samples WRITE setSamples NOTIFY samplesChanged)
    QList<qreal> samples() const;
    //==============================================//


    void deleteAllPoints();     // Удаление всех кординат точек с очищением памяти

    QList<int> gaPoints() const
    {
        return m_gaPoints;
    }

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *); // Событие отрисовки нод
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry); // Событие изменения геометрии окна

public slots:
    void appendSample(qreal value);                 // Добавление  значения к выборке
    void removeFirstSample();                       // Удаление первого значения выборки
    void setSamples(QList<qreal> samples);          // Установка значений выборки
    void pointsUpdated(QList<QPointF> *points);     // Установка значений кординат точек
    void gaPointsUpdated(QList<double> *points);     // Установка значений кординат точек

    void startGA();
signals:
    void samplesChanged(QList<qreal> samples);
    void pointsChanged();
    void pointsUpdatedSig(QList<QPointF> *points);
    void gaPointsChanged();

private:
    QList<qreal> m_samples;
    QList<Point *> m_points;

    bool m_samplesChanged;
    bool m_geometryChanged;
    QList<int> m_gaPoints;

    GeneticAlgorithm alg;
};

#endif // PLOT_H
