# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/doriandrivet/TD-POO/TP-POO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/doriandrivet/TD-POO/build

# Include any dependencies generated for this target.
include CMakeFiles/Simulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Simulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Simulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Simulator.dir/flags.make

CMakeFiles/Simulator.dir/main.cpp.o: CMakeFiles/Simulator.dir/flags.make
CMakeFiles/Simulator.dir/main.cpp.o: /Users/doriandrivet/TD-POO/TP-POO/main.cpp
CMakeFiles/Simulator.dir/main.cpp.o: CMakeFiles/Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doriandrivet/TD-POO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Simulator.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Simulator.dir/main.cpp.o -MF CMakeFiles/Simulator.dir/main.cpp.o.d -o CMakeFiles/Simulator.dir/main.cpp.o -c /Users/doriandrivet/TD-POO/TP-POO/main.cpp

CMakeFiles/Simulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Simulator.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doriandrivet/TD-POO/TP-POO/main.cpp > CMakeFiles/Simulator.dir/main.cpp.i

CMakeFiles/Simulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Simulator.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doriandrivet/TD-POO/TP-POO/main.cpp -o CMakeFiles/Simulator.dir/main.cpp.s

CMakeFiles/Simulator.dir/problem.cpp.o: CMakeFiles/Simulator.dir/flags.make
CMakeFiles/Simulator.dir/problem.cpp.o: /Users/doriandrivet/TD-POO/TP-POO/problem.cpp
CMakeFiles/Simulator.dir/problem.cpp.o: CMakeFiles/Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doriandrivet/TD-POO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Simulator.dir/problem.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Simulator.dir/problem.cpp.o -MF CMakeFiles/Simulator.dir/problem.cpp.o.d -o CMakeFiles/Simulator.dir/problem.cpp.o -c /Users/doriandrivet/TD-POO/TP-POO/problem.cpp

CMakeFiles/Simulator.dir/problem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Simulator.dir/problem.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doriandrivet/TD-POO/TP-POO/problem.cpp > CMakeFiles/Simulator.dir/problem.cpp.i

CMakeFiles/Simulator.dir/problem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Simulator.dir/problem.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doriandrivet/TD-POO/TP-POO/problem.cpp -o CMakeFiles/Simulator.dir/problem.cpp.s

CMakeFiles/Simulator.dir/equation.cpp.o: CMakeFiles/Simulator.dir/flags.make
CMakeFiles/Simulator.dir/equation.cpp.o: /Users/doriandrivet/TD-POO/TP-POO/equation.cpp
CMakeFiles/Simulator.dir/equation.cpp.o: CMakeFiles/Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doriandrivet/TD-POO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Simulator.dir/equation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Simulator.dir/equation.cpp.o -MF CMakeFiles/Simulator.dir/equation.cpp.o.d -o CMakeFiles/Simulator.dir/equation.cpp.o -c /Users/doriandrivet/TD-POO/TP-POO/equation.cpp

CMakeFiles/Simulator.dir/equation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Simulator.dir/equation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doriandrivet/TD-POO/TP-POO/equation.cpp > CMakeFiles/Simulator.dir/equation.cpp.i

CMakeFiles/Simulator.dir/equation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Simulator.dir/equation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doriandrivet/TD-POO/TP-POO/equation.cpp -o CMakeFiles/Simulator.dir/equation.cpp.s

CMakeFiles/Simulator.dir/UniformMesh.cpp.o: CMakeFiles/Simulator.dir/flags.make
CMakeFiles/Simulator.dir/UniformMesh.cpp.o: /Users/doriandrivet/TD-POO/TP-POO/UniformMesh.cpp
CMakeFiles/Simulator.dir/UniformMesh.cpp.o: CMakeFiles/Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doriandrivet/TD-POO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Simulator.dir/UniformMesh.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Simulator.dir/UniformMesh.cpp.o -MF CMakeFiles/Simulator.dir/UniformMesh.cpp.o.d -o CMakeFiles/Simulator.dir/UniformMesh.cpp.o -c /Users/doriandrivet/TD-POO/TP-POO/UniformMesh.cpp

CMakeFiles/Simulator.dir/UniformMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Simulator.dir/UniformMesh.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doriandrivet/TD-POO/TP-POO/UniformMesh.cpp > CMakeFiles/Simulator.dir/UniformMesh.cpp.i

CMakeFiles/Simulator.dir/UniformMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Simulator.dir/UniformMesh.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doriandrivet/TD-POO/TP-POO/UniformMesh.cpp -o CMakeFiles/Simulator.dir/UniformMesh.cpp.s

CMakeFiles/Simulator.dir/variable.cpp.o: CMakeFiles/Simulator.dir/flags.make
CMakeFiles/Simulator.dir/variable.cpp.o: /Users/doriandrivet/TD-POO/TP-POO/variable.cpp
CMakeFiles/Simulator.dir/variable.cpp.o: CMakeFiles/Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doriandrivet/TD-POO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Simulator.dir/variable.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Simulator.dir/variable.cpp.o -MF CMakeFiles/Simulator.dir/variable.cpp.o.d -o CMakeFiles/Simulator.dir/variable.cpp.o -c /Users/doriandrivet/TD-POO/TP-POO/variable.cpp

CMakeFiles/Simulator.dir/variable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Simulator.dir/variable.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doriandrivet/TD-POO/TP-POO/variable.cpp > CMakeFiles/Simulator.dir/variable.cpp.i

CMakeFiles/Simulator.dir/variable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Simulator.dir/variable.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doriandrivet/TD-POO/TP-POO/variable.cpp -o CMakeFiles/Simulator.dir/variable.cpp.s

# Object files for target Simulator
Simulator_OBJECTS = \
"CMakeFiles/Simulator.dir/main.cpp.o" \
"CMakeFiles/Simulator.dir/problem.cpp.o" \
"CMakeFiles/Simulator.dir/equation.cpp.o" \
"CMakeFiles/Simulator.dir/UniformMesh.cpp.o" \
"CMakeFiles/Simulator.dir/variable.cpp.o"

# External object files for target Simulator
Simulator_EXTERNAL_OBJECTS =

Simulator: CMakeFiles/Simulator.dir/main.cpp.o
Simulator: CMakeFiles/Simulator.dir/problem.cpp.o
Simulator: CMakeFiles/Simulator.dir/equation.cpp.o
Simulator: CMakeFiles/Simulator.dir/UniformMesh.cpp.o
Simulator: CMakeFiles/Simulator.dir/variable.cpp.o
Simulator: CMakeFiles/Simulator.dir/build.make
Simulator: /opt/homebrew/lib/libspdlog.1.15.0.dylib
Simulator: /opt/homebrew/lib/libfmt.11.0.2.dylib
Simulator: CMakeFiles/Simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/doriandrivet/TD-POO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Simulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Simulator.dir/build: Simulator
.PHONY : CMakeFiles/Simulator.dir/build

CMakeFiles/Simulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Simulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Simulator.dir/clean

CMakeFiles/Simulator.dir/depend:
	cd /Users/doriandrivet/TD-POO/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/doriandrivet/TD-POO/TP-POO /Users/doriandrivet/TD-POO/TP-POO /Users/doriandrivet/TD-POO/build /Users/doriandrivet/TD-POO/build /Users/doriandrivet/TD-POO/build/CMakeFiles/Simulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Simulator.dir/depend

