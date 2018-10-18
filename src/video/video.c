#include "../video.h"

void video_init() {
	video_window_init();
	video_context_init();
	video_shader_init();
	video_varray_init();
	video_text_init();
	video_window_show();
}

void video_update() {
	video_text_update();
	video_context_update();
	video_window_update();
}