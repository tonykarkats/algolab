# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/algolab/problems/proximity/bistro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/problems/proximity/bistro

# Include any dependencies generated for this target.
include CMakeFiles/bistro.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bistro.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bistro.dir/flags.make

CMakeFiles/bistro.dir/bistro.cpp.o: CMakeFiles/bistro.dir/flags.make
CMakeFiles/bistro.dir/bistro.cpp.o: bistro.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/algolab/problems/proximity/bistro/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bistro.dir/bistro.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bistro.dir/bistro.cpp.o -c /home/algolab/problems/proximity/bistro/bistro.cpp

CMakeFiles/bistro.dir/bistro.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bistro.dir/bistro.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/algolab/problems/proximity/bistro/bistro.cpp > CMakeFiles/bistro.dir/bistro.cpp.i

CMakeFiles/bistro.dir/bistro.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bistro.dir/bistro.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/algolab/problems/proximity/bistro/bistro.cpp -o CMakeFiles/bistro.dir/bistro.cpp.s

CMakeFiles/bistro.dir/bistro.cpp.o.requires:
.PHONY : CMakeFiles/bistro.dir/bistro.cpp.o.requires

CMakeFiles/bistro.dir/bistro.cpp.o.provides: CMakeFiles/bistro.dir/bistro.cpp.o.requires
	$(MAKE) -f CMakeFiles/bistro.dir/build.make CMakeFiles/bistro.dir/bistro.cpp.o.provides.build
.PHONY : CMakeFiles/bistro.dir/bistro.cpp.o.provides

CMakeFiles/bistro.dir/bistro.cpp.o.provides.build: CMakeFiles/bistro.dir/bistro.cpp.o

# Object files for target bistro
bistro_OBJECTS = \
"CMakeFiles/bistro.dir/bistro.cpp.o"

# External object files for target bistro
bistro_EXTERNAL_OBJECTS =

bistro: CMakeFiles/bistro.dir/bistro.cpp.o
bistro: CMakeFiles/bistro.dir/build.make
bistro: /usr/lib/i386-linux-gnu/libmpfr.so
bistro: /usr/lib/i386-linux-gnu/libgmp.so
bistro: /usr/lib/libCGAL_Core.so
bistro: /usr/lib/libCGAL.so
bistro: /usr/lib/i386-linux-gnu/libboost_thread.so
bistro: /usr/lib/i386-linux-gnu/libboost_system.so
bistro: /usr/lib/i386-linux-gnu/libpthread.so
bistro: /usr/lib/libCGAL_Core.so
bistro: /usr/lib/libCGAL.so
bistro: /usr/lib/i386-linux-gnu/libboost_thread.so
bistro: /usr/lib/i386-linux-gnu/libboost_system.so
bistro: /usr/lib/i386-linux-gnu/libpthread.so
bistro: CMakeFiles/bistro.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bistro"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bistro.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bistro.dir/build: bistro
.PHONY : CMakeFiles/bistro.dir/build

CMakeFiles/bistro.dir/requires: CMakeFiles/bistro.dir/bistro.cpp.o.requires
.PHONY : CMakeFiles/bistro.dir/requires

CMakeFiles/bistro.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bistro.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bistro.dir/clean

CMakeFiles/bistro.dir/depend:
	cd /home/algolab/problems/proximity/bistro && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/problems/proximity/bistro /home/algolab/problems/proximity/bistro /home/algolab/problems/proximity/bistro /home/algolab/problems/proximity/bistro /home/algolab/problems/proximity/bistro/CMakeFiles/bistro.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bistro.dir/depend

