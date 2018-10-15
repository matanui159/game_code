#ifndef GAME_LERP_H_
#define GAME_LERP_H_

typedef struct game_lerp_t {
	float v;
	float prev;
} game_lerp_t;

void game_lerp_init(game_lerp_t* lerp, float value);
void game_lerp_update(game_lerp_t* lerp);
float game_lerp_get(game_lerp_t* lerp, float delta);

#endif