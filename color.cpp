#include "color.h"

Color getColor(Color::eColor color)
{
    Color col;
    switch (color)
    {
    case Color::black:
        col.assign(0, 0, 0);
        break;

    case Color::white:
        col.assign(1, 1, 1);
        break;

    case Color::red:
        col.assign(1, 0, 0);
        break;

    case Color::green:
        col.assign(0, 1, 0);
        break;

    default:
        break;
    }

    return col;
}

