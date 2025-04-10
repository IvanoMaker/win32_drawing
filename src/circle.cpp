#include <Windows.h>
#include "circle.h"

Circle::Circle(int x, int y, int radius, int color)
    : x(x), y(y), radius(radius), color(color) {}

void Circle::draw(HDC hdc) {
    HBRUSH brush = CreateSolidBrush((COLORREF)color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}