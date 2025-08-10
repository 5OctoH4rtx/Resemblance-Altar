#pragma once
#include <windows.h>

namespace EGL {

class window_win_impl; // Forward declaration

class window_win {
public:
    window_win();
    ~window_win();

    bool create(const wchar_t* title, int width, int height);
    void message_loop();

    HWND get_hwnd() const; // <-- Added accessor for HWND

private:
    window_win_impl* impl;
};

} // namespace EGL

