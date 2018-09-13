
ifndef EXERCISES_ROOT
$(error EXERCISES_ROOT not defined!)
endif

include $(EXERCISES_ROOT)/cpp_unittesting.mk

# Subject under test configuration
SUT_ROOT:=../generic_linked_list
SUT_BUILD_DIR:=$(SUT_ROOT)/$(BUILD)
SUT_OBJECT_FILES:=$(SUT_BUILD_DIR)/*.o
SUT_MAIN_OBJECT_FILE:=$(SUT_BUILD_DIR)/main.o

CFLAGS:=$(CFLAGS)  -I$(SUT_ROOT)

ADDITIONAL_OBJECTS:=$(filter-out $(SUT_MAIN_OBJECT_FILE) , $(wildcard $(SUT_OBJECT_FILES)))