#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QThread>
#include <QVector>
#include <QPointF>
#include <qmath.h>

#define GA_POWER        500
#define GA_P_CROSS      0.5
#define GA_P_MUTATE     0.001
#define GA_BITS         14
#define GA_MAXITER      16383

#define GA_MASK         0x3fff


struct gene {
    short alleles;
    double fitness;
    double x;

    void fitnes_calc(){
        alleles = alleles & GA_MASK;

        x = 1.0 + 9.0*alleles/16383;

        fitness = qLn(x) * cos(3*x - 15);
    }

    // Test for equality.
    bool operator<(gene const & b) const {return ((this->fitness) < (b.fitness));}
    bool operator==(gene const & gn) const  {return ((this->alleles & GA_MASK) == (gn.alleles & GA_MASK));}
};

struct parents {
    gene parent_1;
    gene parent_2;

    gene child_1;
    gene child_2;

    void crossingover() {
        ushort crossPoint = rand()%(GA_BITS-1) + 2;

        ushort mask_left, mask_right;
        mask_left = mask_right = 0xffff;

        mask_right >> (crossPoint+2);
        mask_left = mask_left^mask_right;

        child_1.alleles = parent_1.alleles & mask_left;
        child_2.alleles = parent_2.alleles & mask_left;

        child_1.alleles = child_1.alleles + (parent_2.alleles & mask_right);
        child_2.alleles = child_2.alleles + (parent_1.alleles & mask_right);

        child_1.fitnes_calc();
        child_2.fitnes_calc();
    }
};

class  GeneticAlgorithm : public QThread
{
    Q_OBJECT
public:
    explicit GeneticAlgorithm();

    void initGenerator();
    void reproductionOperator();
    void reductionOperator();
    void mutationOperator();
protected:
    // QThread interface
    void run();

signals:
    void updatePoints(QVector<QPointF> *points);
public slots:

private:
    QVector<gene> m_genotype;
    QVector<gene> m_newGens;
};

#endif // GENETICALGORITHM_H
