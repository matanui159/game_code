#include "util.h"
#include "input.h"
#include <au/test.h>
#include <au/log.h>

int main(int argc, char* argv[]) {
	#ifdef NDEBUG
		au_log_init(AU_LOG_WARN, au_log_default);
	#else
		au_log_init(AU_LOG_DBUG, au_log_default);
	#endif
	au_test_run();

	if (argc < 3) {
		au_log(AU_LOG_FAIL, "USAGE", "build <input> <output>");
	}
	return 0;
}