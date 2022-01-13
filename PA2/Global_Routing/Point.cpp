#include "Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->distance = 0;
    this->predecessor = NULL;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
    this->distance = 0;
    this->predecessor = NULL;
}

// vertical Edge
Point Point::up(int row, int col)
{
    if (this->x + 1 >= row)
    {
        return Point(-1, -1); // (-1,-1) means there is no legal point.
    }
    return Point(this->x + 1, (this->y));
}
Point Point::down(int row, int col)
{
    if ((this->x) - 1 < 0)
    {
        return Point(-1, -1); // (-1,-1) means this is not legal point.
    }
    return Point((this->x) - 1, this->y);
}
// horizontal edge
Point Point::right(int row, int col)
{
    if (this->y + 1 >= col)
    {
        return Point(-1, -1); // (-1,-1) means this is not legal point.
    }
    return Point(this->x, (this->y) + 1);
}
Point Point::left(int row, int col)
{
    if ((this->y) - 1 < 0)
    {
        return Point(-1, -1); // (-1,-1) means this is not legal point.
    }
    return Point(this->x, (this->y) - 1);
}

Point &Point::operator=(const Point &rhs)
{
    if (this != &rhs)
    { // 檢查自我賦值
        this->x = rhs.x;
        this->y = rhs.y;
        this->distance = rhs.distance;
        this->predecessor = rhs.predecessor;
    }
    return *this;
}