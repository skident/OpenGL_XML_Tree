#ifndef SCROLLBAR_H
#define SCROLLBAR_H

class ScrollBar
{
public:
    enum eLimits
    {
        lim_barWidth        = 20,
    };

    ScrollBar();


    void draw(int winWidth, int winHeight, int invisibleTop, int visible);
};

#endif // SCROLLBAR_H

