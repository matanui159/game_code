#include "window.h"
#include "error.h"
#include <stdlib.h>
#include <stdbool.h>

#define WINDOW_CLASS L"game_class"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static volatile HWND g_window = NULL;

static LRESULT CALLBACK window_proc(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm) {
	switch (msg) {
		case WM_SHOWWINDOW:
			SetFocus(wnd);
			break;
		case WM_DESTROY:
			exit(EXIT_SUCCESS);
			break;
	}

	return DefWindowProcW(wnd, msg, wpm, lpm);
}

static DWORD CALLBACK window_thread(void* data) {
	HANDLE event = data;
	HMODULE instance = GetModuleHandleW(NULL);

	WNDCLASSW wndclass = {
		.hInstance = instance,
		.lpszClassName = WINDOW_CLASS,
		.style = CS_OWNDC,
		.lpfnWndProc = window_proc,
		.hCursor = LoadCursorW(NULL, (WCHAR*)IDC_ARROW)
	};
	if (RegisterClassW(&wndclass) == 0) {
		video_error_win32();
	}

	int x = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;
	RECT rect = {
		.left = x,
		.right = x + WINDOW_WIDTH,
		.top = y,
		.bottom = y + WINDOW_HEIGHT
	};
	unsigned style = WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rect, style, false);

	g_window = CreateWindowW(
		WINDOW_CLASS,
		L"Yet Another Platformer",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		instance,
		NULL
	);
	if (g_window == NULL) {
		video_error_win32();
	}

	SetEvent(event);
	for (;;) {
		MSG msg;
		GetMessageW(&msg, NULL, 0, 0);
		DispatchMessageW(&msg);
	}
	return 0;
}

void video_window_init() {
	HANDLE event = CreateEventW(NULL, true, false, NULL);
	if (event == NULL) {
		video_error_win32();
	}

	if (CreateThread(NULL, 0, window_thread, event, 0, NULL) == NULL) {
		video_error_win32();
	}
	WaitForSingleObject(event, INFINITE);
}

HWND video_window_get() {
	return g_window;
}