# $<	the first dependency
# $@	name of the target
# $+	list of all dependencies
# $^	list of all dependencies (unique elements)

# delete the default suffixes (disable implicit rules)
.SUFFIXES:
# PHONY targets (targets that do not represent a file)
.PHONY: clean all doxygen clean_doxygen clean_all run

# compiler options
CC		:= g++
# -g			add debugging symbols to the binary executable file
# -O0			deactivate optimizations
# -Wall			show reasonable warnings
# -Wextra		show more warnings
# -MMD -MP		generate dependencies to header files so that make recognizes changes to header files,
#				which otherwise do not appear explicitly in any rule
# -std=c++11	enable C++11
CFLAGS := -g -O0 -Wall -Wextra -MMD -MP -std=c++11

# Linker flags
# -lMyLibrary     for additional library libMyLibrary.a
# -LMyPath         for additional library search path
LFLAGS :=

# build directory (to store the executable the .o and .d files)
BUILD	:= build

# source code
BINARY	:= $(BUILD)/main.exe
SOURCES	:= $(wildcard *.cpp)
OBJECTS	:= $(patsubst %.cpp, $(BUILD)/%.o, $(SOURCES))
DEPEND	:= $(patsubst %.cpp, $(BUILD)/%.d, $(SOURCES))

# With this constant, you can provide a space-separated list of additional existing object files
ADDITIONAL_OBJECTS:=

# default target (create the binary executable file)
all: $(BINARY)

run: $(BINARY)
	@echo "Running $(BINARY)..."
	@$(BINARY)

# include dependencies to detect header file changes (this creates new targets!)
-include $(DEPEND)

# create the binary executable file
$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $^  $(ADDITIONAL_OBJECTS) $(LFLAGS)

# create an object file from a source file
$(BUILD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

doxygen:
	if [ ! -e Doxyfile ]; then ( doxygen -g ) fi
	doxygen

clean_doxygen:
	rm -rf html latex Doxyfile

clean_all: clean clean_doxygen
