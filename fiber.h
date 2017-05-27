#ifndef FIBER_H
#define FIBER_H


class fiber
{
public:
    fiber(){}
    virtual ~fiber(){}
    virtual double stress(double e){ return 0; }
    double x() const { return m_x; }
    double y() const { return m_y; }
    double w() const { return m_w; }
    double h() const { return m_h; }
    double A() const { return m_A; }

protected:
    double m_w;
    double m_h;
    double m_x;
    double m_y;
    double m_A;
};

class confiber:public fiber
{
public:
    confiber(double x, double y, double w, double h, double Cs);
    double stress(double e);
    double w() const { return m_w; }
    double h() const { return m_h; }
private:
    double fc;
    double Ec;
    double ecr;
    double n;
    double rho;
    double ac;
};

class stefiber:public fiber
{
public:
    stefiber(double x, double y, double w, double Ss);
    double stress(double e);
private:
    double fy;
    double ey;
    double Es;
};

#endif // FIBER_H
