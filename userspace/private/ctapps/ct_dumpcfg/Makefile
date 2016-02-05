EXE = ct_dumpcfg
dynamic: generic_exe_install

clean:
	rm -f ct_dumpcfg


ct_dumpcfg:
	cp ct_dumpcfg_$(PROFILE)_save ct_dumpcfg

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
