#define  STRICT
#define  WIN32_LEAN_AND_MEAN

#include <Windows.h>

// Предварительное объявление оконных процедур
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK TempWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

HWND hChildWnd = NULL; // Дескриптор дочернего окна

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PSTR szCmdLine,
    _In_ int iCmdShow)
{
    // Используем единый тип TCHAR / LPCTSTR и макрос TEXT(...) во избежание конфликтов Unicode
    LPCTSTR szMainClass = TEXT("MainWin");
    LPCTSTR szTempClass = TEXT("TempWin");
    LPCTSTR szChildClass = TEXT("ChildWin");

    HWND hwnd;
    MSG  msg;
    WNDCLASS wndclass = {}; // Инициализация нулями

    // Базовые общие настройки классов
    //wndclass.style = CS_HREDRAW | CS_VREDRAW; ??
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Не пропадает окно

    // Регистрация класса главного окна
    wndclass.lpfnWndProc = MainWndProc;
    wndclass.lpszClassName = szMainClass;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Failed to register MainWin class!"), szMainClass, MB_ICONERROR);
        return 0; // что покупатель будет делать с этим?
    }

    // 2. Регистрация класса временного окна
    wndclass.lpfnWndProc = TempWndProc;
    wndclass.lpszClassName = szTempClass;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Failed to register TempWin class!"), szTempClass, MB_ICONERROR);
        return 0;
    }

    // 3. Регистрация класса дочернего окна
    wndclass.lpfnWndProc = ChildWndProc;
    wndclass.lpszClassName = szChildClass;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Failed to register ChildWin class!"), szChildClass, MB_ICONERROR);
        return 0;
    }

    // Создание главного окна
    hwnd = CreateWindow(
        szMainClass,
        TEXT("Main Window"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, // что ето, зачем ето, как ето
        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, TEXT("Failed to create main window."), TEXT("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // Создание временного окна
    HWND hwndTemp = CreateWindow(
        szTempClass,
        TEXT("Temporary Window"),
        WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        100, 100, 200, 200,
        hwnd, NULL, hInstance, NULL);

    if (!hwndTemp) {
        MessageBox(NULL, TEXT("Failed to create temporary window."), TEXT("Error"), MB_OK | MB_ICONERROR);
        return -1;
    }

    // Создание дочернего окна
    hChildWnd = CreateWindow(
        szChildClass,
        TEXT("Child Window"),
        WS_CHILDWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        0, 0, 100, 100,
        hwnd, NULL, hInstance, NULL);

    if (!hChildWnd) {
        MessageBox(NULL, TEXT("Failed to create child window."), TEXT("Error"), MB_OK | MB_ICONERROR);
        return -1;
    }

    ShowWindow(hwnd, iCmdShow);

    // Основной цикл сообщений
    while (GetMessage(&msg, NULL, 0, 0))
    {
        //TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;//?? (int)msg.wParam;
}

// Обработчик сообщений главного окна
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        // Если дочернее окно закрыто или уничтожено — выходим без ошибки
        if (!hChildWnd || !IsWindow(hChildWnd)) {
            return 0;
        }

        // Если окно уже внутри главного — ничего не делаем
        if (GetParent(hChildWnd) == hwnd) {
            return 0;
        }

        // Перемещаем дочернее окно в главное
        if (!SetParent(hChildWnd, hwnd)) {
            MessageBox(hwnd, TEXT("Failed to set parent window."), TEXT("Error"), MB_OK | MB_ICONERROR);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// Обработчик сообщений временного окна
LRESULT CALLBACK TempWndProc(HWND hwndTemp, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        // Проверяем физическое существование окна
        if (!hChildWnd || !IsWindow(hChildWnd)) {
            return 0;
        }

        // Если окно уже во временном — не перепривязываем
        if (GetParent(hChildWnd) == hwndTemp) {
            return 0;
        }

        // Переносим дочернее окно во временное
        if (!SetParent(hChildWnd, hwndTemp)) {
            MessageBox(hwndTemp, TEXT("Failed to set parent window."), TEXT("Error"), MB_OK | MB_ICONERROR);
        }
        return 0;

    case WM_RBUTTONDOWN:
    {
        LONG_PTR exStyle = GetWindowLongPtr(hwndTemp, GWL_EXSTYLE);
//Мы берем текущие расширенные стили окна (exStyle) и накладываем маску WS_EX_TOPMOST. 
// Это проверка: "Включен ли у окна флаг поверх_всех_окон прямо сейчас?
        if (exStyle & WS_EX_TOPMOST) // НАИОТЛИЧНЕЙШИЙ ВОПРОС
        {
            SetWindowPos(hwndTemp, HWND_NOTOPMOST, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED); 
            // какое окно меняем; поместить окно позади всех TOPMOST;...;не передавать фокус этому окну; заставить ОС пересчитать границы окна
        }
        else
        {
            SetWindowPos(hwndTemp, HWND_TOPMOST, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
        }
        return 0;
    }
    }

    return DefWindowProc(hwndTemp, message, wParam, lParam);
}

// Обработчик сообщений дочернего окна
LRESULT CALLBACK ChildWndProc(HWND hwndChild, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // Сбрасываем дескриптор при закрытии, предотвращая обращение к мертвому окну
        hChildWnd = NULL; // зачем это, если уже была проверка
        return 0; // способ заставить переменную сказать: «Этого окна больше не существует, дескриптор аннулирован».
    }

    return DefWindowProc(hwndChild, message, wParam, lParam);
}