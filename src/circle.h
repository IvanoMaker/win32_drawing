class Circle {
public:
    int x, y;
    int radius;
    int color;
    
    Circle(int x, int y, int radius, int color);
    
    void draw(HDC hdc);
};