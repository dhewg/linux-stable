KERNEL_DIR:=$(shell readlink -f $(srctree))

MODULES_RA_HWNAT_V3_DIR:=/nonexistant
export GLOBAL_INC_DIR=$(KERNEL_DIR)/vendor/global_inc

include $(srctree)/vendor/UNION_EN7516_7915D_demo.profile
include $(srctree)/vendor/rule.mak

vendor_check:
	@echo $(TC_CFLAGS) | tr ' ' '\n'
	@echo $(srctree)=$(KERNEL_DIR)
