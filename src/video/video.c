#include "../video.h"

void video_init() {
	video_window_init();
	video_context_init();
	video_shader_init();
	video_rect_init();
}

void video_update() {
	video_rect_flush();
	video_context_update();
}