#include "util.h"
#include "input.h"
#include <au/test.h>
#include <au/log.h>

#ifndef WHEEL_LOG_LEVEL
	#define WHEEL_LOG_LEVEL AU_LOG_DBUG
#endif

int main(int argc, char* argv[]) {
	au_log_init(WHEEL_LOG_LEVEL, au_log_default);
	au_test_run();

	if (argc < 3) {
		au_log(AU_LOG_FAIL, "USAGE", "build <input> <output>");
	}
	return 0;
}