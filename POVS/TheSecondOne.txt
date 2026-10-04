#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    LPCTSTR szClass = TEXT("MyWindowClass");

    WNDCLASS wndclass = {};
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.lpszClassName = szClass;
    // Система не подставляет никакой «базовый» цвет, она вообще перестает закрашивать фон, всё делает программист.
    wndclass.hbrBackground = 0; 

    ::RegisterClass(&wndclass);

    // Создаём главное окно
    HWND hWnd = ::CreateWindow(szClass, TEXT("Test - Rectangles"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL) {
        return -1;
    }

    ::ShowWindow(hWnd, nCmdShow);
    // ::UpdateWindow(hWnd);

    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0)) {
        // ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // для хранения текущего выделенного прямоугольника между вызовами сообщений.
    static RECT hoveredRect = { 0, 0, 0, 0 };

    int N = 6; // 4/6/9
    int ROWS, COLS;

    switch (N) {
    case 4:
        ROWS = 2; COLS = 2;
        break;
    case 6:
        ROWS = 2; COLS = 3; // Или наоборот
        break;
    case 9:
        ROWS = 3; COLS = 3;
        break;
    default:
        // Иначе оставляем 4
        ROWS = 2; COLS = 2;
        break;
    }

    switch (message) {

    case WM_MOUSEMOVE:
    {
        // Получаем координаты курсора #include <windowsx.h>
        POINT point;
        point.x = (short)LOWORD(lParam); // point.x = GET_X_LPARAM(lParam); Извлекает младшие 16 бит
		point.y = (short)HIWORD(lParam); // point.y = GET_Y_LPARAM(lParam); Тут старшие
		// Приведение к short необходимо, чтобы корректно обрабатывать отрицательные значения при выходе курсора за пределы окна
        // так как в противном случае превратится в большое число.

        RECT clientRect; // получает текущие физические размеры клиентской области окна в пикселях. Содержит все 4 стороны
        ::GetClientRect(hWnd, &clientRect); // Для клиентской области Windows всегда устанавливает left = 0 и top = 0

        // Вычисляем ширину и высоту одной ячейки
        // Значение right равно точной ширине области в пикселях, а bottom — её высоте.
        int cellW = clientRect.right / COLS;
        int cellH = clientRect.bottom / ROWS;

        RECT currentRect = { 0, 0, 0, 0 };
        bool found = false;

        // Определяем, в каком прямоугольнике находится курсор
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                RECT rect;
				rect.left = c * cellW; // сдвиг по горизонтали
				rect.top = r * cellH; // сдвиг по вертикали
                // Предотвращаем потерю пикселей при делении
				rect.right = (c == COLS - 1) ? clientRect.right : (c + 1) * cellW; // Если это последняя колонка, то правый край совпадает с правым краем клиентской области
                rect.bottom = (r == ROWS - 1) ? clientRect.bottom : (r + 1) * cellH;

                if (::PtInRect(&rect, point)) { // возвращает TRUE, если точка point лежит внутри rect
                    currentRect = rect;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }

        // Если прямоугольник под мышью изменился, запрашиваем перерисовку
        if (!::EqualRect(&hoveredRect, &currentRect)) { // Компьютер перерисовывал окно десятки раз в секунду, даже когда курсор просто ползает внутри одного и того же квадрата
            hoveredRect = currentRect;
			::InvalidateRect(hWnd, NULL, TRUE); // дескриптор; недейстивительное окно; фон должен быть перерисован
        }
        break;
    }

    case WM_NCMOUSEMOVE:
    {
        // Когда мышь переходит на неклиентскую область,
        // сбрасываем выделение и восстанавливаем фон.
        RECT emptyRect = { 0, 0, 0, 0 };
        if (!::EqualRect(&hoveredRect, &emptyRect)) {
            hoveredRect = emptyRect;
            ::InvalidateRect(hWnd, NULL, TRUE);
        }

        // Передать дальше, чтобы система могла обрабатывать кнопки окна и рамку!
		return ::DefWindowProc(hWnd, message, wParam, lParam); // без неё не будет работать кнопка закрытия окна и рамка, т.к неизвестно, что мышь находится на рамке
    }

    case WM_PAINT:
    {
        PAINTSTRUCT paintstruct;
        HDC hDC = ::BeginPaint(hWnd, &paintstruct);

        RECT clientRect;
        ::GetClientRect(hWnd, &clientRect);

        HBRUSH hBgBrsh = (HBRUSH)::GetStockObject(WHITE_BRUSH);
        ::FillRect(hDC, &clientRect, hBgBrsh);
        // ::DeleteObject(hBgBrsh); // Если не удалять кисти после использования, произойдет утечка памяти, и интерфейс начнет рассыпаться.

        // Если есть выделенный прямоугольник, закрашиваем его другим цветом
        RECT emptyRect = { 0, 0, 0, 0 };
        if (!::EqualRect(&hoveredRect, &emptyRect)) {
            HBRUSH hBrsh = ::CreateSolidBrush(RGB(255, 110, 0)); // Светло-голубой цвет - 173, 216, 230
            ::FillRect(hDC, &hoveredRect, hBrsh);
            ::DeleteObject(hBrsh);
        }

        // Отрисовка линий сетки (карандаш 2 пикселя)
        HPEN hPen = ::CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Сплошная линия(??); толщина; Черный цвет
        HPEN oPen = (HPEN)::SelectObject(hDC, hPen); // привязываем созданное перо к холсту

        int cellW = clientRect.right / COLS;
        int cellH = clientRect.bottom / ROWS;

        // Рисуем вертикальные линии
		for (int c = 1; c < COLS; ++c) { // начинаем с 1, чтобы не рисовать линию в начале
            ::MoveToEx(hDC, c * cellW, 0, NULL); // переносит перо в стартовую точку над холстом, не оставляя следа.
            ::LineTo(hDC, c * cellW, clientRect.bottom); // чертит прямую линию до указанных координат (??)
        }

        // Рисуем горизонтальные линии
        for (int r = 1; r < ROWS; ++r) {
            ::MoveToEx(hDC, 0, r * cellH, NULL);
            ::LineTo(hDC, clientRect.right, r * cellH);
        }

        ::SelectObject(hDC, oPen); // возвращает холсту первоначальное перо
		::DeleteObject(hPen); // удаляем созданное перо, чтобы не было утечки памяти

        ::EndPaint(hWnd, &paintstruct);
        break;
    }

    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}