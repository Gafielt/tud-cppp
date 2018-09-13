#
# This Makefile is the basis for unit testing project with UnitTest++
#

ifndef EXERCISES_ROOT
$(error EXERCISES_ROOT not defined!)
endif

include $(EXERCISES_ROOT)/cpp.mk

LFLAGS:=$(LFLAGS) -lUnitTest++