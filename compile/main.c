#include "input.h"
#include "build.h"
#include <stdio.h>
#include <string.h>

static void main_help() {
	wheel_input_error("Invalid usage\n"
		" - compile build <input> <output>\n"
		" - compile link   <map>  <output>"
	);
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		main_help();
	}

	if (strcmp(argv[1], "build") == 0) {
		wheel_input_init(argv[2]);
		wheel_build(argv[3]);
	} else {
		main_help();
	}
	return 0;
}