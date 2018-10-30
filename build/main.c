#include <au/log.h>
#include <au/cmdline.h>
#include <stddef.h>

int main(int argc, char* argv[]) {
	au_cmdline_t cmdline;
	au_cmdline_create(&cmdline, argc, argv);
	while (au_cmdline_next(&cmdline) != NULL);

	au_log_dbug("MAIN", "Debug message");
	au_log_info("MAIN", "Info message");
	au_log_warn("MAIN", "Warning message");
	au_log_fail("MAIN", "Failure message");
	return 0;
}