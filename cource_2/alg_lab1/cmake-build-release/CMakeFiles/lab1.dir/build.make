# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/tgpsun/Prog/clion-2020.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/tgpsun/Prog/clion-2020.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tgpsun/CLionProjects/lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tgpsun/CLionProjects/lab1/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/lab1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1.dir/flags.make

CMakeFiles/lab1.dir/main.c.o: CMakeFiles/lab1.dir/flags.make
CMakeFiles/lab1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tgpsun/CLionProjects/lab1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab1.dir/main.c.o   -c /home/tgpsun/CLionProjects/lab1/main.c

CMakeFiles/lab1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tgpsun/CLionProjects/lab1/main.c > CMakeFiles/lab1.dir/main.c.i

CMakeFiles/lab1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tgpsun/CLionProjects/lab1/main.c -o CMakeFiles/lab1.dir/main.c.s

# Object files for target lab1
lab1_OBJECTS = \
"CMakeFiles/lab1.dir/main.c.o"

# External object files for target lab1
lab1_EXTERNAL_OBJECTS =

lab1: CMakeFiles/lab1.dir/main.c.o
lab1: CMakeFiles/lab1.dir/build.make
lab1: CMakeFiles/lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tgpsun/CLionProjects/lab1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lab1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1.dir/build: lab1

.PHONY : CMakeFiles/lab1.dir/build

CMakeFiles/lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab1.dir/clean

CMakeFiles/lab1.dir/depend:
	cd /home/tgpsun/CLionProjects/lab1/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tgpsun/CLionProjects/lab1 /home/tgpsun/CLionProjects/lab1 /home/tgpsun/CLionProjects/lab1/cmake-build-release /home/tgpsun/CLionProjects/lab1/cmake-build-release /home/tgpsun/CLionProjects/lab1/cmake-build-release/CMakeFiles/lab1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab1.dir/depend

