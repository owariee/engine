#include "Window.h"

LRESULT CALLBACK Window::RedirectPointer(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = (CREATESTRUCTW*)(lParam);
        Window* pWnd = (Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&(Window::RedirectMessage));
        return pWnd->RedirectMessage(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::RedirectMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* pWnd = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    return pWnd->WndProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(69);
        break;
    case WM_KEYDOWN:
        if (wParam == 'F')
        {
            SetWindowText(hWnd, "project d4wn");
        }
        break;
    case WM_KEYUP:
        if (wParam == 'F')
        {
            SetWindowText(hWnd, "Dawn");
        }
        break;
    case WM_CHAR:
    {
        static std::string title;
        if (wParam == VK_BACK && title.length() > 0)
        {
            title.erase(title.length() - 1);
        }
        else
        {
            title.push_back((char)wParam);
        }
        SetWindowText(hWnd, title.c_str());
    }
    break;
    case WM_LBUTTONDOWN:
    {
        //POINTS pt = MAKEPOINTS(lParam);
        //std::ostringstream oss;
        //oss << "(" << pt.x << ", " << pt.y << ")";
        //SetWindowText(hWnd, oss.str().c_str());
    }
    break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(int x, int y, int width, int height, const char className[], const char title[]) :
    className(className),
    title(title)
{
    Window::hWnd = nullptr;
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = Window::RedirectPointer;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = nullptr;
    wc.hCursor = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = Window::className.c_str();
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
    Window::hWnd = CreateWindowEx(
        0,
        Window::className.c_str(),
        Window::title.c_str(),
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        x,
        y,
        width,
        height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );
    ShowWindow((Window::hWnd), SW_SHOW);
}

Window::~Window()
{
    UnregisterClassA(Window::className.c_str(), GetModuleHandle(nullptr));
    DestroyWindow(Window::hWnd);
}

void Window::setTitle(const char title[])
{
    Window::title = std::string(title);
    SetWindowText((Window::hWnd), title);
}

const char* Window::getTitle()
{
    return Window::title.c_str();
}

const char* Window::getClassName()
{
    return Window::className.c_str();
}

HWND* Window::getHandle()
{
    return &(Window::hWnd);
}
