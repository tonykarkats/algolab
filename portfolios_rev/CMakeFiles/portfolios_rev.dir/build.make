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
CMAKE_SOURCE_DIR = /home/algolab/problems/portfolios_rev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/problems/portfolios_rev

# Include any dependencies generated for this target.
include CMakeFiles/portfolios_rev.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/portfolios_rev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/portfolios_rev.dir/flags.make

CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o: CMakeFiles/portfolios_rev.dir/flags.make
CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o: portfolios_rev.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/algolab/problems/portfolios_rev/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o -c /home/algolab/problems/portfolios_rev/portfolios_rev.cpp

CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/algolab/problems/portfolios_rev/portfolios_rev.cpp > CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.i

CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/algolab/problems/portfolios_rev/portfolios_rev.cpp -o CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.s

CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.requires:
.PHONY : CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.requires

CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.provides: CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.requires
	$(MAKE) -f CMakeFiles/portfolios_rev.dir/build.make CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.provides.build
.PHONY : CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.provides

CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.provides.build: CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o

# Object files for target portfolios_rev
portfolios_rev_OBJECTS = \
"CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o"

# External object files for target portfolios_rev
portfolios_rev_EXTERNAL_OBJECTS =

portfolios_rev: CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o
portfolios_rev: CMakeFiles/portfolios_rev.dir/build.make
portfolios_rev: /usr/lib/i386-linux-gnu/libmpfr.so
portfolios_rev: /usr/lib/i386-linux-gnu/libgmp.so
portfolios_rev: /usr/lib/libCGAL_Core.so
portfolios_rev: /usr/lib/libCGAL.so
portfolios_rev: /usr/lib/i386-linux-gnu/libboost_thread.so
portfolios_rev: /usr/lib/i386-linux-gnu/libboost_system.so
portfolios_rev: /usr/lib/i386-linux-gnu/libpthread.so
portfolios_rev: /usr/lib/libCGAL_Core.so
portfolios_rev: /usr/lib/libCGAL.so
portfolios_rev: /usr/lib/i386-linux-gnu/libboost_thread.so
portfolios_rev: /usr/lib/i386-linux-gnu/libboost_system.so
portfolios_rev: /usr/lib/i386-linux-gnu/libpthread.so
portfolios_rev: CMakeFiles/portfolios_rev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable portfolios_rev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/portfolios_rev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/portfolios_rev.dir/build: portfolios_rev
.PHONY : CMakeFiles/portfolios_rev.dir/build

CMakeFiles/portfolios_rev.dir/requires: CMakeFiles/portfolios_rev.dir/portfolios_rev.cpp.o.requires
.PHONY : CMakeFiles/portfolios_rev.dir/requires

CMakeFiles/portfolios_rev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/portfolios_rev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/portfolios_rev.dir/clean

CMakeFiles/portfolios_rev.dir/depend:
	cd /home/algolab/problems/portfolios_rev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/problems/portfolios_rev /home/algolab/problems/portfolios_rev /home/algolab/problems/portfolios_rev /home/algolab/problems/portfolios_rev /home/algolab/problems/portfolios_rev/CMakeFiles/portfolios_rev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/portfolios_rev.dir/depend
