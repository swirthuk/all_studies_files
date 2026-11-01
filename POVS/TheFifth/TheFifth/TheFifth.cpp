#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

enum MenuCommands {
    IDM_EXIT = 40001,
    IDM_START = 40068,
    IDM_STOP = 40070
};

// Константы (не являются изменяемыми глобальными переменными)
const UINT_PTR TIMER_ID = 1;
const UINT     TIMER_DELAY = 100; // 100 мс (10 кадров в секунду)
const int      STEP_ANGLE = 300; // Шаг K = 30 градусов (в LOGFONT задается в десятых долях градуса)
const int      STEP_HEIGHT = 4;   // Шаг изменения высоты шрифта
const int      MIN_HEIGHT = 8;   // Минимальная высота шрифта

struct AppState {
    int   angle;      // Текущий угол в десятых долях градуса (0..3599)
    int   fontHeight; // Текущая высота шрифта
    BOOL  isRunning;  // Флаг работы таймера
    HFONT hFont;      // Кэшированный дескриптор шрифта
};

// Пересоздание шрифта при изменении угла или высоты (вне WM_PAINT)
void UpdateAppFont(AppState* pState)
{
    if (!pState) return;

    if (pState->hFont) {
        ::DeleteObject(pState->hFont);
    }

    LOGFONT lf = {};
    lf.lfHeight = pState->fontHeight;
    lf.lfEscapement = pState->angle; // Угол наклона строки
    lf.lfOrientation = pState->angle; // Угол наклона отдельных символов
    lf.lfWeight = FW_BOLD;       // 700 (как в образце)
    lf.lfCharSet = RUSSIAN_CHARSET;
    lf.lfOutPrecision = OUT_TT_ONLY_PRECIS; // Только TrueType, чтобы гарантировать вращение
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = PROOF_QUALITY;
    lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
    ::lstrcpy(lf.lfFaceName, TEXT("Arial"));

    pState->hFont = ::CreateFontIndirect(&lf);
}

