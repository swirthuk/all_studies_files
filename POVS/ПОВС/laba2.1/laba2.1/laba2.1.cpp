#define STRICT
#define WIN32_LEAN_AND_MEAN 
#define NumOfRect 9
#include <windows.h>
#include <cmath>

struct WindowData
{
    RECT rects[NumOfRect]; 
    int hover;
    HBRUSH hBrush;
    HBRUSH hHoverBrush;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static WindowData pData;
    switch (msg)
    {
    case WM_CREATE : {
        pData.hover = -1;
        pData.hBrush = CreateSolidBrush(RGB(255, 255, 255));
        pData.hHoverBrush = CreateSolidBrush(RGB(255, 143, 0));
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)&pData);
    }
   
    case WM_SIZE:
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        int dx = sqrt(NumOfRect);
        int dy = NumOfRect / dx;
        int width = rc.right / dy;
        int height = rc.bottom / dx;
        for (int i = 0; i < NumOfRect; ++i)
        {
            pData.rects[i].left = (i % dy) * width;
            pData.rects[i].top = (i / dy) * height;
            pData.rects[i].right = pData.rects[i].left + width;
            pData.rects[i].bottom = pData.rects[i].top + height;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }

    case WM_MOUSEMOVE:
    {
        TRACKMOUSEEVENT tm;
        tm.cbSize = sizeof(TRACKMOUSEEVENT);
        tm.dwFlags = TME_LEAVE;
        tm.hwndTrack = hwnd;
        TrackMouseEvent(&tm);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        int prev_hover = pData.hover;
        pData.hover = -1;
        for (int i = 0; i < NumOfRect; ++i)
        {
            if (PtInRect(&pData.rects[i], { x, y }))
            {
                pData.hover = i;
                break;
            }
        }
        if (pData.hover != prev_hover)
        {
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
    case WM_MOUSELEAVE:
    {
        WindowData* pData = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        pData->hover = -1;
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(hdc, hPen);
        for (int i = 0; i < NumOfRect; ++i)

        {
            HBRUSH hCurrentBrush = (i == pData.hover) ? pData.hHoverBrush : pData.hBrush;
            FillRect(hdc, &pData.rects[i], hCurrentBrush);
            FrameRect(hdc, &pData.rects[i], (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
        DeleteObject(hPen);
        EndPaint(hwnd, &ps); 
    }
    break;
    case WM_DESTROY:
        DeleteObject(pData.hBrush);
        DeleteObject(pData.hHoverBrush);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("PARENT");
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
    RegisterClass(&wc);
    int widthWindow = 600;
    int heightWindow = 400;

    RECT Area;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &Area, 0);
    int dX = Area.left + (Area.right - Area.left - widthWindow) / 2;
    int dY = Area.top + (Area.bottom - Area.top - heightWindow) / 2;


    HWND hwndMain = CreateWindow(TEXT("PARENT"), TEXT("My Window"), WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        dX, dY, widthWindow, heightWindow,
        NULL, NULL, hInstance, NULL);

    if (!hwndMain)
    {
        return -1;
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}





