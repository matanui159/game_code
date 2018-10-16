#ifndef GAME_LERP_H_
#define GAME_LERP_H_

void game_lerp_init(float* lerp, float value);
void game_lerp_update(float* lerp);
float game_lerp_get(float* lerp, float delta);

#endif