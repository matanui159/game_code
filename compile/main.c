#include "input.h"
#include "build.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void main_help() {
	puts("Usage:");
	puts("  compile build <output> <file>");
	puts("  compile link  <output> <files...>");
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		main_help();
	}

	if (strcmp(argv[1], "build") == 0) {
		wheel_input_init(argv[3]);
		wheel_build(argv[2]);
		return 0;
	} else {
		main_help();
	}
}