#define  STRICT
#define  WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#define FIGURES 1000
#define M 2000
#define RADIUS 50

//#define IDM_CLOSE 0
//#define IDM_CIRCLE 1
//#define IDM_RECT 2

#define WIDTH 0.5
#define HEIGHT 0.5

#include <Windows.h>
#include "Resource.h"
#include <cmath>
#include <wchar.h>


struct Figure {
    int x[FIGURES];
    int y[FIGURES];
    bool isCircle;
};

BOOL(__stdcall* DrawFigures[])(HDC hdc, int left, int top, int right, int bottom) {
    Rectangle, Ellipse
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
    windowSize.x = static_cast<int>(GetSystemMetrics(SM_CXSCREEN) * WIDTH);
    windowSize.y = static_cast<int>(GetSystemMetrics(SM_CYSCREEN) * HEIGHT);

    HWND hWnd = CreateWindow(szClass, "Window", WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        (GetSystemMetrics(SM_CXSCREEN) - windowSize.x) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - windowSize.y) / 2, windowSize.x, windowSize.y, NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);

    if (!hWnd)
    {
        return -1;
    }

    ::ShowWindow(hWnd, nCmdShow);

    Figure figure;
    for (int i = 0; i < FIGURES; i++) {
        figure.x[i] = (int)(M * rand() / RAND_MAX);
        figure.y[i] = (int)(M * rand() / RAND_MAX);
    }
    figure.isCircle = true;
    SetWindowLong(hWnd, GWLP_USERDATA, (LONG)&figure);

    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0)) {
        ::DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
    case WM_CREATE:
        //HMENU hMenu;
        //HMENU file;
        //HMENU actions;

        //hMenu = CreateMenu();
        //file = CreatePopupMenu();
        //actions = CreatePopupMenu();

        //AppendMenu(file, MF_STRING, IDM_CLOSE, L"Выход");
        //AppendMenu(actions, MF_STRING, IDM_CIRCLE, L"Круги");
        //AppendMenu(actions, MF_STRING, IDM_RECT, L"Квадраты");

        //AppendMenu(hMenu, MF_POPUP, (UINT)file, L"Файл");
        //AppendMenu(hMenu, MF_POPUP, (UINT)actions, L"Фигуры");

        //SetMenu(hWnd, hMenu);

        //EnableMenuItem(actions, IDM_CIRCLE, ODS_GRAYED);
        ////CheckMenuItem(actions, IDM_CIRCLE, MF_CHECKED);

        return 0;
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
        hscroll.nMin = 0;
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
        HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 255, 255));

        Figure* figure;
        figure = (Figure*)GetWindowLong(hWnd, GWLP_USERDATA);
        for (int i = 0; i < FIGURES; i++) {
            if (i % 2 == 0) SelectObject(hdc, yellowBrush);
            else SelectObject(hdc, blueBrush);

            RECT circRect;
            //GetClientRect(hWnd, &Rect);

            circRect.left = figure->x[i] - RADIUS - hScroll.nPos;
            circRect.top = figure->y[i] - RADIUS - vScroll.nPos;
            circRect.right = figure->x[i] + RADIUS - hScroll.nPos;
            circRect.bottom = figure->y[i] + RADIUS - vScroll.nPos;
            RECT rc;

            if (IntersectRect(&rc, &ps.rcPaint, &circRect)) {
                DrawFigures[static_cast<int>(figure->isCircle)](hdc,
                    circRect.left, circRect.top,
                    circRect.right, circRect.bottom);
                SetBkMode(hdc, TRANSPARENT);
                WCHAR numberStr[1024]; // 3 символа и завершающий ноль выделили 1кБ
                swprintf_s(numberStr, L"%d", i + 1);
                DrawTextW(hdc, numberStr, wcslen(numberStr), &circRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            }
        }

        DeleteObject(yellowBrush);
        DeleteObject(blueBrush);
        return 0;
    }
    case WM_HSCROLL: {
        SCROLLINFO hScroll;
        hScroll.cbSize = sizeof(SCROLLINFO);
        hScroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
        GetScrollInfo(hWnd, SB_HORZ, &hScroll);

        RECT rc;
        GetClientRect(hWnd, &rc);

        int pix = 0;
        switch (LOWORD(wParam)) {
        case SB_LINERIGHT:
        case SB_PAGERIGHT: {
            int k = (LOWORD(wParam) == SB_LINERIGHT) ? 10 : 50;
            pix = hScroll.nMax - hScroll.nPos;
            if (pix > k) pix = k;
            hScroll.nPos = hScroll.nPos + pix;
            break;
        }
        case SB_LINELEFT:
        case SB_PAGELEFT: {
            int k = (LOWORD(wParam) == SB_LINELEFT) ? 10 : 50;
            pix = hScroll.nPos - hScroll.nMin;
            if (pix > k) pix = k;
            pix = -pix;
            hScroll.nPos = hScroll.nPos + pix;
            break;
        }
        case SB_THUMBTRACK: {
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
        //UpdateWindow(hWnd);
        return 0;
    }
    case WM_VSCROLL: {
        SCROLLINFO vScroll;
        vScroll.cbSize = sizeof(SCROLLINFO);
        vScroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
        GetScrollInfo(hWnd, SB_VERT, &vScroll);

        RECT rc;
        GetClientRect(hWnd, &rc);

        int pix = 0;
        switch (LOWORD(wParam)) {
        case SB_LINEDOWN:
        case SB_PAGEDOWN: {
            int k = (LOWORD(wParam) == SB_LINEDOWN) ? 10 : 50;
            pix = vScroll.nMax - vScroll.nPos;
            if (pix > k) pix = k;
            vScroll.nPos = vScroll.nPos + pix;
            break;
        }

        case SB_LINEUP:
        case SB_PAGEUP: {
            int k = (LOWORD(wParam) == SB_LINEUP) ? 10 : 50;
            pix = vScroll.nPos - vScroll.nMin;
            if (pix > k) pix = k;
            pix = -pix;
            vScroll.nPos = vScroll.nPos + pix;
            break;
        }
        case SB_THUMBTRACK: {
            pix = vScroll.nTrackPos - vScroll.nPos;
            vScroll.nPos = vScroll.nTrackPos;
            break;
        }
        }ScrollWindowEx(hWnd, 0, -pix, NULL, NULL, NULL, NULL, SW_ERASE);
        if (pix > 0)
            rc.top = rc.bottom - pix;
        else
            rc.bottom = rc.top - pix;
        SetScrollInfo(hWnd, SB_VERT, &vScroll, TRUE);
        InvalidateRect(hWnd, &rc, TRUE);
        //UpdateWindow(hWnd);
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
        case VK_ESCAPE:
            //PostQuitMessage(0);
            ::DestroyWindow(hWnd);
        default:
            return 0;
        }
    case WM_MOUSEWHEEL: {
        short zDelta = (short)(0xFFFF & (wParam >> 16));

        if (GetKeyState(VK_SHIFT) < 0) {
            if (zDelta > 0)
                PostMessage(hWnd, WM_HSCROLL, SB_LINELEFT, NULL);
            else
                PostMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, NULL);
        }
        else {
            if (zDelta > 0)
                PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, NULL);
            else
                PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, NULL);
        }
        return 0;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam))
        {
        case IDM_EXIT: {
            PostQuitMessage(0);
            return 0;
        }
        case IDM_CIRCLE:
        case IDM_RECT:
            HMENU hMenu;
            hMenu = GetMenu(hWnd);
            Figure* figure;
            figure = (Figure*)GetWindowLong(hWnd, GWLP_USERDATA);
            figure->isCircle ^= 1;

            int prevItem = LOWORD(wParam);
            int newItem = (prevItem == IDM_CIRCLE) ? IDM_RECT : IDM_CIRCLE;
            EnableMenuItem(hMenu, prevItem, MF_GRAYED);
            EnableMenuItem(hMenu, newItem, MF_ENABLED);
            /*CheckMenuItem(hMenu, prevItem, MF_UNCHECKED);
            CheckMenuItem(hMenu, newItem, MF_CHECKED);*/

            //RECT rc;
            //GetClientRect(hWnd, &rc);
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