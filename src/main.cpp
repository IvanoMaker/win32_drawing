#include <Windows.h>
#include <ctime>
#include <vector>

#include "circle.h"
#include "rect.h"

// Constants for screen and paddle settings
// screen size is fixed to 720p
constexpr int SCREEN_H = 720;       // fixed screen height of 720 pixels
constexpr int SCREEN_W = 1280;      // fixed screen width of 1280 pixels
constexpr int FRAME_DELAY = 16;     // 60 FPS = 1000ms / 60 = 16.67ms per frame

// Draw a rectangle with a specified color
void drawRect(HDC hdc, RECT rect, int color) {
    // create brush object
    HBRUSH brush = nullptr;

    // color mapping
    switch (color) {
        case 0: // 0 : Black
            brush = CreateSolidBrush(RGB(0, 0, 0));
            break;
        case 1: // 1 : White
            brush = CreateSolidBrush(RGB(255, 255, 255));
            break;
    }

    // Draw the rectangle with the specified color
    if (brush) {
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
    }
}

std::vector<Circle> circles; // Vector to hold Circle objects
std::vector<Rect> rects;   // Vector to hold Rect objects

// Window procedure for handling messages
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // handles for double buffering the bitmaps
    static HDC yourdiditMemDC = nullptr;
    static HBITMAP yourdiditMemBitmap = nullptr;
    static HDC betterluckMemDC = nullptr;
    static HBITMAP betterluckMemBitmap = nullptr;

    // window message switch case
    switch (uMsg) {
        case WM_CREATE: {
            int centerX = SCREEN_W / 2;
            int centerY = SCREEN_H / 2;
            int radius = 100; // or any size you want
            COLORREF white = RGB(255, 255, 255);
            Circle c(centerX, centerY, radius, white);

            circles.push_back(c); // Add the Circle object to the vector
            rects.push_back(Rect(centerX - 250, centerY - 50, 100, 100, RGB(255, 0, 0))); // Add a Rect object to the vector

            break;
        }

        // when stuff is drawn on the window
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // Create a memory device context compatible with the screen
            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP memBitmap = CreateCompatibleBitmap(hdc, SCREEN_W, SCREEN_H);
            HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

            // Clear screen with black on memory DC
            RECT screenRect = { 0, 0, SCREEN_W, SCREEN_H };
            drawRect(memDC, screenRect, 0);

            // Draw each circle in the circle vector
            for (auto& circle : circles) {
                circle.draw(memDC);
            }

            for (auto& rect : rects) {
                rect.draw(memDC);
            }

            // Copy the back buffer to the front buffer
            BitBlt(hdc, 0, 0, SCREEN_W, SCREEN_H, memDC, 0, 0, SRCCOPY);

            // delete the memory DC and bitmap to protect against memory leaks
            SelectObject(memDC, oldBitmap);
            DeleteObject(memBitmap);
            DeleteDC(memDC);
            
            EndPaint(hWnd, &ps);
            return 0;
        }
        
        // when a key is pressed down
        case WM_KEYDOWN:
            switch (wParam) {
                default:
                    break;
            }
            return 0;

        // when a key is released
        case WM_KEYUP:
            switch (wParam) {
                default:
                    break;
            }
            return 0;

        // when the window is closed
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        // default case for unhandled windows messages
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    // Register window class
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WinProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "windowClass";

    RegisterClassA(&wc);

    // Create the main window
    HWND hWnd = CreateWindowA(
        "windowClass",
        "Window",
        WS_CAPTION | WS_POPUP | WS_SYSMENU,
        50, 50, SCREEN_W, SCREEN_H,
        nullptr, nullptr,
        hInstance, nullptr
    );

    // show the window
    ShowWindow(hWnd, nCmdShow);

    // Game loop
    MSG msg;
    // clock object used for timing
    std::clock_t lastTime = std::clock();

    // infinite loop for gameplay, user will close window when done
    for (;;) {
        int bricksLeft = 0; // bricksLeft var used for detecting if the user has beat the game
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return 0;
            }
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        std::clock_t currentTime = std::clock();
        if ((currentTime - lastTime) * 1000 / CLOCKS_PER_SEC >= FRAME_DELAY) {
            
            // Trigger redraw
            InvalidateRect(hWnd, nullptr, TRUE);
            lastTime = currentTime;
        }
    }
    return 0;
}