#include "fiber.h"
#include "qmath.h"

confiber::confiber(double x, double y, double w, double h, double Cs)
    :Ec(30000), fc(Cs)
{
    m_w = w;
    m_h = h;
    m_x = x;
    m_y = y;
    m_A = w*h;
    ecr = 0.000001*(700 + 172*qSqrt(fc));
    n = Ec*ecr/(Ec*ecr - fc);
    rho = fc/Ec/ecr;
    ac = 0.157*qPow(fc, 0.785) - 0.905;
}
double confiber::stress(double e)
{
    if (e<0)
    {
        double x(-e/ecr);
        double dc(0);
        if (x <= 1) dc = 1 - rho*n/(n - 1 + qPow(x, n));
        else dc = 1 - rho/(ac*qPow((x - 1), 2) + x);
        return (1 - dc)*Ec*e;
    }
    else return 0;
}

stefiber::stefiber(double x, double y, double w, double Ss)
{
    m_w = w;
    m_h = 0;
    m_x = x;
    m_y = y;
    m_A = 3.1415926*m_w*m_w/4;
    fy = Ss;
    Es = 205000;
    ey = fy/205000;
}
double stefiber::stress(double e)
{
    if(qAbs(e)<ey) return Es*e;
    else return fy*e/qAbs(e);
}
