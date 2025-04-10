#include <Windows.h>
#include "rect.h"

Rect::Rect(int x, int y, int width, int height, int color)
    : x(x), y(y), width(width), height(height), color(color) {}

void Rect::draw(HDC hdc) {
    HBRUSH brush = CreateSolidBrush((COLORREF)color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}