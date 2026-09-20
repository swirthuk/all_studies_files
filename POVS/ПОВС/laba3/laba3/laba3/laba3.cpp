#define STRICT
#define WIN32_LEAN_AND_MEAN 
#define FIGURES 1000
#define M 2000
#define RADIUS 50

#define WIDTH 0.5
#define HEIGHT 0.5

#include <Windows.h>
#include "Resource.h"
#include <cmath>
#include <time.h>


struct Figure {
    int x[FIGURES];
    int y[FIGURES];
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine, int       nCmdShow)
{

    LPCTSTR szClass = TEXT("DiskTester32");

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = szClass;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    if (!RegisterClass(&wc)) {
        return -1;
    }

    POINT windowSize;
    windowSize.x = int(GetSystemMetrics(SM_CXSCREEN) * WIDTH);
    windowSize.y = int(GetSystemMetrics(SM_CYSCREEN) * HEIGHT);

    HWND hWnd = ::CreateWindow(szClass, L"Window", WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        (GetSystemMetrics(SM_CXSCREEN) - windowSize.x) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - windowSize.y) / 2, windowSize.x, windowSize.y, NULL, 
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);

    if (!hWnd)
    {
        return -1;
    }

    ::ShowWindow(hWnd, nCmdShow);
    srand(static_cast<unsigned int>(time(nullptr)));
    Figure figure;
    for (int i = 0; i < FIGURES; i++) {
        figure.x[i] = (int)(M * rand() / RAND_MAX);
        figure.y[i] = (int)(M * rand() / RAND_MAX);
    }

    SetWindowLong(hWnd, GWL_USERDATA, (LONG)&figure);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
    case WM_SIZE: {
        RECT Rect;
        GetClientRect(hWnd, &Rect);

        SCROLLINFO hscroll = { 0 };
        hscroll.cbSize = sizeof(SCROLLINFO);
        hscroll.fMask = SIF_RANGE;
        hscroll.nMax = M - Rect.right;
        hscroll.nMin = 0;
        SetScrollInfo(hWnd, SB_HORZ, &hscroll, TRUE);

        SCROLLINFO vscroll = { 0 };
        vscroll.cbSize = sizeof(SCROLLINFO);
        vscroll.fMask = SIF_RANGE;
        vscroll.nMax = M - Rect.bottom;
        vscroll.nMin = 0;
        SetScrollInfo(hWnd, SB_VERT, &vscroll, TRUE);

        InvalidateRect(hWnd, NULL, true);
        return 0;
    }
    case WM_PAINT: {
        SCROLLINFO hScroll = { 0 };
        hScroll.cbSize = sizeof(SCROLLINFO);
        hScroll.fMask = SIF_POS;
        GetScrollInfo(hWnd, SB_HORZ, &hScroll);

        SCROLLINFO vScroll = { 0 };
        vScroll.cbSize = sizeof(SCROLLINFO);
        vScroll.fMask = SIF_POS;
        GetScrollInfo(hWnd, SB_VERT, &vScroll);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HMENU hMenu;
        hMenu = GetMenu(hWnd);
        HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));

        Figure* figure;
        figure = (Figure*)GetWindowLong(hWnd, GWL_USERDATA);
        for (int i = 0; i < FIGURES; i++) {

            if (i % 2 == 0) SelectObject(hdc, redBrush);
            else SelectObject(hdc, greenBrush);

            RECT circRect;

            circRect.left = figure->x[i] - RADIUS - hScroll.nPos;
            circRect.top = figure->y[i] - RADIUS - vScroll.nPos;
            circRect.right = figure->x[i] + RADIUS - hScroll.nPos;
            circRect.bottom = figure->y[i] + RADIUS - vScroll.nPos;
            RECT rc;

            if (IntersectRect(&rc, &ps.rcPaint, &circRect)) {
                if (GetMenuState(hMenu, IDM_CIRCLE, MF_BYCOMMAND) & MF_GRAYED) {
                    Ellipse(hdc, circRect.left, circRect.top, circRect.right, circRect.bottom);
                }
                else {
                    Rectangle(hdc, circRect.left, circRect.top, circRect.right, circRect.bottom);
                }
                
            }
        }

        DeleteObject(redBrush);
        DeleteObject(greenBrush);
        return 0;
    }
    case WM_VSCROLL:
    {
        SCROLLINFO vScroll;
        vScroll.cbSize = sizeof(SCROLLINFO);
        vScroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
        GetScrollInfo(hWnd, SB_VERT, &vScroll);


        RECT rc;
        GetClientRect(hWnd, &rc);

        int pix = 0;
        switch (LOWORD(wParam))
        {
        case SB_LINEDOWN:
        case SB_PAGEDOWN:
        {
            int step = (LOWORD(wParam) == SB_LINEDOWN) ? 50 : 100;
            pix = vScroll.nMax - vScroll.nPos;

            if (pix == 0) return 0;
            if (pix > step) pix = step;

            vScroll.nPos += pix;

            break;
        }

        case SB_LINEUP:
        case SB_PAGEUP:
        {
            int step = (LOWORD(wParam) == SB_LINEUP) ? 50 : 100;
            pix = vScroll.nPos;

            if (pix == 0) return 0;
            if (pix > step) pix = step;

            pix = -pix;
            vScroll.nPos += pix;

            break;
        }

        case  SB_THUMBTRACK:
        {
            pix = vScroll.nTrackPos - vScroll.nPos;
            vScroll.nPos = vScroll.nTrackPos;

            break;
        }

        case SB_TOP:
        {
            vScroll.nTrackPos = vScroll.nMin;
            pix = vScroll.nTrackPos - vScroll.nPos;
            if (0 == pix) { return 0; }
            vScroll.nPos = vScroll.nTrackPos;
            break;
        }

        case SB_BOTTOM:
        {
            if (vScroll.nMax == pix) { return 0; }
            vScroll.nTrackPos = vScroll.nMax;
            pix = vScroll.nTrackPos - vScroll.nPos;
            vScroll.nPos = vScroll.nTrackPos;

            break;
        }
        }

        ScrollWindowEx(hWnd, 0, -pix, NULL, NULL, NULL, NULL, SW_ERASE);

        if (pix > 0)
            rc.top = rc.bottom - pix;
        else
            rc.bottom = rc.top - pix;

        SetScrollInfo(hWnd, SB_VERT, &vScroll, TRUE);
        InvalidateRect(hWnd, &rc, TRUE);
        return 0;
    }

    case WM_HSCROLL:
    {
        SCROLLINFO hScroll;
        hScroll.cbSize = sizeof(SCROLLINFO);
        hScroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
        GetScrollInfo(hWnd, SB_HORZ, &hScroll);

        RECT rc;
        GetClientRect(hWnd, &rc);

        int pix = 0;
        switch (LOWORD(wParam))
        {
        case SB_LINERIGHT:
        case SB_PAGERIGHT:
        {
            int step = (LOWORD(wParam) == SB_LINERIGHT) ? 50 : 100;
            pix = hScroll.nMax - hScroll.nPos;

            if (pix == 0) return 0;
            if (pix > step) pix = step;

            hScroll.nPos += pix;

            break;
        }

        case SB_LINELEFT:
        case SB_PAGELEFT:
        {
            int step = (LOWORD(wParam) == SB_LINELEFT) ? 50 : 100;
            pix = hScroll.nPos;

            if (pix == 0) return 0;
            if (pix > step) pix = step;

            pix = -pix;
            hScroll.nPos += pix;

            break;
        }

        case SB_THUMBTRACK:
        {
            pix = hScroll.nTrackPos - hScroll.nPos;
            hScroll.nPos = hScroll.nTrackPos;

            break;
        }

        case SB_TOP:
        {
            hScroll.nTrackPos = hScroll.nMin;
            pix = hScroll.nTrackPos - hScroll.nPos;
            if (0 == pix) { return 0; }
            hScroll.nPos = hScroll.nTrackPos;

            break;
        }

        case SB_BOTTOM:
        {
            if (hScroll.nMax == pix) { return 0; }
            hScroll.nTrackPos = hScroll.nMax;
            pix = hScroll.nTrackPos - hScroll.nPos;
            hScroll.nPos = hScroll.nTrackPos;

            break;
        }
        }

        ScrollWindowEx(hWnd, -pix, 0, NULL, NULL, NULL, NULL, SW_ERASE);

        if (pix > 0)
            rc.left = rc.right - pix;
        else
            rc.right = rc.left - pix;

        SetScrollInfo(hWnd, SB_HORZ, &hScroll, TRUE);
        InvalidateRect(hWnd, &rc, TRUE);
        return 0;
    }
    case WM_KEYDOWN:
        switch (LOWORD(wParam)) {
        case VK_UP: {
            PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, NULL);
            return 0;
        }
        case VK_DOWN: {
            PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, NULL);
            return 0;
        }
        case VK_RIGHT: {
            PostMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, NULL);
            return 0;
        }
        case VK_LEFT: {
            PostMessage(hWnd, WM_HSCROLL, SB_LINELEFT, NULL);
            return 0;
        }
        case VK_HOME: {
            PostMessage(hWnd, WM_VSCROLL, SB_TOP, NULL);
            PostMessage(hWnd, WM_HSCROLL, SB_TOP, NULL);
            return 0;
        }
        case VK_END: {
            PostMessage(hWnd, WM_VSCROLL, SB_BOTTOM, NULL);
            PostMessage(hWnd, WM_HSCROLL, SB_BOTTOM, NULL);
            return 0;
        }
        case VK_ESCAPE:
            DestroyWindow(hWnd);
        default:
            return 0;
        }
    case WM_COMMAND: {
        switch (LOWORD(wParam))
        {
        case IDM_EXIT: {
            DestroyWindow(hWnd);
            return 0;
        }
        case IDM_CIRCLE:
        case IDM_RECT:
            HMENU hMenu;
            hMenu = GetMenu(hWnd);
            
            int prevItem = LOWORD(wParam);
            int newItem = (prevItem == IDM_CIRCLE) ? IDM_RECT : IDM_CIRCLE;
            EnableMenuItem(hMenu, prevItem, MF_GRAYED);
            EnableMenuItem(hMenu, newItem, MF_ENABLED);
            InvalidateRect(hWnd, 0, TRUE);
            return 0;
        }
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}