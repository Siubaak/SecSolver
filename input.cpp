#include "input.h"

input::input(QString order, double Cs, double Ss)
{
    QVector<QString> line;
    m_psec.clear();
    int k(0);
    for (int i = 0; i != order.size(); ++i)
    {
        if (order.data()[i] == '\n')
        {
            line<<order.mid(k, i - k);
            k = i + 1;
        }
    }
    for (int i = 0; i != line.size(); ++i)
    {
        if (line[i].section(",",0,0) == "c")
            m_psec<<QSharedPointer<fiber>(new confiber(line[i].section(",",1,1).toDouble(),
                                                      line[i].section(",",2,2).toDouble(),
                                                      line[i].section(",",3,3).toDouble(),
                                                      line[i].section(",",4,4).toDouble(),Cs));
        else if (line[i].section(",",0,0) == "s")
            m_psec<<QSharedPointer<fiber>(new stefiber(line[i].section(",",1,1).toDouble(),
                                                      line[i].section(",",2,2).toDouble(),
                                                      line[i].section(",",3,3).toDouble(),Ss));
    }
}

