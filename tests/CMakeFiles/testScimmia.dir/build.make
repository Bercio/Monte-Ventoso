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
CMAKE_COMMAND = /opt/clion-2016.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2016.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rita/Documenti/Programmi/Monte-Ventoso

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rita/Documenti/Programmi/Monte-Ventoso

# Include any dependencies generated for this target.
include tests/CMakeFiles/testScimmia.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/testScimmia.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/testScimmia.dir/flags.make

tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o: tests/CMakeFiles/testScimmia.dir/flags.make
tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o: tests/testScimmia.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rita/Documenti/Programmi/Monte-Ventoso/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o"
	cd /home/rita/Documenti/Programmi/Monte-Ventoso/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testScimmia.dir/testScimmia.cpp.o -c /home/rita/Documenti/Programmi/Monte-Ventoso/tests/testScimmia.cpp

tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testScimmia.dir/testScimmia.cpp.i"
	cd /home/rita/Documenti/Programmi/Monte-Ventoso/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rita/Documenti/Programmi/Monte-Ventoso/tests/testScimmia.cpp > CMakeFiles/testScimmia.dir/testScimmia.cpp.i

tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testScimmia.dir/testScimmia.cpp.s"
	cd /home/rita/Documenti/Programmi/Monte-Ventoso/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rita/Documenti/Programmi/Monte-Ventoso/tests/testScimmia.cpp -o CMakeFiles/testScimmia.dir/testScimmia.cpp.s

tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.requires:

.PHONY : tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.requires

tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.provides: tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/testScimmia.dir/build.make tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.provides.build
.PHONY : tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.provides

tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.provides.build: tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o


# Object files for target testScimmia
testScimmia_OBJECTS = \
"CMakeFiles/testScimmia.dir/testScimmia.cpp.o"

# External object files for target testScimmia
testScimmia_EXTERNAL_OBJECTS =

tests/testScimmia: tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o
tests/testScimmia: tests/CMakeFiles/testScimmia.dir/build.make
tests/testScimmia: lib/gtest/libgtest.a
tests/testScimmia: lib/gtest/libgtest_main.a
tests/testScimmia: libScimmia.a
tests/testScimmia: lib/gtest/libgtest.a
tests/testScimmia: libParete.a
tests/testScimmia: lib/Snap-3.0/snap-core/Snap.o
tests/testScimmia: tests/CMakeFiles/testScimmia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rita/Documenti/Programmi/Monte-Ventoso/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testScimmia"
	cd /home/rita/Documenti/Programmi/Monte-Ventoso/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testScimmia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/testScimmia.dir/build: tests/testScimmia

.PHONY : tests/CMakeFiles/testScimmia.dir/build

tests/CMakeFiles/testScimmia.dir/requires: tests/CMakeFiles/testScimmia.dir/testScimmia.cpp.o.requires

.PHONY : tests/CMakeFiles/testScimmia.dir/requires

tests/CMakeFiles/testScimmia.dir/clean:
	cd /home/rita/Documenti/Programmi/Monte-Ventoso/tests && $(CMAKE_COMMAND) -P CMakeFiles/testScimmia.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testScimmia.dir/clean

tests/CMakeFiles/testScimmia.dir/depend:
	cd /home/rita/Documenti/Programmi/Monte-Ventoso && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rita/Documenti/Programmi/Monte-Ventoso /home/rita/Documenti/Programmi/Monte-Ventoso/tests /home/rita/Documenti/Programmi/Monte-Ventoso /home/rita/Documenti/Programmi/Monte-Ventoso/tests /home/rita/Documenti/Programmi/Monte-Ventoso/tests/CMakeFiles/testScimmia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testScimmia.dir/depend

