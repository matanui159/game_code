export config ?= debug
ifeq ($(verbose),y)
	export TUP_FLAGS += --verbose
endif

all: setup
	tup $(TUP_FLAGS)
setup:
	echo CONFIG = $(config) > tup/config.tup
	cd libau; make setup
clean:
	git clean -fdX
	cd libau; make clean
.PHONY: all setup clean