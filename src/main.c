#include "video/video.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RAND(max) (((float)rand() / RAND_MAX) * (max))

int main() {
	video_init();
	unsigned shader = video_shader_create(VIDEO_SHADER_CODE(
		in vec4 color;
		out vec4 fcolor;
		void main() {
			fcolor = color;
		}
	));
	video_window_show();

	for (;;) {
		video_matrix_t matrix;
		video_shader_use(shader);
		video_matrix_identity(&matrix);
		video_matrix_translate(&matrix, -1, -1);
		video_matrix_scale(&matrix, 2, 2);
		video_rect_draw(&matrix, 0xFF000000);
		video_update();
	}
}