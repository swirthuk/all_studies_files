#define ROTATION_STEP 200
#define Sec 1000

#define WIDTH 0.5
#define HEIGHT 0.5

#include <windows.h>
#include <string>
#include "Resource.h"


struct WindowData {
    int rotationAngle;
    int fontSize;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{

    LPCTSTR szClass = "DiskTester32";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = szClass;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc)) {
        return -1;
    }

    POINT windowSize;
    windowSize.x = int(GetSystemMetrics(SM_CXSCREEN) * WIDTH);
    windowSize.y = int(GetSystemMetrics(SM_CYSCREEN) * HEIGHT);

    HWND hWnd = CreateWindowEx(0, szClass, "Window", WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - windowSize.x) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - windowSize.y) / 2, windowSize.x, windowSize.y, NULL,
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);

    if (!hWnd)
    {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);

    WindowData pData = { 0, 48 };
    SetWindowLongPtr(hWnd, GWLP_USERDATA, LONG_PTR(&pData));

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        HMENU hMenu;
        hMenu = GetMenu(hWnd);
        SetTimer(hWnd, IDM_TIMER, Sec, nullptr);
        EnableMenuItem(hMenu, IDM_START, MF_GRAYED);
        return 0;
    }
    case WM_PAINT: {
        RECT rc;
        GetClientRect(hWnd, &rc);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        WindowData* pData = (WindowData*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
        HFONT hFont = CreateFont(pData->fontSize, 0, pData->rotationAngle, 0,
            FW_MEDIUM, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");

        HFONT oFont = (HFONT)SelectObject(hdc, hFont);

        
        LPCTSTR text = "string";
        TextOut(hdc, rc.right / 2, rc.bottom / 2, text, lstrlen(text));

        SelectObject(hdc, oFont);

        EndPaint(hWnd, &ps);

        DeleteObject(hFont);
        return 0;
    }


    case WM_TIMER:
        switch (wParam) {
        case IDM_TIMER: {
            KillTimer(hWnd, IDM_TIMER);
            WindowData* pData = (WindowData*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));

            pData->rotationAngle += ROTATION_STEP;

            InvalidateRect(hWnd, NULL, TRUE);
            SetTimer(hWnd, IDM_TIMER, Sec, nullptr);
        }
        } return 0;

    case WM_LBUTTONUP: {
        WindowData* pData = (WindowData*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        pData->fontSize += 5;
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    }
    case WM_RBUTTONUP: {
        WindowData* pData = (WindowData*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        pData->fontSize -= 5;
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_STOP:
            HMENU hMenu;
            hMenu = GetMenu(hWnd);
            EnableMenuItem(hMenu, IDM_STOP, MF_DISABLED);
            EnableMenuItem(hMenu, IDM_START, MF_ENABLED);
            KillTimer(hWnd, IDM_TIMER);
            break;
        case IDM_START:
            hMenu = GetMenu(hWnd);
            EnableMenuItem(hMenu, IDM_START, MF_DISABLED);
            EnableMenuItem(hMenu, IDM_STOP, MF_ENABLED);
;           SetTimer(hWnd, IDM_TIMER, Sec, nullptr);
            break;
        }
        return 0;
    }

    case WM_DESTROY: {
        KillTimer(hWnd, IDM_TIMER);
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
