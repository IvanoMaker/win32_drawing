class Rect {
public:
    int x, y;
    int width, height;
    int color;
        
    Rect(int x, int y, int width, int height, int color);
        
    void draw(HDC hdc);
};