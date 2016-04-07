#ifndef DRAWER_H
#define DRAWER_H

#include <string>
#include "point.h"
#include "color.h"

//! Draw on window
class Drawer
{
public:
    //! State of node
    enum ElementState
    {
        state_opened,
        state_closed,
        state_none
    };

    //! Draw text str start from point
    //! \param str text for drawing
    //! \param point coordinates of start position
    static void drawBitmapText(std::string str, Point point);

    //! Draw rectangle from top left angle to bottom right angle with needed color
    static void DrawRect(Point topLeft, Point bottomRight, Color color);
    static void DrawNode(bool isOpen, bool hasChildren, Point point, int size, Color color, std::string title);
    static void DrawTriangle(Point top, Point leftBottom, Point rightBottom, Color color);
};

#endif // DRAWER_H
