#pragma once
#include <windows.h>

namespace EGL {

class OpenGL_Base {
public:
    OpenGL_Base();
    ~OpenGL_Base();

    bool initialize(HWND hwnd);
    void render();
    void cleanup();

private:
    HDC hdc = nullptr;
    HGLRC hglrc = nullptr;
};

} // namespace EGL

