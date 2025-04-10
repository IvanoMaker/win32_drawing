#include <Windows.h>
#include "line.h"
#include "fpoint.h"

Line::Line(fPoint start, fPoint end, int width, int color)
    : a(start), b(end), width(width), color(color) {}

Line::draw(HDC hdc) {
    HPEN pen = CreatePen(PS_SOLID, width, (COLORREF)color);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    MoveToEx(hdc, a.x, a.y, NULL);
    LineTo(hdc, b.x, b.y);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}
