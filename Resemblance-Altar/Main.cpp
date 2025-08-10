#include "window_win.h"
#include "OpenGL_Base.h"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    EGL::window_win window;
    if (!window.create(L"Resemblance Altar", 960, 640)) {
        return -1;
    }

    HWND hwnd = window.get_hwnd();
    EGL::OpenGL_Base gl;
    if (!gl.initialize(hwnd)) {
        return -2;
    }

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        gl.render();
    }

    gl.cleanup();
    return 0;
}