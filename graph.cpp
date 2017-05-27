#include "graph.h"
#include <QPainter>

graph::graph(QWidget *parent) : QWidget(parent)
{

}

void graph::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.fillRect(0, 0, this->width(), this->height(), Qt::white);
    double max(0);
    double max1(0);
    if(m_co.size()>0)
    {
        for(int i = 0; i != m_co.size(); ++i)
        {
            max = qMax(max, m_co[i][0]);
            max1 = qMax(max1, m_co[i][1]);
        }
        double scale(this->height()/1.2/max);
        double scale1(this->width()/max1);
        for(int i = 1; i != m_co.size(); ++i)
        {
            QLineF line(m_co[i-1][1]*scale1, this->height() - m_co[i-1][0]*scale, m_co[i][1]*scale1, this->height() - m_co[i][0]*scale);
            painter.drawLine(line);
        }
        painter.drawText(this->width()/1.3,15,"Max Capacity");
        painter.drawText(this->width()/1.3,30,QString::number(max/1000000)+"kNm");
    }
}

void graph::setModel(QVector<QVector<double> > co)
{
    m_co = co;
    update();
}
