#include "point.h"

Point::Point(int  _x, int _y)
    : x(_x)
    , y(_y)
{
}

Point::Point()
    : Point(0, 0)
{

}

void Point::assign(int  _x, int _y)
{
    x = _x;
    y = _y;
}


Point operator+(Point point, int scale)
{
    point.x += scale;
    point.y += scale;
    return point;
}
