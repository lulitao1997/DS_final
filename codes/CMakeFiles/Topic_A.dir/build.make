# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/lulitao/.Clion/clion-2016.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lulitao/.Clion/clion-2016.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A"

# Include any dependencies generated for this target.
include CMakeFiles/Topic_A.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Topic_A.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Topic_A.dir/flags.make

CMakeFiles/Topic_A.dir/Topic_A.cpp.o: CMakeFiles/Topic_A.dir/flags.make
CMakeFiles/Topic_A.dir/Topic_A.cpp.o: Topic_A.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Topic_A.dir/Topic_A.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Topic_A.dir/Topic_A.cpp.o -c "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A/Topic_A.cpp"

CMakeFiles/Topic_A.dir/Topic_A.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Topic_A.dir/Topic_A.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A/Topic_A.cpp" > CMakeFiles/Topic_A.dir/Topic_A.cpp.i

CMakeFiles/Topic_A.dir/Topic_A.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Topic_A.dir/Topic_A.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A/Topic_A.cpp" -o CMakeFiles/Topic_A.dir/Topic_A.cpp.s

CMakeFiles/Topic_A.dir/Topic_A.cpp.o.requires:

.PHONY : CMakeFiles/Topic_A.dir/Topic_A.cpp.o.requires

CMakeFiles/Topic_A.dir/Topic_A.cpp.o.provides: CMakeFiles/Topic_A.dir/Topic_A.cpp.o.requires
	$(MAKE) -f CMakeFiles/Topic_A.dir/build.make CMakeFiles/Topic_A.dir/Topic_A.cpp.o.provides.build
.PHONY : CMakeFiles/Topic_A.dir/Topic_A.cpp.o.provides

CMakeFiles/Topic_A.dir/Topic_A.cpp.o.provides.build: CMakeFiles/Topic_A.dir/Topic_A.cpp.o


# Object files for target Topic_A
Topic_A_OBJECTS = \
"CMakeFiles/Topic_A.dir/Topic_A.cpp.o"

# External object files for target Topic_A
Topic_A_EXTERNAL_OBJECTS =

Topic_A: CMakeFiles/Topic_A.dir/Topic_A.cpp.o
Topic_A: CMakeFiles/Topic_A.dir/build.make
Topic_A: CMakeFiles/Topic_A.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Topic_A"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Topic_A.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Topic_A.dir/build: Topic_A

.PHONY : CMakeFiles/Topic_A.dir/build

CMakeFiles/Topic_A.dir/requires: CMakeFiles/Topic_A.dir/Topic_A.cpp.o.requires

.PHONY : CMakeFiles/Topic_A.dir/requires

CMakeFiles/Topic_A.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Topic_A.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Topic_A.dir/clean

CMakeFiles/Topic_A.dir/depend:
	cd "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A" "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A" "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A" "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A" "/home/lulitao/文档/Data Structure Homework/Final Project/Topic_A/CMakeFiles/Topic_A.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Topic_A.dir/depend
