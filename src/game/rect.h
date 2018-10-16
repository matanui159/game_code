#ifndef GAME_RECT_H_
#define GAME_RECT_H_
#include "lerp.h"
#include "../video.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct game_rect_t {
	uint32_t color;
	game_lerp_t x;
	game_lerp_t y;
	game_lerp_t width;
	game_lerp_t height;
	game_lerp_t angle;
} game_rect_t;

void game_rect_update(game_rect_t* rect);
void game_rect_draw(game_rect_t* rect, video_matrix_t matrix, float delta);
bool game_rect_collide(game_rect_t* rect, game_rect_t* other);

#endif