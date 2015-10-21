#include "Plot.h"
#include "BackgroundNode.h"
#include "LineNode.h"

#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>


Plot::Plot()
{
    connect(&alg, &GeneticAlgorithm::updatePoints, this, &Plot::gaPointsUpdated);
    connect(this, &Plot::pointsUpdatedSig, this, &Plot::pointsUpdated);
    setFlag(ItemHasContents, true);

}

Plot::~Plot()
{
    deleteAllPoints();
}

QList<qreal> Plot::samples() const
{
    return m_samples;
}

void Plot::deleteAllPoints()
{
    for(int i = 0; i < m_points.size(); i++){
        if(m_points.at(i)){
            delete m_points[i];
            m_points[i] = NULL;
        }
    }
    m_points.clear();
}

QList<Point *> Plot::points() const
{
    return m_points;
}

QList<QObject *> Plot::pointsAsObject() const
{

    QList<QObject *> res;
    res.reserve(m_points.count());
    for(auto i : m_points)
        res.append(i);

    return res;
}

class PlotNode : public QSGNode
{
public:
    BackgroundNode *background;
    LineNode *line;
};

QSGNode *Plot::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    PlotNode *node= static_cast<PlotNode *>(oldNode);

    QRectF bounds = boundingRect();

    if (!node) {
        node = new PlotNode();
        node->background = new  BackgroundNode(QColor(0, 0, 0, 30));
        node->line = new LineNode(2, QColor("steelblue"));
        node->appendChildNode(node->background);
        node->appendChildNode(node->line);

    }
    if (m_geometryChanged || m_samplesChanged) {
        QList<QPointF> *points = new QList<QPointF>;
        node->line->updateGeometry(bounds, m_samples, points);
        node->background->updateGeometry(bounds, m_samples);
        emit pointsUpdatedSig(points);
    }


    m_geometryChanged = false;
    m_samplesChanged = false;

    return node;
}

void Plot::appendSample(qreal value)
{
    m_samples << value;
    m_samplesChanged = true;
    emit samplesChanged(m_samples);
    update();
}


void Plot::removeFirstSample()
{
    m_samples.removeFirst();
    m_samplesChanged = true;
    emit samplesChanged(m_samples);
    update();
}

void Plot::setSamples(QList<qreal> samples)
{
    if (m_samples == samples)
        return;

    m_samples = samples;
    m_samplesChanged = true;
    emit samplesChanged(samples);
    update();
}

void Plot::pointsUpdated(QList<QPointF> *points)
{
    if(points->size() < m_points.size())
        deleteAllPoints();
    for(int i = 0; i < points->size(); i++){
        if(m_points.size() > i){
            m_points.at(i)->setX(points->at(i).x());
            m_points.at(i)->setY(points->at(i).y());
        }
        else
            m_points.append(new Point(points->at(i).x(), points->at(i).y()));
    }
    delete points;

    emit pointsChanged();
}

void Plot::gaPointsUpdated(QList<double> *points)
{
    m_history << points;
    emit historyCountChanged();
//    foreach(double i, *points) {
//        int index = (i - 1)*100;
//        if(m_points.length() > index && index >= 0)
//            m_points.at(index)->setSelected(true);
//    }
//    delete points;
//    emit gaPointsChanged();
}

void Plot::startGA()
{
    m_history.clear();
    alg.start(QThread::LowPriority);
}

void Plot::setHistoryIndex(int historyIndex)
{
    if (m_historyIndex == historyIndex || historyIndex == m_history.length())
        return;

    m_historyIndex = historyIndex;
    emit clearPointsFlags();

    foreach(double i, *m_history.at(m_historyIndex)) {
        int index = (i - 1)*100;
        if(m_points.length() > index && index >= 0)
            connect(this, &Plot::clearPointsFlags, m_points.at(index), &Point::clearFlags);
            m_points.at(index)->setSelected(true);
    }
    emit pointsChanged();
    emit historyIndexChanged();
}


void Plot::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}


