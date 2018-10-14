#include "context.h"
#include "error.h"
#include "window.h"
#include <ogl.h>

static HDC g_dc;

void video_context_init() {
	g_dc = GetDC(video_window_get());

	PIXELFORMATDESCRIPTOR format = {
		.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iLayerType = PFD_MAIN_PLANE,
		.cColorBits = 24
	};
	if (!SetPixelFormat(g_dc, ChoosePixelFormat(g_dc, &format), &format)) {
		video_error_win32();
	}

	HGLRC context = wglCreateContext(g_dc);
	if (context == NULL) {
		video_error_win32();
	}
	wglMakeCurrent(g_dc, context);
	video_ogl_init();

	const int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	wglMakeCurrent(g_dc, NULL);
	wglDeleteContext(context);
	context = wglCreateContextAttribsARB(g_dc, NULL, attribs);
	if (context == NULL) {
		video_error_win32();
	}
	wglMakeCurrent(g_dc, context);
	wglSwapIntervalEXT(1);
}

void video_context_update() {
	SwapBuffers(g_dc);
}