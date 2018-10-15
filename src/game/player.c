#include "player.h"
#include "lerp.h"
#include "../input.h"

static game_lerp_t g_x;
static game_lerp_t g_y;
static float g_vy;
static bool g_jump;
static bool g_ground;

void game_player_init() {
	game_lerp_init(&g_x, 0);
	game_lerp_init(&g_y, 0);
	g_vy = 0;
	g_jump = false;
}

void game_player_update() {
	game_lerp_update(&g_x);
	game_lerp_update(&g_y);
	
	if (input_keyboard_down('A')) {
		g_x.v -= 1;
	}
	if (input_keyboard_down('D')) {
		g_x.v += 1;
	}

	g_vy -= 0.5;
	bool jump = input_keyboard_down('W');
	if (jump && !g_jump) {
		if (g_ground) {
			g_vy = 2;
		}
	}
	g_jump = jump;

	g_y.v += g_vy;
	if (g_y.v < 0) {
		g_y.v = 0;
		g_vy = 0;
		g_ground = true;
	} else {
		g_ground = false;
	}
}

void game_player_draw(video_matrix_t matrix, float delta) {
	video_matrix_translate(&matrix,
		game_lerp_get(&g_x, delta),
		game_lerp_get(&g_y, delta)
	);
	video_rect_draw(&matrix, 0xFFFFFFFF);
}