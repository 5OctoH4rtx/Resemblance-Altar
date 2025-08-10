#include "OpenGL_Base.h"
#include <GL/gl.h>

namespace EGL {

OpenGL_Base::OpenGL_Base() {}

OpenGL_Base::~OpenGL_Base() {
    cleanup();
}

bool OpenGL_Base::initialize(HWND hwnd) {
    hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pf = ChoosePixelFormat(hdc, &pfd);
    if (pf == 0) return false;
    if (!SetPixelFormat(hdc, pf, &pfd)) return false;

    hglrc = wglCreateContext(hdc);
    if (!hglrc) return false;
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    return true;
}

void OpenGL_Base::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Example: draw nothing, just clear
    SwapBuffers(hdc);
}

void OpenGL_Base::cleanup() {
    if (hglrc) {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(hglrc);
        hglrc = nullptr;
    }
    if (hdc) {
        ReleaseDC(WindowFromDC(hdc), hdc);
        hdc = nullptr;
    }
}

} // namespace EGL
