# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug

# Include any dependencies generated for this target.
include src/bbvm/CMakeFiles/bbvm.dir/depend.make
# Include the progress variables for this target.
include src/bbvm/CMakeFiles/bbvm.dir/progress.make

# Include the compile flags for this target's objects.
include src/bbvm/CMakeFiles/bbvm.dir/flags.make

src/bbvm/CMakeFiles/bbvm.dir/main.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/main.cc.o: ../src/bbvm/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/main.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/main.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/main.cc

src/bbvm/CMakeFiles/bbvm.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/main.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/main.cc > CMakeFiles/bbvm.dir/main.cc.i

src/bbvm/CMakeFiles/bbvm.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/main.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/main.cc -o CMakeFiles/bbvm.dir/main.cc.s

src/bbvm/CMakeFiles/bbvm.dir/bbvm.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/bbvm.cc.o: ../src/bbvm/bbvm.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/bbvm.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/bbvm.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/bbvm.cc

src/bbvm/CMakeFiles/bbvm.dir/bbvm.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/bbvm.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/bbvm.cc > CMakeFiles/bbvm.dir/bbvm.cc.i

src/bbvm/CMakeFiles/bbvm.dir/bbvm.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/bbvm.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/bbvm.cc -o CMakeFiles/bbvm.dir/bbvm.cc.s

src/bbvm/CMakeFiles/bbvm.dir/renderer.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/renderer.cc.o: ../src/bbvm/renderer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/renderer.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/renderer.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/renderer.cc

src/bbvm/CMakeFiles/bbvm.dir/renderer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/renderer.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/renderer.cc > CMakeFiles/bbvm.dir/renderer.cc.i

src/bbvm/CMakeFiles/bbvm.dir/renderer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/renderer.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/renderer.cc -o CMakeFiles/bbvm.dir/renderer.cc.s

src/bbvm/CMakeFiles/bbvm.dir/inport.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/inport.cc.o: ../src/bbvm/inport.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/inport.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/inport.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/inport.cc

src/bbvm/CMakeFiles/bbvm.dir/inport.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/inport.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/inport.cc > CMakeFiles/bbvm.dir/inport.cc.i

src/bbvm/CMakeFiles/bbvm.dir/inport.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/inport.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/inport.cc -o CMakeFiles/bbvm.dir/inport.cc.s

src/bbvm/CMakeFiles/bbvm.dir/input_iml.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/input_iml.cc.o: ../src/bbvm/input_iml.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/input_iml.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/input_iml.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/input_iml.cc

src/bbvm/CMakeFiles/bbvm.dir/input_iml.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/input_iml.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/input_iml.cc > CMakeFiles/bbvm.dir/input_iml.cc.i

src/bbvm/CMakeFiles/bbvm.dir/input_iml.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/input_iml.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/input_iml.cc -o CMakeFiles/bbvm.dir/input_iml.cc.s

src/bbvm/CMakeFiles/bbvm.dir/outport.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/outport.cc.o: ../src/bbvm/outport.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/outport.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/outport.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/outport.cc

src/bbvm/CMakeFiles/bbvm.dir/outport.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/outport.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/outport.cc > CMakeFiles/bbvm.dir/outport.cc.i

src/bbvm/CMakeFiles/bbvm.dir/outport.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/outport.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/outport.cc -o CMakeFiles/bbvm.dir/outport.cc.s

src/bbvm/CMakeFiles/bbvm.dir/screen.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/screen.cc.o: ../src/bbvm/screen.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/screen.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/screen.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/screen.cc

src/bbvm/CMakeFiles/bbvm.dir/screen.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/screen.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/screen.cc > CMakeFiles/bbvm.dir/screen.cc.i

src/bbvm/CMakeFiles/bbvm.dir/screen.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/screen.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/screen.cc -o CMakeFiles/bbvm.dir/screen.cc.s

src/bbvm/CMakeFiles/bbvm.dir/storage.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/storage.cc.o: ../src/bbvm/storage.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/storage.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/storage.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/storage.cc

