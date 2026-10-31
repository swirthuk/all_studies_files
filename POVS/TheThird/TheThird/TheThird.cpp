#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>
#include <time.h>

// Идентификаторы команд меню через enum (не создают переменных в памяти)
enum MenuCommands {
    IDM_EXIT = 40001,
    IDM_SQUARES = 40002,
    IDM_CIRCLES = 40003
};

const int M_WIDTH = 3000;
const int N_HEIGHT = 2000;
const int K_POINTS = 500;
const int RADIUS = 50;

struct AppState {
    POINT points[K_POINTS];
    HBRUSH brushes[8];
    int scrollX;
    int scrollY;
    BOOL isCircles; // FALSE = Квадраты, TRUE = Круги
};

// Создание меню программно без глобальных ресурсов
HMENU CreateAppMenu()
{
    HMENU hMainMenu = ::CreateMenu();
    HMENU hFileMenu = ::CreatePopupMenu();
    HMENU hViewMenu = ::CreatePopupMenu();

    ::AppendMenu(hFileMenu, MF_STRING, IDM_EXIT, TEXT("Выход"));
    ::AppendMenu(hViewMenu, MF_STRING | MF_GRAYED, IDM_SQUARES, TEXT("Квадраты"));
    ::AppendMenu(hViewMenu, MF_STRING | MF_ENABLED, IDM_CIRCLES, TEXT("Круги"));

    ::AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hFileMenu, TEXT("Файл"));
    ::AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hViewMenu, TEXT("Изображение"));

    return hMainMenu;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nCmdShow)
{
    LPCTSTR szClass = TEXT("Tester");

    WNDCLASS wndclass = {};
    wndclass.style = CS_HREDRAW | CS_VREDRAW; // ????
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName = szClass;

    if (!::RegisterClass(&wndclass)) {
        return -1;
    }

    AppState state = {};
    srand((unsigned int)time(NULL));

    for (int i = 0; i < K_POINTS; ++i) {
        state.points[i].x = RADIUS + rand() % (M_WIDTH - 2 * RADIUS);
        state.points[i].y = RADIUS + rand() % (N_HEIGHT - 2 * RADIUS);
    }

    for (int i = 0; i < 8; ++i) {
        state.brushes[i] = ::CreateSolidBrush(RGB(223, 223, i * 32));
    }

    int screenW = ::GetSystemMetrics(SM_CXSCREEN);
    int screenH = ::GetSystemMetrics(SM_CYSCREEN);
    int winW = screenW / 2;
    int winH = screenH / 2;

    HMENU hMenu = CreateAppMenu();

    HWND hWnd = ::CreateWindow(szClass, szClass,
        WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
        (screenW - winW) / 2, (screenH - winH) / 2, winW, winH,
        NULL, hMenu, hInstance, &state);

    if (!hWnd) {
        ::DestroyMenu(hMenu);
        for (int i = 0; i < 8; ++i) ::DeleteObject(state.brushes[i]);
        return -1;
    }

    ::ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0)) {
        ::DispatchMessage(&msg);
    }

    for (int i = 0; i < 8; ++i) {
        ::DeleteObject(state.brushes[i]);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    AppState* pState = (AppState*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (message) {

    case WM_CREATE:
        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
        return 0;

    case WM_SIZE:
    {
        if (!pState) return 0;

        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;

        si.nMax = M_WIDTH - 1;
        si.nPage = LOWORD(lParam);
        si.nPos = pState->scrollX;
        ::SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
        pState->scrollX = ::GetScrollPos(hWnd, SB_HORZ);

        si.nMax = N_HEIGHT - 1;
        si.nPage = HIWORD(lParam);
        si.nPos = pState->scrollY;
        ::SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        pState->scrollY = ::GetScrollPos(hWnd, SB_VERT);

        return 0;
    }

    case WM_COMMAND:
    {
        if (!pState) return 0;

        switch (LOWORD(wParam)) {
        case IDM_EXIT:
            ::DestroyWindow(hWnd);
            break;

        case IDM_SQUARES:
        case IDM_CIRCLES:
        {
            pState->isCircles = (LOWORD(wParam) == IDM_CIRCLES);
            HMENU hMenu = ::GetMenu(hWnd);
            ::EnableMenuItem(hMenu, IDM_SQUARES, MF_BYCOMMAND | (pState->isCircles ? MF_ENABLED : MF_GRAYED));
            ::EnableMenuItem(hMenu, IDM_CIRCLES, MF_BYCOMMAND | (pState->isCircles ? MF_GRAYED : MF_ENABLED));
            ::InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        }
        return 0;
    }

    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_UP:    ::SendMessage(hWnd, WM_VSCROLL, SB_LINEUP, 0); break;
        case VK_DOWN:  ::SendMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, 0); break;
        case VK_PRIOR: ::SendMessage(hWnd, WM_VSCROLL, SB_PAGEUP, 0); break;
        case VK_NEXT:  ::SendMessage(hWnd, WM_VSCROLL, SB_PAGEDOWN, 0); break;
        case VK_LEFT:  ::SendMessage(hWnd, WM_HSCROLL, SB_LINELEFT, 0); break;
        case VK_RIGHT: ::SendMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, 0); break;
        case VK_HOME:  ::SendMessage(hWnd, WM_HSCROLL, SB_LEFT, 0); break;
        case VK_END:   ::SendMessage(hWnd, WM_HSCROLL, SB_RIGHT, 0); break;
        }
        return 0;
    }

    case WM_HSCROLL:
    {
        if (!pState) return 0;

        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        ::GetScrollInfo(hWnd, SB_HORZ, &si);

        int oldPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_LEFT:       si.nPos = si.nMin; break;
        case SB_RIGHT:      si.nPos = si.nMax; break;
        case SB_LINELEFT:   si.nPos -= 20; break;
        case SB_LINERIGHT:  si.nPos += 20; break;
        case SB_PAGELEFT:   si.nPos -= si.nPage; break;
        case SB_PAGERIGHT:  si.nPos += si.nPage; break;
        case SB_THUMBTRACK: si.nPos = si.nTrackPos; break;
        }

        si.fMask = SIF_POS;
        ::SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
        ::GetScrollInfo(hWnd, SB_HORZ, &si);

        if (si.nPos != oldPos) {
            pState->scrollX = si.nPos;
            ::ScrollWindow(hWnd, oldPos - si.nPos, 0, NULL, NULL);
        }
        return 0;
    }

    case WM_VSCROLL:
    {
        if (!pState) return 0;

        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        ::GetScrollInfo(hWnd, SB_VERT, &si);

        int oldPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_TOP:        si.nPos = si.nMin; break;
        case SB_BOTTOM:     si.nPos = si.nMax; break;
        case SB_LINEUP:     si.nPos -= 20; break;
        case SB_LINEDOWN:   si.nPos += 20; break;
        case SB_PAGEUP:     si.nPos -= si.nPage; break;
        case SB_PAGEDOWN:   si.nPos += si.nPage; break;
        case SB_THUMBTRACK: si.nPos = si.nTrackPos; break;
        }

        si.fMask = SIF_POS;
        ::SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        ::GetScrollInfo(hWnd, SB_VERT, &si);

        if (si.nPos != oldPos) {
            pState->scrollY = si.nPos;
            ::ScrollWindow(hWnd, 0, oldPos - si.nPos, NULL, NULL);
        }
        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC = ::BeginPaint(hWnd, &ps);

        if (pState) {
            ::SetBkMode(hDC, TRANSPARENT);
            ::SetTextAlign(hDC, TA_CENTER);

            BOOL(WINAPI * drawShape)(HDC, int, int, int, int) = pState->isCircles ? ::Ellipse : ::Rectangle;
            HBRUSH oBrush = (HBRUSH)::SelectObject(hDC, pState->brushes[0]);

            for (int i = 0; i < K_POINTS; ++i) {
                int cx = pState->points[i].x - pState->scrollX;
                int cy = pState->points[i].y - pState->scrollY;

                RECT rcShape = { cx - RADIUS, cy - RADIUS, cx + RADIUS, cy + RADIUS };
                RECT dummy;

                if (::IntersectRect(&dummy, &rcShape, &ps.rcPaint)) {
                    ::SelectObject(hDC, pState->brushes[i % 8]);
                    drawShape(hDC, rcShape.left, rcShape.top, rcShape.right, rcShape.bottom);

                    TCHAR szBuf[16];
                    int len = ::wsprintf(szBuf, TEXT("%d"), i + 1);
                    ::TextOut(hDC, cx, cy, szBuf, len);
                }
            }

            ::SelectObject(hDC, oBrush);
        }

        ::EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}