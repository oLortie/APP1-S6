# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build

# Include any dependencies generated for this target.
include CMakeFiles/stb_image.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stb_image.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stb_image.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stb_image.dir/flags.make

CMakeFiles/stb_image.dir/src/stb_image.c.o: CMakeFiles/stb_image.dir/flags.make
CMakeFiles/stb_image.dir/src/stb_image.c.o: ../src/stb_image.c
CMakeFiles/stb_image.dir/src/stb_image.c.o: CMakeFiles/stb_image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/stb_image.dir/src/stb_image.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/stb_image.dir/src/stb_image.c.o -MF CMakeFiles/stb_image.dir/src/stb_image.c.o.d -o CMakeFiles/stb_image.dir/src/stb_image.c.o -c /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/src/stb_image.c

CMakeFiles/stb_image.dir/src/stb_image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/stb_image.dir/src/stb_image.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/src/stb_image.c > CMakeFiles/stb_image.dir/src/stb_image.c.i

CMakeFiles/stb_image.dir/src/stb_image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/stb_image.dir/src/stb_image.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/src/stb_image.c -o CMakeFiles/stb_image.dir/src/stb_image.c.s

# Object files for target stb_image
stb_image_OBJECTS = \
"CMakeFiles/stb_image.dir/src/stb_image.c.o"

# External object files for target stb_image
stb_image_EXTERNAL_OBJECTS =

libstb_image.a: CMakeFiles/stb_image.dir/src/stb_image.c.o
libstb_image.a: CMakeFiles/stb_image.dir/build.make
libstb_image.a: CMakeFiles/stb_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libstb_image.a"
	$(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stb_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stb_image.dir/build: libstb_image.a
.PHONY : CMakeFiles/stb_image.dir/build

CMakeFiles/stb_image.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stb_image.dir/clean

CMakeFiles/stb_image.dir/depend:
	cd /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22 /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22 /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build /home/paul/Documents/GitHub/APP1-S6/GIF643-Proto-E22/build/CMakeFiles/stb_image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stb_image.dir/depend

