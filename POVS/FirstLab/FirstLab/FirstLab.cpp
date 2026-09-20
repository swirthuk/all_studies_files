///////////////////////////////////////////////////////////
//	Test.cpp
//
//	Одно главное, одно временное, одно дочернее окно.
//	ЛКМ в клиентской части главного/временного окна делает его
//	родителем дочернего (SetParent).
//	Двойной ЛКМ в клиентской части временного окна переключает
//	расширенный стиль WS_EX_TOPMOST (SetWindowPos).
//
//	Один класс окна, одна оконная функция, глобальные переменные —
//	как разрешено методичкой.
//
#define  STRICT
#define  WIN32_LEAN_AND_MEAN

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// ---- глобальные хэндлы окон и состояние ------------------
HWND g_hMain = NULL;
HWND g_hTemp = NULL;
HWND g_hChild = NULL;
BOOL g_bTopMost = FALSE;	// текущее состояние TOPMOST у временного окна

//=========================================================
int WINAPI  WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE, // hPrevInstance,
    _In_ LPSTR, // lpCmdLine,
    _In_ int nCmdShow
)
{
    LPCTSTR szClass = TEXT("LabWndClass");

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = szClass;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    ::RegisterClass(&wc);

    // Все окна должны иметь заголовок, изменять размер,
    // кнопки "Свернуть" и "Распахнуть" -> WS_OVERLAPPEDWINDOW
    // (включает WS_CAPTION | WS_SYSMENU | WS_THICKFRAME |
    //  WS_MINIMIZEBOX | WS_MAXIMIZEBOX).

    // 1. Главное окно
    g_hMain = ::CreateWindow(szClass, TEXT("Главное окно"), WS_OVERLAPPEDWINDOW,
        50, 50, 400, 300, NULL, NULL, hInstance, NULL);
    if (g_hMain == NULL) return -1;

    // 2. Временное окно
    g_hTemp = ::CreateWindow(szClass, TEXT("Временное окно"), WS_OVERLAPPEDWINDOW,
        500, 50, 400, 300, NULL, NULL, hInstance, NULL);
    if (g_hTemp == NULL) return -1;

    // 3. Дочернее окно — изначально дочернее по отношению к главному.
    //    WS_CHILD совместим с WS_CAPTION/WS_SYSMENU/WS_THICKFRAME/
    //    WS_MINIMIZEBOX/WS_MAXIMIZEBOX — окно рисуется внутри клиентской
    //    области родителя, но сохраняет заголовок, рамку и кнопки.
    g_hChild = ::CreateWindow(szClass, TEXT("Дочернее окно"),
        WS_CHILD | WS_VISIBLE | WS_CAPTION | WS_SYSMENU |
        WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
        20, 20, 200, 150, g_hMain, NULL, hInstance, NULL);
    if (g_hChild == NULL) return -1;

    ::ShowWindow(g_hMain, nCmdShow);
    ::ShowWindow(g_hTemp, nCmdShow);
    ::ShowWindow(g_hChild, nCmdShow);

    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return 0;
}
//=========================================================

// Переносит дочернее окно к новому родителю и располагает его
// по центру клиентской области этого родителя.
static void ReparentChildTo(HWND hNewParent)
{
    if (g_hChild == NULL || !::IsWindow(g_hChild)) return;
    if (::GetParent(g_hChild) == hNewParent) return;	// уже родитель

    ::SetParent(g_hChild, hNewParent);

    RECT rcParent, rcChild;
    ::GetClientRect(hNewParent, &rcParent);
    ::GetClientRect(g_hChild, &rcChild);

    int cw = rcChild.right - rcChild.left;
    int ch = rcChild.bottom - rcChild.top;
    int x = (rcParent.right - rcParent.left - cw) / 2;
    int y = (rcParent.bottom - rcParent.top - ch) / 2;
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    ::SetWindowPos(g_hChild, NULL, x, y, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
}

//=========================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_LBUTTONDOWN:
        // Клик в клиентской части главного или временного окна ->
        // это окно становится родителем дочернего.
        if (hWnd == g_hMain || hWnd == g_hTemp) {
            ReparentChildTo(hWnd);
        }
        return 0;

    case WM_LBUTTONDBLCLK:
        // Двойной клик в клиентской части временного окна ->
        // переключить WS_EX_TOPMOST.
        if (hWnd == g_hTemp) {
            g_bTopMost = !g_bTopMost;
            ::SetWindowPos(hWnd, g_bTopMost ? HWND_TOPMOST : HWND_NOTOPMOST,
                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
        return 0;

    case WM_CLOSE:
        ::DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
        if (hWnd == g_hMain) {
            g_hMain = NULL;
            ::PostQuitMessage(0);
        }
        else if (hWnd == g_hTemp) {
            g_hTemp = NULL;
        }
        else if (hWnd == g_hChild) {
            g_hChild = NULL;
        }
        return 0;
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}
//=========================================================
