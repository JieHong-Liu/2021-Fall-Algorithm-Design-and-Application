#pragma once
#include "Point.h"
class wire
{
public:
    int index;
    int distance;
    Point startPos;
    Point endPos;
    wire(); // constructor
    void setWire(int w_index, int start_x, int start_y, int end_x, int end_y);

private:
    void calculateBasicDistance();
};