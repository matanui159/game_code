#include "player.h"
#include "lerp.h"

static game_lerp_t g_x;
static game_lerp_t g_y;

void game_player_init() {
	game_lerp_init(&g_x, 0);
	game_lerp_init(&g_y, 0);
}

void game_player_update() {
	game_lerp_update(&g_x);
	game_lerp_update(&g_y);
	g_x.v += 0.1;
}

void game_player_draw(video_matrix_t matrix, float delta) {
	video_matrix_translate(&matrix,
		game_lerp_get(&g_x, delta),
		game_lerp_get(&g_y, delta)
	);
	video_rect_draw(&matrix, 0xFFFFFFFF);
}