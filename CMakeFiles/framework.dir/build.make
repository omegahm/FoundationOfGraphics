# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = "/Applications/CMake 2.6-2.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.6-2.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.6-2.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ohm/projects/grafik/GraphicsProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ohm/projects/grafik

# Include any dependencies generated for this target.
include CMakeFiles/framework.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/framework.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/framework.dir/flags.make

CMakeFiles/framework.dir/src/main.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/src/main.o: GraphicsProject/src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ohm/projects/grafik/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/framework.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/src/main.o -c /Users/ohm/projects/grafik/GraphicsProject/src/main.cpp

CMakeFiles/framework.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ohm/projects/grafik/GraphicsProject/src/main.cpp > CMakeFiles/framework.dir/src/main.i

CMakeFiles/framework.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ohm/projects/grafik/GraphicsProject/src/main.cpp -o CMakeFiles/framework.dir/src/main.s

CMakeFiles/framework.dir/src/main.o.requires:
.PHONY : CMakeFiles/framework.dir/src/main.o.requires

CMakeFiles/framework.dir/src/main.o.provides: CMakeFiles/framework.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/src/main.o.provides.build
.PHONY : CMakeFiles/framework.dir/src/main.o.provides

CMakeFiles/framework.dir/src/main.o.provides.build: CMakeFiles/framework.dir/src/main.o
.PHONY : CMakeFiles/framework.dir/src/main.o.provides.build

# Object files for target framework
framework_OBJECTS = \
"CMakeFiles/framework.dir/src/main.o"

# External object files for target framework
framework_EXTERNAL_OBJECTS =

framework: CMakeFiles/framework.dir/src/main.o
framework: CMakeFiles/framework.dir/build.make
framework: CMakeFiles/framework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable framework"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/framework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/framework.dir/build: framework
.PHONY : CMakeFiles/framework.dir/build

CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/src/main.o.requires
.PHONY : CMakeFiles/framework.dir/requires

CMakeFiles/framework.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/framework.dir/cmake_clean.cmake
.PHONY : CMakeFiles/framework.dir/clean

CMakeFiles/framework.dir/depend:
	cd /Users/ohm/projects/grafik && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ohm/projects/grafik/GraphicsProject /Users/ohm/projects/grafik/GraphicsProject /Users/ohm/projects/grafik /Users/ohm/projects/grafik /Users/ohm/projects/grafik/CMakeFiles/framework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/framework.dir/depend

