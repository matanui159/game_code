#ifndef GAME_RECT_H_
#define GAME_RECT_H_
#include "../video.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct game_rect_t {
	uint32_t color;
	float x;
	float prev_x;
	float y;
	float prev_y;
	float width;
	float prev_width;
	float height;
	float prev_height;
	float angle;
	float prev_angle;
} game_rect_t;

void game_rect_update(game_rect_t* rect);
void game_rect_draw(game_rect_t* rect, video_matrix_t matrix, float delta);
bool game_rect_collide(game_rect_t* rect, game_rect_t* other);

#endif