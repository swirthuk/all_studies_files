#define WIDTH 0.7
#define HEIGHT 0.7
#define BUTTON_INDENT 0
#define BUTTON_NUM 2600  
#define BUTTON_HEIGHT 25
#define BUTTON_WIDTH 100
#define FIRST_BTN 0

#include <windows.h>
#include "resource.h"
#include <stdio.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    LPCTSTR szClass = "DiskTester32";
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

    HWND hWnd = CreateWindowEx(0, szClass, "Window", WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - windowSize.x) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - windowSize.y) / 2, windowSize.x, windowSize.y, NULL,
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL);

    if (!hWnd)
    {
        return -1;
    }
    ShowWindow(hWnd, nCmdShow);

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {
        char buff[20] = { 0 };
        int k = 1;
        for (int i = 0; i < BUTTON_NUM; i += 2)
        {
            if (2600 <= i) {
                MessageBox(hWnd, "Нельзя создать более 1300 кнопок.", "Ошибка", MB_OK | MB_ICONERROR);
                DestroyWindow(hWnd);
                break;
            }

            wsprintf(buff, "Кнопка %d", k);
            if (!(CreateWindow("BUTTON", buff,
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                BUTTON_INDENT,
                BUTTON_INDENT * k + BUTTON_HEIGHT * (k - 1),
                BUTTON_WIDTH,
                BUTTON_HEIGHT,
                hWnd,
                HMENU(i),
                GetModuleHandle(NULL), NULL))) {
                return -1;
            }
            

            sprintf_s(buff, "Радио %d", k);

            if (!(CreateWindow("BUTTON", buff,
                WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
                2 * BUTTON_WIDTH + BUTTON_INDENT,
                BUTTON_INDENT * k + BUTTON_HEIGHT * (k - 1),
                BUTTON_WIDTH,
                BUTTON_HEIGHT,
                hWnd,
                HMENU(i + 1),
                GetModuleHandle(NULL), NULL))) {
                return -1;
            }
            
            k++;
        }
        SendDlgItemMessage(hWnd, FIRST_BTN, BM_SETSTATE, BN_PUSHED, NULL);
        SendDlgItemMessage(hWnd, FIRST_BTN + 1, BM_SETCHECK, BST_CHECKED, NULL);
        SetWindowLong(hWnd, GWLP_USERDATA, FIRST_BTN);
        return 0;
    }

    case WM_SIZE: {
        RECT screen;
        SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);
        RECT rc;
        GetClientRect(hWnd, &rc);
        SCROLLINFO scroll = { 0 };
        scroll.cbSize = sizeof(SCROLLINFO);
        scroll.fMask = SIF_RANGE;
        scroll.nMin = 0;
        int n = (BUTTON_NUM / 2 - rc.bottom / (BUTTON_INDENT + BUTTON_HEIGHT));
        scroll.nMax = BUTTON_HEIGHT * n + (BUTTON_INDENT * (n - 1));
        SetScrollInfo(hWnd, SB_VERT, &scroll, TRUE);

        return 0;
    }

    case WM_COMMAND: {
        int btn_num = GetWindowLong(hWnd, GWLP_USERDATA);
        int Id = LOWORD(wParam);

        if (HIWORD(wParam) == BN_CLICKED) {

            if (Id % 2 != 0) {
                Id -= 1;
            }


            if (SendDlgItemMessage(hWnd, Id + 1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                return 0;
            }

            SendDlgItemMessage(hWnd, btn_num + 1, BM_SETCHECK, BST_UNCHECKED, NULL);
            SendDlgItemMessage(hWnd, Id + 1, BM_SETCHECK, BST_CHECKED, NULL);

            if (SendDlgItemMessage(hWnd, Id, BM_GETSTATE, 0, 0) == BST_PUSHED) {
                return 0;
            }

            SendDlgItemMessage(hWnd, btn_num, BM_SETSTATE, BST_UNCHECKED, NULL);
            SendDlgItemMessage(hWnd, Id, BM_SETSTATE, BN_PUSHED, NULL);

            SetWindowLong(hWnd, GWLP_USERDATA, Id);
        }

        if (Id == IDM_EXIT) {
            DestroyWindow(hWnd);
            break;
        }

        return 0;
    }


    case WM_VSCROLL: {
        SCROLLINFO vscroll = { 0 };
        vscroll.cbSize = sizeof(SCROLLINFO);
        vscroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
        GetScrollInfo(hWnd, SB_VERT, &vscroll);
        int nyPos = vscroll.nPos;

        int buttonOffset = BUTTON_HEIGHT + BUTTON_INDENT; 

        switch (LOWORD(wParam)) {
        case SB_PAGEDOWN:
            nyPos += buttonOffset * 22; 
            break;
        case SB_LINEDOWN:
            nyPos += buttonOffset; 
            break;
        case SB_PAGEUP:
            nyPos -= buttonOffset * 22; 
            break;
        case SB_LINEUP:
            nyPos -= buttonOffset; 
            break;
        case SB_BOTTOM:
            nyPos = vscroll.nMax;
            break;
        case SB_TOP:
            nyPos = vscroll.nMin;
            break;
        case SB_THUMBTRACK:
            nyPos = HIWORD(wParam);
            break;
        default:
            break;
        }

        nyPos = max(0, nyPos);
        nyPos = min(vscroll.nMax, nyPos);

        if (nyPos == vscroll.nPos)
            return 0;

        int yDelta = nyPos - vscroll.nPos;
        vscroll.nPos = nyPos;
        ScrollWindow(hWnd, 0, -yDelta, NULL, NULL);
        SetScrollInfo(hWnd, SB_VERT, &vscroll, TRUE);

        return 0;
    }

    case WM_KEYDOWN: {
        switch (wParam) {
        case VK_UP:
            PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, NULL);
            break;
        case VK_DOWN:
            PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, NULL);
            break;
        case VK_PRIOR:
            PostMessage(hWnd, WM_VSCROLL, SB_PAGEUP, NULL);
            break;
        case VK_NEXT:
            PostMessage(hWnd, WM_VSCROLL, SB_PAGEDOWN, NULL);
            break;
        case VK_HOME:
            PostMessage(hWnd, WM_VSCROLL, SB_TOP, NULL);
            break;
        case VK_END:
            PostMessage(hWnd, WM_VSCROLL, SB_BOTTOM, NULL);
            break;
        }
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
