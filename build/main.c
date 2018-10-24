#include "util.h"
#include "input.h"

int main(int argc, char* argv[]) {
	if (argc < 3) {
		wheel_util_error("[USAGE] %s <input> <output>", argv[0]);
	}
	return 0;
}