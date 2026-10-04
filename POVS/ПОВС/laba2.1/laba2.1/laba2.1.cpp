#define STRICT
#define WIN32_LEAN_AND_MEAN 

// Поддерживаемые значения N: 4, 6, 9
#define NumOfRect 9

#include <windows.h>

struct WindowData
{
    RECT rects[NumOfRect];
    int hover;
    int rows;
    int cols;
};

// Функция определения сетки (строки x столбцы) для N = 4, 6, 9
void GetGridDimensions(int n, int& rows, int& cols)
{
    switch (n)
    {
    case 4: rows = 2; cols = 2; break;
    case 6: rows = 2; cols = 3; break;
    case 9: rows = 3; cols = 3; break;
    default: rows = 1; cols = n; break;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Извлекаем указатель на данные экземпляра окна (без глобальных переменных)
    WindowData* pData = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (msg)
    {
    case WM_CREATE:
    {
        pData = new WindowData();
        pData->hover = -1;
        GetGridDimensions(NumOfRect, pData->rows, pData->cols);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pData);
        return 0;
    }

    case WM_SIZE:
    {
        if (!pData) break;

        RECT rc;
        GetClientRect(hwnd, &rc);

        int clientWidth = rc.right - rc.left;
        int clientHeight = rc.bottom - rc.top;

        // Расчёт прямоугольников с точным заполнением без потерь на округление
        for (int i = 0; i < NumOfRect; ++i)
        {
            int r = i / pData->cols;
            int c = i % pData->cols;

            pData->rects[i].left = (c * clientWidth) / pData->cols;
            pData->rects[i].right = ((c + 1) * clientWidth) / pData->cols;
            pData->rects[i].top = (r * clientHeight) / pData->rows;
            pData->rects[i].bottom = ((r + 1) * clientHeight) / pData->rows;
        }

        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }

    case WM_MOUSEMOVE:
    {
        if (!pData) break;

        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        int prevHover = pData->hover;
        pData->hover = -1;

        for (int i = 0; i < NumOfRect; ++i)
        {
            if (PtInRect(&pData->rects[i], pt))
            {
                pData->hover = i;
                break;
            }
        }

        if (pData->hover != prevHover)
        {
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    }

    // По условию: при выходе курсора на неклиентскую область (рамка, заголовок)
    case WM_NCMOUSEMOVE:
    {
        if (pData && pData->hover != -1)
        {
            pData->hover = -1;
            InvalidateRect(hwnd, NULL, FALSE);
        }
        break; // Обязательно передаём дальше в DefWindowProc для работы заголовка и кнопок окна
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (pData)
        {
            RECT clientRc;
            GetClientRect(hwnd, &clientRc);

            // 1. Закраска прямоугольников
            for (int i = 0; i < NumOfRect; ++i)
            {
                COLORREF color = (i == pData->hover) ? RGB(255, 143, 0) : RGB(255, 255, 255);
                HBRUSH hBrush = CreateSolidBrush(color);
                FillRect(hdc, &pData->rects[i], hBrush);
                DeleteObject(hBrush);
            }

            // 2. Разделительные прямые линии толщиной 2 пикселя через MoveToEx / LineTo
            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            HPEN oPen = (HPEN)SelectObject(hdc, hPen);

            // Вертикальные линии сетки
            for (int c = 1; c < pData->cols; ++c)
            {
                int x = (c * clientRc.right) / pData->cols;
                MoveToEx(hdc, x, 0, NULL);
                LineTo(hdc, x, clientRc.bottom);
            }

            // Горизонтальные линии сетки
            for (int r = 1; r < pData->rows; ++r)
            {
                int y = (r * clientRc.bottom) / pData->rows;
                MoveToEx(hdc, 0, y, NULL);
                LineTo(hdc, clientRc.right, y);
            }

            // Восстановление старого пера и удаление созданного
            SelectObject(hdc, oPen);
            DeleteObject(hPen);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
    {
        if (pData)
        {
            delete pData;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
        }
        PostQuitMessage(0);
        return 0;
    }

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("PARENT");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&wc);

    int widthWindow = 600;
    int heightWindow = 400;

    RECT Area;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &Area, 0);
    int dX = Area.left + (Area.right - Area.left - widthWindow) / 2;
    int dY = Area.top + (Area.bottom - Area.top - heightWindow) / 2;

    HWND hwndMain = CreateWindow(
        TEXT("PARENT"),
        TEXT("Grid Window"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        dX, dY, widthWindow, heightWindow,
        NULL, NULL, hInstance, NULL
    );

    if (!hwndMain)
    {
        return -1;
    }

    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}