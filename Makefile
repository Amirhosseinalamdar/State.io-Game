# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amirhossein/Desktop/state.io

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amirhossein/Desktop/state.io

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/amirhossein/Desktop/state.io/CMakeFiles /home/amirhossein/Desktop/state.io/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/amirhossein/Desktop/state.io/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named state

# Build rule for target.
state: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 state
.PHONY : state

# fast build rule for target.
state/fast:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/build
.PHONY : state/fast

src/first_menu.o: src/first_menu.c.o

.PHONY : src/first_menu.o

# target to build an object file
src/first_menu.c.o:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/first_menu.c.o
.PHONY : src/first_menu.c.o

src/first_menu.i: src/first_menu.c.i

.PHONY : src/first_menu.i

# target to preprocess a source file
src/first_menu.c.i:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/first_menu.c.i
.PHONY : src/first_menu.c.i

src/first_menu.s: src/first_menu.c.s

.PHONY : src/first_menu.s

# target to generate assembly for a file
src/first_menu.c.s:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/first_menu.c.s
.PHONY : src/first_menu.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/main.c.s
.PHONY : src/main.c.s

src/main_menu.o: src/main_menu.c.o

.PHONY : src/main_menu.o

# target to build an object file
src/main_menu.c.o:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/main_menu.c.o
.PHONY : src/main_menu.c.o

src/main_menu.i: src/main_menu.c.i

.PHONY : src/main_menu.i

# target to preprocess a source file
src/main_menu.c.i:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/main_menu.c.i
.PHONY : src/main_menu.c.i

src/main_menu.s: src/main_menu.c.s

.PHONY : src/main_menu.s

# target to generate assembly for a file
src/main_menu.c.s:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/main_menu.c.s
.PHONY : src/main_menu.c.s

src/map.o: src/map.c.o

.PHONY : src/map.o

# target to build an object file
src/map.c.o:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/map.c.o
.PHONY : src/map.c.o

src/map.i: src/map.c.i

.PHONY : src/map.i

# target to preprocess a source file
src/map.c.i:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/map.c.i
.PHONY : src/map.c.i

src/map.s: src/map.c.s

.PHONY : src/map.s

# target to generate assembly for a file
src/map.c.s:
	$(MAKE) -f CMakeFiles/state.dir/build.make CMakeFiles/state.dir/src/map.c.s
.PHONY : src/map.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... state"
	@echo "... src/first_menu.o"
	@echo "... src/first_menu.i"
	@echo "... src/first_menu.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/main_menu.o"
	@echo "... src/main_menu.i"
	@echo "... src/main_menu.s"
	@echo "... src/map.o"
	@echo "... src/map.i"
	@echo "... src/map.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

