#include "wire.h"
wire::wire()
{
    this->index = 0;
    this->startPos.setx(0);
    this->startPos.sety(0);
    this->endPos.setx(0);
    this->endPos.sety(0);
    this->distance = 0;
}
void wire::calculateBasicDistance()
{
    this->distance = abs(this->endPos.getx() - this->startPos.getx()) + abs(this->endPos.gety() - this->startPos.gety()); // calculate the absolute value.
}

void wire::setWire(int w_index, int start_x, int start_y, int end_x, int end_y)
{
    this->index = w_index;
    this->startPos.setx(start_x);
    this->startPos.sety(start_y);
    this->endPos.setx(end_x);
    this->endPos.sety(end_y);
    calculateBasicDistance();
}
