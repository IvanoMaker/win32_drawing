#include "point.h"

class Line {
public:
    Point a, b;
    int width;
    int color;

    Line(Point a, Point b, int width, int color);

    void draw(HDC hdc);
};