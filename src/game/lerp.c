#include "lerp.h"

void game_lerp_init(game_lerp_t* lerp, float value) {
	lerp->v = value;
	lerp->prev = value;
}

void game_lerp_update(game_lerp_t* lerp) {
	lerp->prev = lerp->v;
}

float game_lerp_get(game_lerp_t* lerp, float delta) {
	return (lerp->v - lerp->prev) * delta + lerp->prev;
}