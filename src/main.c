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
	video_matrix_t matrix;

	clock_t start = clock();
	int frames = 0;

	for (;;) {
		++frames;
		if (clock() - start >= CLOCKS_PER_SEC) {
			printf("FPS: %i\n", frames);
			start = clock();
			frames = 0;
		}

		video_shader_use(shader);

		video_matrix_identity(&matrix);
		video_matrix_translate(&matrix, -1, -1);
		video_matrix_scale(&matrix, 2, 2);
		video_rect_draw(&matrix, 0x000000FF);

		video_matrix_scale(&matrix, 1.0 / 16, 1.0 / 9);
		for (int i = 0; i < 10000; ++i) {
			video_matrix_t copy = matrix;
			video_matrix_translate(&copy, RAND(16), RAND(9));
			video_matrix_rotate(&copy, RAND(6));
			video_rect_draw(&copy, (uint32_t)RAND(0xFFFFFFFF));
		}
		video_update();
	}
}