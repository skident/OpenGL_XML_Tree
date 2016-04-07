#ifndef POINT_H
#define POINT_H

//! 2 dimension point
struct Point
{
    int x;  //! horizpntal position
    int y;  //! vertical position

    //! Constructor with params
    Point(int _x, int  _y);

    //! Default constructor
    Point();

    //! Reinit internal values
    void assign(int  _x, int _y);
};

Point operator+(Point point, int scale);


#endif // POINT_H
