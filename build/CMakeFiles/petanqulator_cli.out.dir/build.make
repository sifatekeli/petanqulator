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
<<<<<<< HEAD
CMAKE_SOURCE_DIR = /home/kevin/Bureau/master/projet/petanqulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevin/Bureau/master/projet/petanqulator/build
=======
CMAKE_SOURCE_DIR = /home/sifa/Bureau/ULCO/projet/petanqulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sifa/Bureau/ULCO/projet/petanqulator/build
>>>>>>> master

# Include any dependencies generated for this target.
include CMakeFiles/petanqulator_cli.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/petanqulator_cli.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/petanqulator_cli.out.dir/flags.make

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o: CMakeFiles/petanqulator_cli.out.dir/flags.make
CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o: ../src/petanqulator_cli/petanqulator_cli.cpp
<<<<<<< HEAD
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kevin/Bureau/master/projet/petanqulator/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o -c /home/kevin/Bureau/master/projet/petanqulator/src/petanqulator_cli/petanqulator_cli.cpp

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kevin/Bureau/master/projet/petanqulator/src/petanqulator_cli/petanqulator_cli.cpp > CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.i

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kevin/Bureau/master/projet/petanqulator/src/petanqulator_cli/petanqulator_cli.cpp -o CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.s
=======
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sifa/Bureau/ULCO/projet/petanqulator/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o -c /home/sifa/Bureau/ULCO/projet/petanqulator/src/petanqulator_cli/petanqulator_cli.cpp

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sifa/Bureau/ULCO/projet/petanqulator/src/petanqulator_cli/petanqulator_cli.cpp > CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.i

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sifa/Bureau/ULCO/projet/petanqulator/src/petanqulator_cli/petanqulator_cli.cpp -o CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.s
>>>>>>> master

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.requires:
.PHONY : CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.requires

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.provides: CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.requires
	$(MAKE) -f CMakeFiles/petanqulator_cli.out.dir/build.make CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.provides.build
.PHONY : CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.provides

CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.provides.build: CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o

# Object files for target petanqulator_cli.out
petanqulator_cli_out_OBJECTS = \
"CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o"

# External object files for target petanqulator_cli.out
petanqulator_cli_out_EXTERNAL_OBJECTS =

petanqulator_cli.out: CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o
petanqulator_cli.out: CMakeFiles/petanqulator_cli.out.dir/build.make
petanqulator_cli.out: libpetanqulator.a
petanqulator_cli.out: /usr/lib/x86_64-linux-gnu/libBulletDynamics.so
petanqulator_cli.out: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
petanqulator_cli.out: /usr/lib/x86_64-linux-gnu/libLinearMath.so
petanqulator_cli.out: /usr/lib/x86_64-linux-gnu/libBulletSoftBody.so
petanqulator_cli.out: CMakeFiles/petanqulator_cli.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable petanqulator_cli.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/petanqulator_cli.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/petanqulator_cli.out.dir/build: petanqulator_cli.out
.PHONY : CMakeFiles/petanqulator_cli.out.dir/build

CMakeFiles/petanqulator_cli.out.dir/requires: CMakeFiles/petanqulator_cli.out.dir/src/petanqulator_cli/petanqulator_cli.cpp.o.requires
.PHONY : CMakeFiles/petanqulator_cli.out.dir/requires

CMakeFiles/petanqulator_cli.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/petanqulator_cli.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/petanqulator_cli.out.dir/clean

CMakeFiles/petanqulator_cli.out.dir/depend:
<<<<<<< HEAD
	cd /home/kevin/Bureau/master/projet/petanqulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin/Bureau/master/projet/petanqulator /home/kevin/Bureau/master/projet/petanqulator /home/kevin/Bureau/master/projet/petanqulator/build /home/kevin/Bureau/master/projet/petanqulator/build /home/kevin/Bureau/master/projet/petanqulator/build/CMakeFiles/petanqulator_cli.out.dir/DependInfo.cmake --color=$(COLOR)
=======
	cd /home/sifa/Bureau/ULCO/projet/petanqulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sifa/Bureau/ULCO/projet/petanqulator /home/sifa/Bureau/ULCO/projet/petanqulator /home/sifa/Bureau/ULCO/projet/petanqulator/build /home/sifa/Bureau/ULCO/projet/petanqulator/build /home/sifa/Bureau/ULCO/projet/petanqulator/build/CMakeFiles/petanqulator_cli.out.dir/DependInfo.cmake --color=$(COLOR)
>>>>>>> master
.PHONY : CMakeFiles/petanqulator_cli.out.dir/depend

