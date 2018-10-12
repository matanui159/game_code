#include "video/window.h"
#include "video/context.h"
#include <stdio.h>

int main() {
	video_window_init();
	video_context_init();
	for (;;) {
		video_context_update();
	}
}