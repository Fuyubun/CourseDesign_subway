#include "subwayline.h"

subwayLine::subwayLine()
{

}

void subwayLine::setCycle(double c0, double c1)
{
    this->Cycle0=c0;
    this->Cycle1=c1;
}

double subwayLine::getCycle0()
{
    return this->Cycle0;
}

double subwayLine::getCycle1()
{
    return this->Cycle1;
}
