#include "player.h"
#include "rect.h"
#include "lerp.h"
#include "../input.h"

static game_rect_t g_rect;
static float g_vy;
static bool g_jump;
static bool g_ground;

void game_player_init() {
	g_rect.color = 0xFFFFFFFF;
	game_lerp_init(&g_rect.x, 0);
	game_lerp_init(&g_rect.y, 0);
	game_lerp_init(&g_rect.width, 2);
	game_lerp_init(&g_rect.height, 1);
	game_lerp_init(&g_rect.angle, 1);
}

void game_player_update() {
	game_rect_update(&g_rect);
	
	if (input_keyboard_down('A')) {
		g_rect.x -= 1;
	}
	if (input_keyboard_down('D')) {
		g_rect.x += 1;
	}
	g_rect.angle += 2;

	g_vy -= 0.5;
	bool jump = input_keyboard_down('W');
	if (jump && !g_jump) {
		if (g_ground) {
			g_vy = 2;
		}
	}
	g_jump = jump;

	g_rect.y += g_vy;
	if (g_rect.y < 0.5) {
		g_rect.y = 0.5;
		g_vy = 0;
		g_ground = true;
	} else {
		g_ground = false;
	}
}

void game_player_draw(video_matrix_t matrix, float delta) {
	game_rect_draw(&g_rect, matrix, delta);
}