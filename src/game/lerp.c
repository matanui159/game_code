#include "lerp.h"

void game_lerp_init(float* lerp, float value) {
	lerp[0] = value;
	lerp[1] = value;
}

void game_lerp_update(float* lerp) {
	lerp[1] = lerp[0];
}

float game_lerp_get(float* lerp, float delta) {
	return lerp[0] * delta + lerp[1] * (1 - delta);
}