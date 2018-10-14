#include "context.h"
#include "error.h"
#include "window.h"
#include <ogl.h>
#include <stdio.h>

static HDC g_dc;

#ifndef NDEBUG
	static void APIENTRY context_debug(unsigned source, unsigned type, unsigned id, unsigned level, int size, const char* msg, const void* data) {
		// unused
		((void)source);
		((void)type);
		((void)id);
		((void)size);
		((void)data);

		puts(msg);
		if (level == GL_DEBUG_SEVERITY_HIGH) {
			video_error("OpenGL error");
		}
	}
#endif

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
		#ifndef NDEBUG
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		#endif
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

	#ifndef NDEBUG
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(context_debug, NULL);
	#endif
}

void video_context_update() {
	SwapBuffers(g_dc);
}