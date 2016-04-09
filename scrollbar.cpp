#include "scrollbar.h"
#include "drawer.h"

ScrollBar::ScrollBar()
{

}

void ScrollBar::draw(int winWidth, int winHeight, int invisibleTop, int visible)
{
    if (visible == 100)
        return;

    int scrollHeight = visible * winHeight / 100;
    float scrollTop = (float)invisibleTop * winHeight / 100;

    Drawer::DrawRect(Point(winWidth-lim_barWidth, scrollTop),
                     Point(winWidth, scrollTop + scrollHeight),
                     Color(1,1,1));
}
