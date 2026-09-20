#define STRICT
#define WIN32_LEAN_AND_MEAN
#define WIDTH 0.5
#define HEIGHT 0.5
#define LSTRING 256

#include <Windows.h>
#include "resource.h"



LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    HBITMAP hBMP = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
    HBRUSH  hBrh = CreatePatternBrush(hBMP);
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "NAME_CLASS";
    wc.hbrBackground = (hBrh);
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    wc.style = CS_HREDRAW | CS_VREDRAW;


    if (!RegisterClass(&wc)) return -1; 

    HINSTANCE hInst = GetModuleHandle(NULL);
    TCHAR mainTitle[LSTRING];
    LoadString(hInst, 1, mainTitle, sizeof(mainTitle));

    POINT windowSize;
    windowSize.x = int(GetSystemMetrics(SM_CXSCREEN) * WIDTH);
    windowSize.y = int(GetSystemMetrics(SM_CYSCREEN) * HEIGHT);

    HWND hWnd = CreateWindow("NAME_CLASS", mainTitle, WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - windowSize.x) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - windowSize.y) / 2,
        windowSize.x, windowSize.y, NULL, NULL, hInstance, NULL);
    if (!hWnd) { return -1; }

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }
    DeleteObject(hBrh);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {

    case WM_RBUTTONDOWN: {
        POINT pt;
        GetCursorPos(&pt);

        HMENU hPopupMenu = CreatePopupMenu();
        TCHAR title[LSTRING];
        HINSTANCE hInst = GetModuleHandle(NULL);

        for (int id = IDS_STRING1; id <= IDS_STRING4; id++) {
            if (LoadString(hInst, id, title, sizeof(title))) {
                AppendMenu(hPopupMenu, MF_STRING, id, title);
            }
        }

        AppendMenu(hPopupMenu, MF_SEPARATOR, 0, NULL);

        for (int id = IDB_BITMAP1; id <= IDB_BITMAP2; id++) {
            if (LoadString(hInst, id, title, sizeof(title))) {
                AppendMenu(hPopupMenu, MF_STRING, id, title);
            }
        }

        SetMenu(hwnd, hPopupMenu);
        TrackPopupMenu(hPopupMenu, TPM_CENTERALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, hwnd, NULL);
        DestroyMenu(hPopupMenu);
        return 0;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        HINSTANCE hInst = GetModuleHandle(NULL);

        if (id >= IDS_STRING1 && id <= IDS_STRING4) {
            TCHAR szMenuString[LSTRING];
            LoadString(hInst, id, szMenuString, sizeof(szMenuString) / sizeof(TCHAR));
            SetWindowText(hwnd, szMenuString);
        }
        else if (id >= IDB_BITMAP1 && id <= IDB_BITMAP2) {
            HBITMAP hBMP = LoadBitmap(hInst, MAKEINTRESOURCE(id));
            HBRUSH hBrh = CreatePatternBrush(hBMP);

            DeleteObject((HGDIOBJ)SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrh));

            InvalidateRect(hwnd, 0, TRUE);
        }
        else if (id == IDM_EXIT) {
            DestroyWindow(hwnd);
        }
        return 0;
    }

    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}