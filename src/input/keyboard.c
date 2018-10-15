#include "keyboard.h"

bool input_keyboard_down(int key) {
	return GetAsyncKeyState(key) >> 15;
}

