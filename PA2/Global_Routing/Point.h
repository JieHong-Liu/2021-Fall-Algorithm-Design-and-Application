#pragma once
#include <iostream>
using std::ostream;
class Point
{
public:
    double distance;
    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << p.x << ' ' << p.y;
        return os;
    }
    Point();
    Point(int x, int y);
    ~Point(){};
    // copy constructor
    Point &operator=(const Point &rhs);
    // vertical Edge
    Point up(int row, int col);
    Point down(int row, int col);
    // horizontal edge
    Point right(int row, int col);
    Point left(int row, int col);
    int getx() { return this->x; }
    int gety() { return this->y; }
    void setx(int x) { this->x = x; }
    void sety(int y) { this->y = y; }
    Point *getPredecessor() { return this->predecessor; }
    void setPredecessor(Point *p) { this->predecessor = p; }

private:
    int x;
    int y;
    Point *predecessor;
};