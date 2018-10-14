#include "error.h"
#include "window.h"
#include <ogl.h>
#include <windows.h>
#include <stdlib.h>

void video_error(const char* error) {
	MessageBoxA(video_window_get(), error, NULL, MB_ICONERROR);
	exit(EXIT_FAILURE);
}

void video_error_win32() {
	unsigned flags
		= FORMAT_MESSAGE_ALLOCATE_BUFFER
		| FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS;
	
	char* buffer;
	FormatMessageA(flags, NULL, GetLastError(), 0, (char*)&buffer, 0, NULL);
	video_error(buffer);
}

void video_error_gl() {
	#define GL_CASE(error) \
		case error: \
			video_error(#error); \
			break;
	
	switch (glGetError()) {
		GL_CASE(GL_OUT_OF_MEMORY)
		GL_CASE(GL_INVALID_VALUE)
		GL_CASE(GL_INVALID_ENUM)
		GL_CASE(GL_INVALID_OPERATION)
		GL_CASE(GL_INVALID_FRAMEBUFFER_OPERATION)
	}
}