#ifndef COLOR_H
#define COLOR_H

struct Color
{
    float r;
    float g;
    float b;

    enum eColor
    {
        black,
        white,
        red,
        green
    };

    Color(float _r = 1, float _g = 1, float _b = 1)
    {
        r = _r;
        g = _g;
        b = _b;
    }

    void assign(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
};

Color getColor(Color::eColor color);

#endif // COLOR_H

