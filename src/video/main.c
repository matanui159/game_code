#include "window.h"
#include "context.h"

int main() {
	video_window_init();
	video_context_init();
	video_window_show();
	for (;;) {
		video_context_update();
	}
	return 0;
}