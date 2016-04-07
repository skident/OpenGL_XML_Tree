#include "drawer.h"
#include <GL/gl.h>
#include <GL/glut.h>


void Drawer::drawBitmapText(std::string str, Point point)
{
    glRasterPos2f(point.x, point.y + 18);

    for (auto ch : str)
    {
        glutBitmapCharacter(/*GLUT_BITMAP_TIMES_ROMAN_10*/GLUT_BITMAP_TIMES_ROMAN_24, ch);
    }
}

void Drawer::DrawRect(Point topLeft, Point bottomRight, Color color)
{
    glColor3f(color.r, color.g, color.b);

    // draw rectangle
    glBegin(GL_QUADS);
    glVertex2f(topLeft.x,       topLeft.y);
    glVertex2f(bottomRight.x,   topLeft.y);
    glVertex2f(bottomRight.x,   bottomRight.y);
    glVertex2f(topLeft.x,       bottomRight.y);

    glEnd();
}

void Drawer::DrawTriangle(Point topMiddle, Point bottomLeft, Point bottomRight, Color color)
{
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_TRIANGLES);
    glVertex2f(topMiddle.x, topMiddle.y);
    glVertex2f(bottomLeft.x, bottomLeft.y);
    glVertex2f(bottomRight.x, bottomRight.y);

    glEnd();
}


void Drawer::DrawNode(bool isOpen, bool hasChildren, Point point, int size, Color color, std::string title)
{
    std::string status = " ";
    if (hasChildren)
    {
        status = "+";
        if (isOpen)
            status = "-";
    }

    glColor3f(color.r, color.g, color.b);

    drawBitmapText(status, point);
    point.x += 20;
    DrawRect(point, point+size, color);
    point.x += 30;
    drawBitmapText(title, point);
}