src/bbvm/CMakeFiles/bbvm.dir/storage.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/storage.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/storage.cc > CMakeFiles/bbvm.dir/storage.cc.i

src/bbvm/CMakeFiles/bbvm.dir/storage.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/storage.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/storage.cc -o CMakeFiles/bbvm.dir/storage.cc.s

src/bbvm/CMakeFiles/bbvm.dir/string_manager.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/string_manager.cc.o: ../src/bbvm/string_manager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/string_manager.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/string_manager.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/string_manager.cc

src/bbvm/CMakeFiles/bbvm.dir/string_manager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/string_manager.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/string_manager.cc > CMakeFiles/bbvm.dir/string_manager.cc.i

src/bbvm/CMakeFiles/bbvm.dir/string_manager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/string_manager.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/string_manager.cc -o CMakeFiles/bbvm.dir/string_manager.cc.s

src/bbvm/CMakeFiles/bbvm.dir/utils.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/utils.cc.o: ../src/bbvm/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/utils.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/utils.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/utils.cc

src/bbvm/CMakeFiles/bbvm.dir/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/utils.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/utils.cc > CMakeFiles/bbvm.dir/utils.cc.i

src/bbvm/CMakeFiles/bbvm.dir/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/utils.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/utils.cc -o CMakeFiles/bbvm.dir/utils.cc.s

src/bbvm/CMakeFiles/bbvm.dir/sdl.cc.o: src/bbvm/CMakeFiles/bbvm.dir/flags.make
src/bbvm/CMakeFiles/bbvm.dir/sdl.cc.o: ../src/bbvm/sdl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/bbvm/CMakeFiles/bbvm.dir/sdl.cc.o"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bbvm.dir/sdl.cc.o -c /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/sdl.cc

src/bbvm/CMakeFiles/bbvm.dir/sdl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bbvm.dir/sdl.cc.i"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/sdl.cc > CMakeFiles/bbvm.dir/sdl.cc.i

src/bbvm/CMakeFiles/bbvm.dir/sdl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bbvm.dir/sdl.cc.s"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm/sdl.cc -o CMakeFiles/bbvm.dir/sdl.cc.s

# Object files for target bbvm
bbvm_OBJECTS = \
"CMakeFiles/bbvm.dir/main.cc.o" \
"CMakeFiles/bbvm.dir/bbvm.cc.o" \
"CMakeFiles/bbvm.dir/renderer.cc.o" \
"CMakeFiles/bbvm.dir/inport.cc.o" \
"CMakeFiles/bbvm.dir/input_iml.cc.o" \
"CMakeFiles/bbvm.dir/outport.cc.o" \
"CMakeFiles/bbvm.dir/screen.cc.o" \
"CMakeFiles/bbvm.dir/storage.cc.o" \
"CMakeFiles/bbvm.dir/string_manager.cc.o" \
"CMakeFiles/bbvm.dir/utils.cc.o" \
"CMakeFiles/bbvm.dir/sdl.cc.o"

# External object files for target bbvm
bbvm_EXTERNAL_OBJECTS =

src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/main.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/bbvm.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/renderer.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/inport.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/input_iml.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/outport.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/screen.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/storage.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/string_manager.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/utils.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/sdl.cc.o
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/build.make
src/bbvm/bbvm: src/bbvm/CMakeFiles/bbvm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable bbvm"
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bbvm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/bbvm/CMakeFiles/bbvm.dir/build: src/bbvm/bbvm
.PHONY : src/bbvm/CMakeFiles/bbvm.dir/build

src/bbvm/CMakeFiles/bbvm.dir/clean:
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm && $(CMAKE_COMMAND) -P CMakeFiles/bbvm.dir/cmake_clean.cmake
.PHONY : src/bbvm/CMakeFiles/bbvm.dir/clean

src/bbvm/CMakeFiles/bbvm.dir/depend:
	cd /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/src/bbvm /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm /Users/liangyulin/WorkSpace/Projects/CLionProjects/bbasic/cmake-build-debug/src/bbvm/CMakeFiles/bbvm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bbvm/CMakeFiles/bbvm.dir/depend

