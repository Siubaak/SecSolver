#include "figure.h"
#include "qmath.h"
#include <QPainter>

figure::figure(QWidget *parent) : QWidget(parent)
{

}

void figure::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.fillRect(0, 0, this->width(), this->height(), Qt::white);
    double max(0);
    double max1(0);
    if (m_co.size()>0)
    {
        for(int i = 0; i != m_co.size(); i = i + 2)
        {
            max = qMax(max, qAbs(m_co[i]) + m_d[i]/2);
            max1 = qMax(max1, qAbs(m_co[i + 1]) + m_d[i]/2);
        }
        double scale(0.5/qMax(max/this->width(), max1/this->height()));
        for(int i = 0; i != m_co.size(); i = i + 2)
        {
            if(m_d[i + 1] != 0)
            {
                painter.setBrush(Qt::gray);
                painter.drawRect(this->width()/2 + m_co[i]*scale - m_d[i]*scale/2,
                                 this->height()/2 - m_co[i + 1]*scale - m_d[i + 1]*scale/2,
                                 m_d[i]*scale,
                                 m_d[i+1]*scale);
            }
            else
            {
                painter.setBrush(Qt::red);
                painter.drawEllipse(this->width()/2 + m_co[i]*scale - m_d[i]*scale/2,
                                    this->height()/2 - m_co[i + 1]*scale - m_d[i]*scale/2,
                                    m_d[i]*scale,
                                    m_d[i]*scale);
            }
        }
    }
}

void figure::setModel(QVector<QSharedPointer<fiber> > psec)
{
    m_co.clear();
    m_d.clear();
    for (int i = 0; i != psec.size(); ++i)
    {
        m_co<<psec[i]->x();
        m_co<<psec[i]->y();
        m_d<<psec[i]->w();
        m_d<<psec[i]->h();
    }
    update();
}
