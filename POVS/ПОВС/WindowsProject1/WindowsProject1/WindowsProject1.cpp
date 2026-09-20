#include <Windows.h> // Подключение заголовочного файла для работы с функциями Windows API

// Определение обработчиков сообщений для каждого окна
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK TempWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

HWND hChildWnd; // Объявление глобальной переменной для хранения дескриптора дочернего окна


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    // Определение структуры WNDCLASS для регистрации классов окон
    static TCHAR szMainClass[] = TEXT("MainWin");
    static PCSTR szTempClass  = "TempWin";
    static TCHAR szChildClass[] = TEXT("ChildWin");
    HWND         hwnd; // Дескриптор главного окна.
    MSG          msg; // Структура для обработки сообщений.
    WNDCLASS     wndclass; // Структура для определения параметров класса окна

    // Заполнение структуры WNDCLASS для главного окна
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;

    // Регистрация класса главного окна
    wndclass.lpfnWndProc = MainWndProc;
    wndclass.lpszClassName = szMainClass;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szMainClass, MB_ICONERROR);
        return 0;
    }
    
    // Регистрация класса временного окна
    wndclass.lpfnWndProc = TempWndProc;
    wndclass.lpszClassName = szTempClass;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szTempClass, MB_ICONERROR);
        return 0;
    }

    // Регистрация класса дочернего окна
    wndclass.lpfnWndProc = ChildWndProc;
    wndclass.lpszClassName = szChildClass;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szChildClass, MB_ICONERROR);
        return 0;
    }

    // Создание главного окна
    hwnd = CreateWindow(szMainClass,
        TEXT("Main Window"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    // Обработка ошибки создания главного окна
    if (!hwnd) {
        MessageBox(NULL, "Failed to create main window.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    HWND hwndTemp = CreateWindow(TEXT("TempWin"), TEXT("Temporary Window"),
        WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        100, 100,
        200, 200,
        hwnd, NULL,
        hInstance, NULL);

    if (!hwndTemp) {
        MessageBox(NULL, "Failed to create temporary window.", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // Установка стиля WS_EX_TOOLWINDOW для временного окна
    //SetWindowLong(hwndTemp, GWL_EXSTYLE, GetWindowLong(hwndTemp, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

    // Отображение и обновление временного окна
    //ShowWindow(hwndTemp, SW_SHOW);
    //UpdateWindow(hwndTemp);

    // Создание дочернего окна с определенными параметрами и стилем
    hChildWnd = CreateWindow(TEXT("ChildWin"), TEXT("Child Window"),
        WS_CHILDWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        0, 0,
        100, 100,
        hwnd, NULL,
        hInstance, NULL);

    if (!hChildWnd) {
        MessageBox(NULL, "Failed to create child window.", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // Установка стиля WS_EX_TOOLWINDOW для дочернего окна
    //SetWindowLong(hChildWnd, GWL_EXSTYLE, GetWindowLong(hChildWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

    // Отображение и обновление дочернего окна.
    //ShowWindow(hChildWnd, SW_SHOW);
    //UpdateWindow(hChildWnd);


    // Отображение и обновление главного окна
    ShowWindow(hwnd, iCmdShow);
    //UpdateWindow(hwnd);

    // Основной цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Обработчик сообщений для главного окна
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndTemp; // Статическая переменная для временного окна

    switch (message)
    {
    case WM_CREATE:
        // Создание временного окна с определенными параметрами и стилем

        return 0;

    case WM_LBUTTONDOWN:

        // Установка дочернего окна как дочернего для главного окна
        if (!SetParent(hChildWnd, hwnd)) {
            MessageBox(NULL, "Failed to set parent window.", "Error", MB_OK | MB_ICONERROR);
        }
        return 0;

    case WM_DESTROY:
        // Завершение программы.
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// Обработчик сообщений для временного окна.
LRESULT CALLBACK TempWndProc(HWND hwndTemp, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_LBUTTONDOWN:

        // Установка дочернего окна как дочернего для временного окна.
        if (!SetParent(hChildWnd, hwndTemp)) {
            MessageBox(NULL, "Failed to set parent window.", "Error", MB_OK | MB_ICONERROR);
        }
        return 0;

    case WM_RBUTTONDOWN:
    {

        // Установка(снятие) расширенного стиля TOPMOST.
        //DWORD dwStyle = GetWindowLong(hwndTemp, GWL_EXSTYLE);

        if (GetWindowLong(hwndTemp, GWL_EXSTYLE) & WS_EX_TOPMOST) {
            SetWindowPos(hwndTemp, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
        else
            SetWindowPos(hwndTemp, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    }

    return DefWindowProc(hwndTemp, message, wParam, lParam);
}

// Обработчик сообщений для дочернего окна.
LRESULT CALLBACK ChildWndProc(HWND hwndChild, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwndChild, message, wParam, lParam);
}