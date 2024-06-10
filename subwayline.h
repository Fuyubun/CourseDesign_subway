#ifndef SUBWAYLINE_H
#define SUBWAYLINE_H


class subwayLine
{
    double Cycle0;//正方向周期，单位分钟
    double Cycle1;//反方向周期，单位分钟
public:
    subwayLine();
    void setCycle(double c0,double c1);
    double getCycle0();
    double getCycle1();
};

#endif // SUBWAYLINE_H
