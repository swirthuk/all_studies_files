#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>
#include <time.h>

// Константы из задания
const int M_WIDTH = 3000;
const int N_HEIGHT = 2000;
const int K_POINTS = 500;
const int RADIUS = 50;

// Структура для хранения состояния приложения (избавляемся от глобальных переменных)
struct AppState {
    POINT points[K_POINTS];
    int scrollX;
    int scrollY;
    int clientW;
    int clientH;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    LPCTSTR szClass = TEXT("ScrollWindowClass");
    WNDCLASS wndclass = {};

    // Учтено замечание: добавлены флаги для перерисовки при изменении размера окна
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName = szClass;

    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"), TEXT("Ошибка"), MB_ICONERROR);
        return -1; // Учтено замечание: возвращаем код ошибки, а не 0
    }

    // Инициализация данных
    AppState state = { 0 };
    srand((unsigned int)time(NULL));

    // Генерируем K_POINTS псевдослучайных точек (центры окружностей)
    for (int i = 0; i < K_POINTS; ++i) {
        // Учитываем радиус, чтобы круги не обрезались краями виртуальной области
        state.points[i].x = RADIUS + rand() % (M_WIDTH - 2 * RADIUS);
        state.points[i].y = RADIUS + rand() % (N_HEIGHT - 2 * RADIUS);
    }

    // Создаем окно и передаем указатель на state параметром lpParam
    HWND hWnd = CreateWindow(szClass, TEXT("Оптимальный скроллинг"),
        WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, &state);

    if (!hWnd) {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam; // Учтено замечание: корректный код возврата
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Извлекаем указатель на состояние окна
    AppState* pState = (AppState*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (message) {

    case WM_CREATE:
    {
        // Извлекаем lpParam (указатель на state), переданный в CreateWindow
        CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
        pState = (AppState*)pcs->lpCreateParams;

        // Сохраняем указатель в памяти окна
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pState);
        return 0;
    }

    case WM_SIZE:
    {
        if (!pState) return 0;

        pState->clientW = LOWORD(lParam);
        pState->clientH = HIWORD(lParam);

        // Настраиваем горизонтальную полосу прокрутки
        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        si.nMin = 0;
        si.nMax = M_WIDTH - 1; // Размер виртуальной области
        si.nPage = pState->clientW; // Размер "страницы" (клиентской части)
        si.nPos = pState->scrollX;
        SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

        // Настраиваем вертикальную полосу прокрутки
        si.nMax = N_HEIGHT - 1;
        si.nPage = pState->clientH;
        si.nPos = pState->scrollY;
        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

        return 0;
    }

    case WM_HSCROLL:
    {
        if (!pState) return 0;

        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_HORZ, &si);

        int oldPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_LINELEFT:      si.nPos -= 20; break;
        case SB_LINERIGHT:     si.nPos += 20; break;
        case SB_PAGELEFT:      si.nPos -= si.nPage; break;
        case SB_PAGERIGHT:     si.nPos += si.nPage; break;
        case SB_THUMBTRACK:    si.nPos = si.nTrackPos; break;
        }

        // Ограничиваем скролл диапазоном
        int maxPos = si.nMax - max((int)si.nPage - 1, 0);
        if (si.nPos < 0) si.nPos = 0;
        if (si.nPos > maxPos) si.nPos = maxPos;

        if (si.nPos != oldPos) {
            int dx = oldPos - si.nPos; // Вычисляем дельту сдвига
            pState->scrollX = si.nPos;

            // Физически сдвигаем пиксели. Окно пометит только "новые" участки для перерисовки
            ScrollWindow(hWnd, dx, 0, NULL, NULL);

            // Обновляем ползунок
            si.fMask = SIF_POS;
            SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
            UpdateWindow(hWnd); // Форсируем немедленную отправку WM_PAINT
        }
        return 0;
    }

    case WM_VSCROLL:
    {
        if (!pState) return 0;

        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &si);

        int oldPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_LINEUP:        si.nPos -= 20; break;
        case SB_LINEDOWN:      si.nPos += 20; break;
        case SB_PAGEUP:        si.nPos -= si.nPage; break;
        case SB_PAGEDOWN:      si.nPos += si.nPage; break;
        case SB_THUMBTRACK:    si.nPos = si.nTrackPos; break;
        }

        int maxPos = si.nMax - max((int)si.nPage - 1, 0);
        if (si.nPos < 0) si.nPos = 0;
        if (si.nPos > maxPos) si.nPos = maxPos;

        if (si.nPos != oldPos) {
            int dy = oldPos - si.nPos;
            pState->scrollY = si.nPos;

            ScrollWindow(hWnd, 0, dy, NULL, NULL);

            si.fMask = SIF_POS;
            SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
            UpdateWindow(hWnd);
        }
        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hWnd, &ps);

        if (pState) {
            // Учтено замечание: создаем кисть и перо один раз, а не внутри цикла
            HBRUSH hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // Стандартная кисть (удалять не нужно)
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 120, 200));
            HPEN oPen = (HPEN)SelectObject(hDC, hPen);
            HBRUSH oBrush = (HBRUSH)SelectObject(hDC, hBrush);

            for (int i = 0; i < K_POINTS; ++i) {
                // Вычисляем координаты центра относительно текущего положения прокрутки
                int cx = pState->points[i].x - pState->scrollX;
                int cy = pState->points[i].y - pState->scrollY;

                // Формируем прямоугольник (Bounding box) текущей окружности
                RECT rcCircle;
                rcCircle.left = cx - RADIUS;
                rcCircle.top = cy - RADIUS;
                rcCircle.right = cx + RADIUS;
                rcCircle.bottom = cy + RADIUS;

                RECT dummy;
                // ОПТИМАЛЬНОСТЬ: Проверяем, пересекается ли прямоугольник окружности
                // с прямоугольником недействительной области (ps.rcPaint).
                // Учтено замечание: передаем прямоугольники по указателю!
                if (IntersectRect(&dummy, &rcCircle, &ps.rcPaint)) {
                    Ellipse(hDC, rcCircle.left, rcCircle.top, rcCircle.right, rcCircle.bottom);
                }
            }

            SelectObject(hDC, oPen);
            SelectObject(hDC, oBrush);
            DeleteObject(hPen);
        }

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}