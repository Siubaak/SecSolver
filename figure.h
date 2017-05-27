#ifndef FIGURE_H
#define FIGURE_H

#include <QWidget>
#include <QVector>
#include <QVector>
#include <QSharedPointer>
#include "fiber.h"

class figure : public QWidget
{
    Q_OBJECT
public:
    explicit figure(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void setModel(QVector<QSharedPointer<fiber> > psec);

signals:

public slots:

private:
    QVector<double> m_co;
    QVector<double> m_d;
};

#endif // FIGURE_H
