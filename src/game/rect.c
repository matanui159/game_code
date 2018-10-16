#include "rect.h"

void game_rect_update(game_rect_t* rect) {
	game_lerp_update(&rect->x);
	game_lerp_update(&rect->y);
	game_lerp_update(&rect->width);
	game_lerp_update(&rect->height);
	game_lerp_update(&rect->angle);
}

void game_rect_draw(game_rect_t* rect, video_matrix_t matrix, float delta) {
	float width = game_lerp_get(&rect->width, delta);
	float height = game_lerp_get(&rect->height, delta);

	video_matrix_translate(&matrix,
		game_lerp_get(&rect->x, delta) + width / 2,
		game_lerp_get(&rect->y, delta) + height / 2
	);
	video_matrix_rotate(&matrix, game_lerp_get(&rect->angle, delta));
	video_matrix_scale(&matrix, width, height);
	video_matrix_translate(&matrix, -0.5, -0.5);
	video_rect_draw(&matrix, rect->color);
}