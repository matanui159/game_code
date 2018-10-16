#include "player.h"
#include <time.h>

#define MAIN_CLOCK (CLOCKS_PER_SEC / 20)

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

	clock_t start = clock();
	game_player_init();
	for (;;) {
		clock_t current = clock();
		if (current - start >= MAIN_CLOCK) {
			game_player_update();

			start += MAIN_CLOCK;
			if (current - start >= MAIN_CLOCK) {
				start = current;
			}
		}
		float delta = (float)(current - start) / MAIN_CLOCK;

		video_matrix_t matrix;
		video_shader_use(shader);
		video_matrix_identity(&matrix);
		video_matrix_translate(&matrix, -1, -1);
		video_matrix_scale(&matrix, 2, 2);
		video_rect_draw(&matrix, 0x000000FF);
		video_matrix_scale(&matrix, 1.0 / 16, 1.0 / 9);

		game_player_draw(matrix, delta);

		video_update();
	}
}