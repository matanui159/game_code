#include "util.h"
#include "input.h"
#include <au/test.h>
#include <au/log.h>

int main(int argc, char* argv[]) {
	au_log_init(AU_LOG_DBUG, NULL, NULL);
	au_test_run();
	if (argc < 3) {
		AU_LOG(AU_LOG_FAIL, "Invalid usage");
	}
	return 0;
}