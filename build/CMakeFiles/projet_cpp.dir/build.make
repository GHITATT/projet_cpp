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
CMAKE_SOURCE_DIR = /home/ghita/Documents/C++/projet_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ghita/Documents/C++/projet_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/projet_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/projet_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/projet_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projet_cpp.dir/flags.make

CMakeFiles/projet_cpp.dir/src/main.cpp.o: CMakeFiles/projet_cpp.dir/flags.make
CMakeFiles/projet_cpp.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/projet_cpp.dir/src/main.cpp.o: CMakeFiles/projet_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghita/Documents/C++/projet_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/projet_cpp.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/projet_cpp.dir/src/main.cpp.o -MF CMakeFiles/projet_cpp.dir/src/main.cpp.o.d -o CMakeFiles/projet_cpp.dir/src/main.cpp.o -c /home/ghita/Documents/C++/projet_cpp/src/main.cpp

CMakeFiles/projet_cpp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/projet_cpp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghita/Documents/C++/projet_cpp/src/main.cpp > CMakeFiles/projet_cpp.dir/src/main.cpp.i

CMakeFiles/projet_cpp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/projet_cpp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghita/Documents/C++/projet_cpp/src/main.cpp -o CMakeFiles/projet_cpp.dir/src/main.cpp.s

CMakeFiles/projet_cpp.dir/src/vibes.cpp.o: CMakeFiles/projet_cpp.dir/flags.make
CMakeFiles/projet_cpp.dir/src/vibes.cpp.o: ../src/vibes.cpp
CMakeFiles/projet_cpp.dir/src/vibes.cpp.o: CMakeFiles/projet_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghita/Documents/C++/projet_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/projet_cpp.dir/src/vibes.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/projet_cpp.dir/src/vibes.cpp.o -MF CMakeFiles/projet_cpp.dir/src/vibes.cpp.o.d -o CMakeFiles/projet_cpp.dir/src/vibes.cpp.o -c /home/ghita/Documents/C++/projet_cpp/src/vibes.cpp

CMakeFiles/projet_cpp.dir/src/vibes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/projet_cpp.dir/src/vibes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghita/Documents/C++/projet_cpp/src/vibes.cpp > CMakeFiles/projet_cpp.dir/src/vibes.cpp.i

CMakeFiles/projet_cpp.dir/src/vibes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/projet_cpp.dir/src/vibes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghita/Documents/C++/projet_cpp/src/vibes.cpp -o CMakeFiles/projet_cpp.dir/src/vibes.cpp.s

# Object files for target projet_cpp
projet_cpp_OBJECTS = \
"CMakeFiles/projet_cpp.dir/src/main.cpp.o" \
"CMakeFiles/projet_cpp.dir/src/vibes.cpp.o"

# External object files for target projet_cpp
projet_cpp_EXTERNAL_OBJECTS =

projet_cpp: CMakeFiles/projet_cpp.dir/src/main.cpp.o
projet_cpp: CMakeFiles/projet_cpp.dir/src/vibes.cpp.o
projet_cpp: CMakeFiles/projet_cpp.dir/build.make
projet_cpp: CMakeFiles/projet_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ghita/Documents/C++/projet_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable projet_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/projet_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projet_cpp.dir/build: projet_cpp
.PHONY : CMakeFiles/projet_cpp.dir/build

CMakeFiles/projet_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/projet_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/projet_cpp.dir/clean

CMakeFiles/projet_cpp.dir/depend:
	cd /home/ghita/Documents/C++/projet_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ghita/Documents/C++/projet_cpp /home/ghita/Documents/C++/projet_cpp /home/ghita/Documents/C++/projet_cpp/build /home/ghita/Documents/C++/projet_cpp/build /home/ghita/Documents/C++/projet_cpp/build/CMakeFiles/projet_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projet_cpp.dir/depend

