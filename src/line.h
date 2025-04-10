#include "fpoint.h"

class Line {
public:
    fPoint a, b;
    int width;
    int color;

    Line(fPoint a, fPoint b, int width, int color);

    void draw(HDC hdc);
};
