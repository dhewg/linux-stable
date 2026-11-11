KERNEL_DIR:=$(PWD)

MODULES_RA_HWNAT_V3_DIR:=/nonexistant
export GLOBAL_INC_DIR=$(KERNEL_DIR)/vendor/global_inc

include $(KERNEL_DIR)/vendor/UNION_EN7516_7915D_demo.profile
include $(KERNEL_DIR)/vendor/rule.mak

vendor_check:
	@echo $(TC_CFLAGS) | tr ' ' '\n'
