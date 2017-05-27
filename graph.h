#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

class graph : public QWidget
{
    Q_OBJECT
public:
    explicit graph(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void setModel(QVector<QVector<double> > co);

signals:

public slots:

private:
    QVector<QVector<double> > m_co;
};

#endif // GRAPH_H
