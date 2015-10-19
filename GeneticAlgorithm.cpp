#include "GeneticAlgorithm.h"
#include <QDebug>

GeneticAlgorithm::GeneticAlgorithm()
{}

void GeneticAlgorithm::initGenerator()
{
    m_genotype.clear();
    for(int i = 0; i <  GA_POWER; i++) {
        gene g;
        g.alleles = rand()%16383;
        g.fitnes_calc();
        m_genotype << g;
    }
    qSort(m_genotype);
}

void GeneticAlgorithm::reproductionOperator()
{
    bool parentsCount = 0;
    gene parentsArray[2];
    m_newGens.clear();
    for(int i = 0; i < m_genotype.length(); i++) {
        gene g = m_genotype.at(i);
        double chance = i/GA_POWER * GA_P_CROSS;
        double r = static_cast<double>(rand()%100)/100.0;
        if(r <= chance) {
            parentsArray[parentsCount] = g;
            parentsCount++;

            if(parentsCount == 2) {
                parents p;
                p.parent_1 = parentsArray[0];
                p.parent_2 = parentsArray[1];
                p.crossingover();
                m_newGens << p.child_1;
                m_newGens << p.child_2;
                parentsCount = 0;
            }
        }
    }
}

void GeneticAlgorithm::reductionOperator()
{
    m_genotype << m_newGens;
    qSort(m_genotype);
    if(m_genotype.length() > GA_POWER){
        m_genotype.remove(500, m_genotype.length() - 500);
    }
}

void GeneticAlgorithm::mutationOperator()
{
    for(int i = 0; i < m_newGens.length(); i++) {
        int p = rand()%1000;
        if(p == 1000*GA_P_MUTATE)
        {
            ushort bit = rand()%GA_BITS;
            ushort mask = 1 << bit;
            m_newGens[i].alleles = m_newGens.at(i).alleles ^ mask;
            qDebug() << "Mutation!";
        }
    }
}

void GeneticAlgorithm::run()
{
    for (int i = 0; i < GA_MAXITER; i++) {
        initGenerator();
        reproductionOperator();
        mutationOperator();
        reductionOperator();

        QVector<QPointF> *points = new QVector<QPointF> ();
        for( int i = 0; i < 10; i++){
            points->append(QPointF(m_genotype.at(i).x,m_genotype.at(i).fitness));
        }
        emit updatePoints(points);
//        QVector<gene> copy = m_genotype;
//        copy.removeAll(copy.first());
//        if(copy.isEmpty()){
//            qDebug() << "===============Fast EXIT!=================";
//            break;
//        }
    }

    qDebug() << "END:" << m_genotype.last().fitness;

}
