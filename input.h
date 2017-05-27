#ifndef INPUT_H
#define INPUT_H
#include <QString>
#include <QVector>
#include <QSharedPointer>
#include "fiber.h"

class input
{
public:
    input(QString order = 0, double Cs = 14.3, double Ss = 360);
    QVector<QSharedPointer<fiber> > sec() const { return m_psec; }
    QVector<QVector<double> > Mphi() const { return m_M_phi; }

private:
    QVector<QSharedPointer<fiber> > m_psec;
    QVector<QVector<double> > m_M_phi;
};

#endif // INPUT_H
