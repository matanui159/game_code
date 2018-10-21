ifndef config
	config = debug
endif

ifeq ($(verbose),y)
	TUP_FLAGS += --verbose
endif

all:
	echo CONFIG = $(config) > tup/config.tup
	tup $(TUP_FLAGS)

clean:
	git clean -fdX

.PHONY: all clean
.SILENT: all clean