// Программное создание меню
HMENU CreateAppMenu()
{
    HMENU hMainMenu = ::CreateMenu();
    HMENU hFileMenu = ::CreatePopupMenu();
    HMENU hActionMenu = ::CreatePopupMenu();

    ::AppendMenu(hFileMenu, MF_STRING, IDM_EXIT, TEXT("Выход"));

    // При старте вращение еще не запущено: "Запустить" активна, "Остановить" серая
    ::AppendMenu(hActionMenu, MF_STRING | MF_ENABLED, IDM_START, TEXT("Запустить"));
    ::AppendMenu(hActionMenu, MF_STRING | MF_GRAYED, IDM_STOP, TEXT("Остановить"));

    ::AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hFileMenu, TEXT("Файл"));
    ::AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hActionMenu, TEXT("Действия"));

    return hMainMenu;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE,
    _In_ LPSTR,
    _In_ int nCmdShow)
{
    LPCTSTR szClass = TEXT("Tester");

    WNDCLASS wndclass = {};
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName = szClass;

    if (!::RegisterClass(&wndclass)) {
        return FALSE;
    }

    // Локальное состояние приложения (без глобальных переменных)
    AppState state = {};
    state.angle = 0;
    state.fontHeight = 40;
    state.isRunning = FALSE;
    state.hFont = NULL;

    // Центрирование окна (размер в половину экрана, как в эталоне)
    int screenW = ::GetSystemMetrics(SM_CXSCREEN);
    int screenH = ::GetSystemMetrics(SM_CYSCREEN);
    int winW = screenW / 2;
    int winH = screenH / 2;
    int posX = (screenW - winW) / 2;
    int posY = (screenH - winH) / 2;

    HMENU hMenu = CreateAppMenu();

    HWND hWnd = ::CreateWindow(
        szClass,
        TEXT("Tester"),
        WS_OVERLAPPEDWINDOW,
        posX, posY, winW, winH,
        NULL, hMenu, hInstance, &state);

    if (!hWnd) {
        ::DestroyMenu(hMenu);
        return FALSE;
    }

    ::ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0)) {
        ::DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    AppState* pState = (AppState*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (message) {

    case WM_CREATE:
    {
        CREATESTRUCT* pCS = (CREATESTRUCT*)lParam;
        pState = (AppState*)pCS->lpCreateParams;
        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pState);

        // Создаем начальный шрифт один раз при инициализации окна
        UpdateAppFont(pState);
        return 0;
    }

    case WM_SIZE:
        // При изменении размеров окна центр смещается — запрашиваем перерисовку с очисткой фона
        ::InvalidateRect(hWnd, NULL, TRUE);
        return 0;

    case WM_COMMAND:
    {
        if (!pState) return 0;

        switch (LOWORD(wParam)) {
        case IDM_EXIT:
            ::DestroyWindow(hWnd);
            break;

        case IDM_START:
            if (!pState->isRunning) {
                ::SetTimer(hWnd, TIMER_ID, TIMER_DELAY, NULL);
                pState->isRunning = TRUE;

                HMENU hMenu = ::GetMenu(hWnd);
                ::EnableMenuItem(hMenu, IDM_START, MF_BYCOMMAND | MF_GRAYED);
                ::EnableMenuItem(hMenu, IDM_STOP, MF_BYCOMMAND | MF_ENABLED);
            }
            break;

        case IDM_STOP:
            if (pState->isRunning) {
                ::KillTimer(hWnd, TIMER_ID);
                pState->isRunning = FALSE;

                HMENU hMenu = ::GetMenu(hWnd);
                ::EnableMenuItem(hMenu, IDM_START, MF_BYCOMMAND | MF_ENABLED);
                ::EnableMenuItem(hMenu, IDM_STOP, MF_BYCOMMAND | MF_GRAYED);
            }
            break;
        }
        return 0;
    }

    case WM_TIMER:
    {
        if (!pState || wParam != TIMER_ID) return 0;

        // Поворачиваем на шаг K (30 градусов = 300 десятых долей)
        pState->angle += STEP_ANGLE;
        if (pState->angle >= 3600) {
            pState->angle -= 3600;
        }

        UpdateAppFont(pState);
        ::InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    case WM_LBUTTONUP:
    {
        if (!pState) return 0;

        // Отпускание ЛКМ увеличивает высоту шрифта
        pState->fontHeight += STEP_HEIGHT;
        UpdateAppFont(pState);
        ::InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    case WM_RBUTTONUP:
    {
        if (!pState) return 0;

        // Отпускание ПКМ уменьшает высоту шрифта (не ниже порога MIN_HEIGHT)
        if (pState->fontHeight - STEP_HEIGHT >= MIN_HEIGHT) {
            pState->fontHeight -= STEP_HEIGHT;
            UpdateAppFont(pState);
            ::InvalidateRect(hWnd, NULL, TRUE);
        }
        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC = ::BeginPaint(hWnd, &ps);

        if (pState && pState->hFont) {
            RECT rcClient;
            ::GetClientRect(hWnd, &rcClient);

            ::SetBkMode(hDC, TRANSPARENT);
            // Привязка точки вывода к центру строки и базовой линии
            ::SetTextAlign(hDC, TA_CENTER | TA_BASELINE);

            HFONT hOldFont = (HFONT)::SelectObject(hDC, pState->hFont);

            LPCTSTR szText = TEXT("Test string");
            int centerX = (rcClient.right - rcClient.left) / 2;
            int centerY = (rcClient.bottom - rcClient.top) / 2;

            ::TextOut(hDC, centerX, centerY, szText, ::lstrlen(szText));

            ::SelectObject(hDC, hOldFont);
        }

        ::EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_DESTROY:
    {
        if (pState) {
            if (pState->isRunning) {
                ::KillTimer(hWnd, TIMER_ID);
                pState->isRunning = FALSE;
            }
            if (pState->hFont) {
                ::DeleteObject(pState->hFont);
                pState->hFont = NULL;
            }
        }
        ::PostQuitMessage(0);
        return 0;
    }
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}