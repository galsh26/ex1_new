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
CMAKE_COMMAND = /home/galsh26/cmake-3.17.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/galsh26/cmake-3.17.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Projects/yearB/clion projects/ex1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/ex1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex1.dir/flags.make

CMakeFiles/ex1.dir/main.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/main.cpp.o -c "/mnt/c/Projects/yearB/clion projects/ex1/main.cpp"

CMakeFiles/ex1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Projects/yearB/clion projects/ex1/main.cpp" > CMakeFiles/ex1.dir/main.cpp.i

CMakeFiles/ex1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Projects/yearB/clion projects/ex1/main.cpp" -o CMakeFiles/ex1.dir/main.cpp.s

CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o -c "/mnt/c/Projects/yearB/clion projects/ex1/anomaly_detection_util.cpp"

CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Projects/yearB/clion projects/ex1/anomaly_detection_util.cpp" > CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i

CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Projects/yearB/clion projects/ex1/anomaly_detection_util.cpp" -o CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s

# Object files for target ex1
ex1_OBJECTS = \
"CMakeFiles/ex1.dir/main.cpp.o" \
"CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o"

# External object files for target ex1
ex1_EXTERNAL_OBJECTS =

ex1: CMakeFiles/ex1.dir/main.cpp.o
ex1: CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o
ex1: CMakeFiles/ex1.dir/build.make
ex1: CMakeFiles/ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ex1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex1.dir/build: ex1

.PHONY : CMakeFiles/ex1.dir/build

CMakeFiles/ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex1.dir/clean

CMakeFiles/ex1.dir/depend:
	cd "/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Projects/yearB/clion projects/ex1" "/mnt/c/Projects/yearB/clion projects/ex1" "/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug" "/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug" "/mnt/c/Projects/yearB/clion projects/ex1/cmake-build-debug/CMakeFiles/ex1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ex1.dir/depend

