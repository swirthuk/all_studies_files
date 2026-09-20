#include <windows.h>
#include <cmath>

struct WindowData
{
    RECT rects[9];
    int hover;
    int N;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WindowData* pData = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (msg)
    {
    case WM_CREATE:
    {
        pData = new WindowData;
        if (pData == NULL)
        {
            // Не удалось выделить память
            return -1;
        }
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pData);

        pData->N = 6; // количество прямоугольников
        pData->hover = -1;
        break;
    }
    case WM_SIZE:
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        int dx = rc.right / sqrt(pData->N);
        int dy = rc.bottom / sqrt(pData->N);
        for (int i = 0; i < pData->N; ++i)
        {
            pData->rects[i].left = (i % (int)sqrt(pData->N)) * dx;
            pData->rects[i].top = (i / (int)sqrt(pData->N)) * dy;
            pData->rects[i].right = pData->rects[i].left + dx;
            pData->rects[i].bottom = pData->rects[i].top + dy;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
    case WM_MOUSEMOVE:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        int prev_hover = pData->hover;
        pData->hover = -1;
        for (int i = 0; i < 9; ++i)
        {
            if (PtInRect(&pData->rects[i], { x, y }))
            {
                pData->hover = i;
                break;
            }
        }
        if (pData->hover != prev_hover)
        {
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
    /*case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        for (int i = 0; i < pData->N; ++i)
        {
            HBRUSH hBrush = CreateSolidBrush(i == pData->hover ? RGB(255, 0, 0) : RGB(255, 255, 255));
            FillRect(hdc, &pData->rects[i], hBrush);
            DeleteObject(hBrush);

            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
            SelectObject(hdc, hPen);
            Rectangle(hdc, pData->rects[i].left, pData->rects[i].top, pData->rects[i].right, pData->rects[i].bottom);
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
        }
        EndPaint(hwnd, &ps);
        break;
    }*/
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        for (int i = 0; i < 9; ++i)
        {
            HBRUSH hBrush = CreateSolidBrush(i == pData->hover ? RGB(255, 0, 0) : RGB(255, 255, 255));
            FillRect(hdc, &pData->rects[i], hBrush);
            DeleteObject(hBrush);

            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, pData->rects[i].left, pData->rects[i].top, NULL);
            LineTo(hdc, pData->rects[i].right, pData->rects[i].top);
            LineTo(hdc, pData->rects[i].right, pData->rects[i].bottom);
            LineTo(hdc, pData->rects[i].left, pData->rects[i].bottom);
            LineTo(hdc, pData->rects[i].left, pData->rects[i].top);
            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
        }
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        delete pData;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "My Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        return 0;
    }

    // Получите размеры экрана
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;
    int posX = (screenWidth - windowWidth) / 2;
    int posY = (screenHeight - windowHeight) / 2;
    SetWindowPos(hwnd, 0, posX, posY, windowWidth, windowHeight, SWP_NOZORDER);
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
