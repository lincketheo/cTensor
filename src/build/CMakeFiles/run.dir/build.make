# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/theo/Documents/projects/math/tensorFlow/cTensor/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/theo/Documents/projects/math/tensorFlow/cTensor/src/build

# Include any dependencies generated for this target.
include CMakeFiles/run.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run.dir/flags.make

CMakeFiles/run.dir/main.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/theo/Documents/projects/math/tensorFlow/cTensor/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/main.cpp.o -c /home/theo/Documents/projects/math/tensorFlow/cTensor/src/main.cpp

CMakeFiles/run.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theo/Documents/projects/math/tensorFlow/cTensor/src/main.cpp > CMakeFiles/run.dir/main.cpp.i

CMakeFiles/run.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theo/Documents/projects/math/tensorFlow/cTensor/src/main.cpp -o CMakeFiles/run.dir/main.cpp.s

CMakeFiles/run.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/run.dir/main.cpp.o.requires

CMakeFiles/run.dir/main.cpp.o.provides: CMakeFiles/run.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/run.dir/main.cpp.o.provides

CMakeFiles/run.dir/main.cpp.o.provides.build: CMakeFiles/run.dir/main.cpp.o


CMakeFiles/run.dir/Matrix/kernel.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/Matrix/kernel.cpp.o: ../Matrix/kernel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/theo/Documents/projects/math/tensorFlow/cTensor/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/run.dir/Matrix/kernel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/Matrix/kernel.cpp.o -c /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Matrix/kernel.cpp

CMakeFiles/run.dir/Matrix/kernel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/Matrix/kernel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Matrix/kernel.cpp > CMakeFiles/run.dir/Matrix/kernel.cpp.i

CMakeFiles/run.dir/Matrix/kernel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/Matrix/kernel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Matrix/kernel.cpp -o CMakeFiles/run.dir/Matrix/kernel.cpp.s

CMakeFiles/run.dir/Matrix/kernel.cpp.o.requires:

.PHONY : CMakeFiles/run.dir/Matrix/kernel.cpp.o.requires

CMakeFiles/run.dir/Matrix/kernel.cpp.o.provides: CMakeFiles/run.dir/Matrix/kernel.cpp.o.requires
	$(MAKE) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/Matrix/kernel.cpp.o.provides.build
.PHONY : CMakeFiles/run.dir/Matrix/kernel.cpp.o.provides

CMakeFiles/run.dir/Matrix/kernel.cpp.o.provides.build: CMakeFiles/run.dir/Matrix/kernel.cpp.o


CMakeFiles/run.dir/Matrix/operations.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/Matrix/operations.cpp.o: ../Matrix/operations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/theo/Documents/projects/math/tensorFlow/cTensor/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/run.dir/Matrix/operations.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/Matrix/operations.cpp.o -c /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Matrix/operations.cpp

CMakeFiles/run.dir/Matrix/operations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/Matrix/operations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Matrix/operations.cpp > CMakeFiles/run.dir/Matrix/operations.cpp.i

CMakeFiles/run.dir/Matrix/operations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/Matrix/operations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Matrix/operations.cpp -o CMakeFiles/run.dir/Matrix/operations.cpp.s

CMakeFiles/run.dir/Matrix/operations.cpp.o.requires:

.PHONY : CMakeFiles/run.dir/Matrix/operations.cpp.o.requires

CMakeFiles/run.dir/Matrix/operations.cpp.o.provides: CMakeFiles/run.dir/Matrix/operations.cpp.o.requires
	$(MAKE) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/Matrix/operations.cpp.o.provides.build
.PHONY : CMakeFiles/run.dir/Matrix/operations.cpp.o.provides

CMakeFiles/run.dir/Matrix/operations.cpp.o.provides.build: CMakeFiles/run.dir/Matrix/operations.cpp.o


CMakeFiles/run.dir/Networks/Network.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/Networks/Network.cpp.o: ../Networks/Network.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/theo/Documents/projects/math/tensorFlow/cTensor/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/run.dir/Networks/Network.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run.dir/Networks/Network.cpp.o -c /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Networks/Network.cpp

CMakeFiles/run.dir/Networks/Network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/Networks/Network.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Networks/Network.cpp > CMakeFiles/run.dir/Networks/Network.cpp.i

CMakeFiles/run.dir/Networks/Network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/Networks/Network.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theo/Documents/projects/math/tensorFlow/cTensor/src/Networks/Network.cpp -o CMakeFiles/run.dir/Networks/Network.cpp.s

CMakeFiles/run.dir/Networks/Network.cpp.o.requires:

.PHONY : CMakeFiles/run.dir/Networks/Network.cpp.o.requires

CMakeFiles/run.dir/Networks/Network.cpp.o.provides: CMakeFiles/run.dir/Networks/Network.cpp.o.requires
	$(MAKE) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/Networks/Network.cpp.o.provides.build
.PHONY : CMakeFiles/run.dir/Networks/Network.cpp.o.provides

CMakeFiles/run.dir/Networks/Network.cpp.o.provides.build: CMakeFiles/run.dir/Networks/Network.cpp.o


# Object files for target run
run_OBJECTS = \
"CMakeFiles/run.dir/main.cpp.o" \
"CMakeFiles/run.dir/Matrix/kernel.cpp.o" \
"CMakeFiles/run.dir/Matrix/operations.cpp.o" \
"CMakeFiles/run.dir/Networks/Network.cpp.o"

# External object files for target run
run_EXTERNAL_OBJECTS =

run: CMakeFiles/run.dir/main.cpp.o
run: CMakeFiles/run.dir/Matrix/kernel.cpp.o
run: CMakeFiles/run.dir/Matrix/operations.cpp.o
run: CMakeFiles/run.dir/Networks/Network.cpp.o
run: CMakeFiles/run.dir/build.make
run: CMakeFiles/run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/theo/Documents/projects/math/tensorFlow/cTensor/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run.dir/build: run

.PHONY : CMakeFiles/run.dir/build

CMakeFiles/run.dir/requires: CMakeFiles/run.dir/main.cpp.o.requires
CMakeFiles/run.dir/requires: CMakeFiles/run.dir/Matrix/kernel.cpp.o.requires
CMakeFiles/run.dir/requires: CMakeFiles/run.dir/Matrix/operations.cpp.o.requires
CMakeFiles/run.dir/requires: CMakeFiles/run.dir/Networks/Network.cpp.o.requires

.PHONY : CMakeFiles/run.dir/requires

CMakeFiles/run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run.dir/clean

CMakeFiles/run.dir/depend:
	cd /home/theo/Documents/projects/math/tensorFlow/cTensor/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/theo/Documents/projects/math/tensorFlow/cTensor/src /home/theo/Documents/projects/math/tensorFlow/cTensor/src /home/theo/Documents/projects/math/tensorFlow/cTensor/src/build /home/theo/Documents/projects/math/tensorFlow/cTensor/src/build /home/theo/Documents/projects/math/tensorFlow/cTensor/src/build/CMakeFiles/run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run.dir/depend
