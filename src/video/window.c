#include "window.h"
#include "error.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define WINDOW_CLASS "WINDOW_CLASS"

static volatile HWND g_window;

static LONG_PTR CALLBACK window_proc(HWND wnd, unsigned msg, uintptr_t arg1, LONG_PTR arg2) {
	switch (msg) {
		case WM_SHOWWINDOW:
			SetFocus(wnd);
			break;
		case WM_DESTROY:
			exit(EXIT_SUCCESS);
			break;
	}

	return DefWindowProcA(wnd, msg, arg1, arg2);
}

void video_window_init() {
	HINSTANCE instance = GetModuleHandleA(NULL);

	WNDCLASSA wndclass = {
		.hInstance = instance,
		.lpszClassName = WINDOW_CLASS,
		.style = CS_OWNDC,
		.lpfnWndProc = window_proc,
		.hCursor = LoadCursorA(NULL, (char*)IDC_ARROW)
	};
	if (RegisterClassA(&wndclass) == 0) {
		video_error_win32();
	}

	unsigned style = WS_POPUP;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	#ifndef NDEBUG
		style = WS_CAPTION | WS_SYSMENU;
		width /= 2;
		height /= 2;
	#endif

	g_window = CreateWindowExA(
		0,
		WINDOW_CLASS,
		"Code?",
		style,
		0, 0,
		width, height,
		NULL,
		NULL,
		instance,
		NULL
	);
	if (g_window == NULL) {
		video_error_win32();
	}
}

void video_window_show() {
	ShowWindow(g_window, SW_SHOW);
}

void video_window_update() {
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		DispatchMessageA(&msg);
		TranslateMessage(&msg);
	}	
}

HWND video_window_get() {
	return g_window;
}