#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_
#include "../video.h"

void game_player_init();
void game_player_update();
void game_player_draw(video_matrix_t matrix, float delta);

#endif