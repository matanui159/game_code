#include "util.h"
#include "input.h"
#include <au/test.h>
#include <au/log.h>

int main(int argc, char* argv[]) {
	au_log_init(AU_LOG_DBUG, NULL, NULL);
	au_test_run();

	if (argc < 3) {
		au_log(AU_LOG_FAIL, "Usage: build <input> <output>");
	}
	return 0;
}