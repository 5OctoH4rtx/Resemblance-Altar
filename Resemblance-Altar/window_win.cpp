#include "window_win.h"
#include <windows.h>

namespace EGL {

class window_win_impl {
public:
    HWND hwnd = nullptr;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    bool create(const wchar_t* title, int width, int height) {
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"EGLWindowClass";

        RegisterClass(&wc);

        // Calculate centered position
        RECT desktopRect;
        HWND desktop = GetDesktopWindow();
        GetWindowRect(desktop, &desktopRect);
        int screenWidth = desktopRect.right - desktopRect.left;
        int screenHeight = desktopRect.bottom - desktopRect.top;

        // Adjust for window style (so client area is correct size)
        RECT windowRect = { 0, 0, width, height };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
        int winWidth = windowRect.right - windowRect.left;
        int winHeight = windowRect.bottom - windowRect.top;

        int x = (screenWidth - winWidth) / 2;
        int y = (screenHeight - winHeight) / 2;

        hwnd = CreateWindowEx(
            0,
            wc.lpszClassName,
            title,
            WS_OVERLAPPEDWINDOW,
            x, y, winWidth, winHeight,
            nullptr, nullptr, wc.hInstance, nullptr
        );

        if (!hwnd) return false;

        ShowWindow(hwnd, SW_SHOW);
        return true;
    }

    void message_loop() {
        MSG msg = {};
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
};

window_win::window_win() : impl(new window_win_impl) {}

window_win::~window_win() { delete impl; }

bool window_win::create(const wchar_t* title, int width, int height) {
    return impl->create(title, width, height);
}

void window_win::message_loop() {
    impl->message_loop();
}

HWND window_win::get_hwnd() const {
    return impl ? impl->hwnd : nullptr;
}

} // namespace EGL
