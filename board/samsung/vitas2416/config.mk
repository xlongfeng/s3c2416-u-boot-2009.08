#
# (C) Copyright 2015
# xlongfeng <xlongfeng@126.com>
#
# VITAS2416 board with S3C2416 (ARM926ejs) cpu
#

#
# VITAS2416 has 1 bank of 64 MB DRAM
#
# 3000'0000 to 3400'0000
#
# Linux-Kernel is expected to be at 3000'8000, entry 3000'8000
# optionally with a ramdisk at 3080'0000
#
# we load ourself to 33C0'0000
#
# download area is 3300'0000
#


TEXT_BASE = 0x33C00000

LDSCRIPT := $(SRCTREE)/board/$(BOARDDIR)/u-boot.lds
