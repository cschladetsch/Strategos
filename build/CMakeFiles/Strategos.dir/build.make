# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/xian/local/ChessGo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xian/local/ChessGo/build

# Include any dependencies generated for this target.
include CMakeFiles/Strategos.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Strategos.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Strategos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Strategos.dir/flags.make

CMakeFiles/Strategos.dir/src/board.cpp.o: CMakeFiles/Strategos.dir/flags.make
CMakeFiles/Strategos.dir/src/board.cpp.o: /home/xian/local/ChessGo/src/board.cpp
CMakeFiles/Strategos.dir/src/board.cpp.o: CMakeFiles/Strategos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/xian/local/ChessGo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Strategos.dir/src/board.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Strategos.dir/src/board.cpp.o -MF CMakeFiles/Strategos.dir/src/board.cpp.o.d -o CMakeFiles/Strategos.dir/src/board.cpp.o -c /home/xian/local/ChessGo/src/board.cpp

CMakeFiles/Strategos.dir/src/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Strategos.dir/src/board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xian/local/ChessGo/src/board.cpp > CMakeFiles/Strategos.dir/src/board.cpp.i

CMakeFiles/Strategos.dir/src/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Strategos.dir/src/board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xian/local/ChessGo/src/board.cpp -o CMakeFiles/Strategos.dir/src/board.cpp.s

CMakeFiles/Strategos.dir/src/game.cpp.o: CMakeFiles/Strategos.dir/flags.make
CMakeFiles/Strategos.dir/src/game.cpp.o: /home/xian/local/ChessGo/src/game.cpp
CMakeFiles/Strategos.dir/src/game.cpp.o: CMakeFiles/Strategos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/xian/local/ChessGo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Strategos.dir/src/game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Strategos.dir/src/game.cpp.o -MF CMakeFiles/Strategos.dir/src/game.cpp.o.d -o CMakeFiles/Strategos.dir/src/game.cpp.o -c /home/xian/local/ChessGo/src/game.cpp

CMakeFiles/Strategos.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Strategos.dir/src/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xian/local/ChessGo/src/game.cpp > CMakeFiles/Strategos.dir/src/game.cpp.i

CMakeFiles/Strategos.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Strategos.dir/src/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xian/local/ChessGo/src/game.cpp -o CMakeFiles/Strategos.dir/src/game.cpp.s

CMakeFiles/Strategos.dir/src/main.cpp.o: CMakeFiles/Strategos.dir/flags.make
CMakeFiles/Strategos.dir/src/main.cpp.o: /home/xian/local/ChessGo/src/main.cpp
CMakeFiles/Strategos.dir/src/main.cpp.o: CMakeFiles/Strategos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/xian/local/ChessGo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Strategos.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Strategos.dir/src/main.cpp.o -MF CMakeFiles/Strategos.dir/src/main.cpp.o.d -o CMakeFiles/Strategos.dir/src/main.cpp.o -c /home/xian/local/ChessGo/src/main.cpp

CMakeFiles/Strategos.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Strategos.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xian/local/ChessGo/src/main.cpp > CMakeFiles/Strategos.dir/src/main.cpp.i

CMakeFiles/Strategos.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Strategos.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xian/local/ChessGo/src/main.cpp -o CMakeFiles/Strategos.dir/src/main.cpp.s

CMakeFiles/Strategos.dir/src/utils.cpp.o: CMakeFiles/Strategos.dir/flags.make
CMakeFiles/Strategos.dir/src/utils.cpp.o: /home/xian/local/ChessGo/src/utils.cpp
CMakeFiles/Strategos.dir/src/utils.cpp.o: CMakeFiles/Strategos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/xian/local/ChessGo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Strategos.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Strategos.dir/src/utils.cpp.o -MF CMakeFiles/Strategos.dir/src/utils.cpp.o.d -o CMakeFiles/Strategos.dir/src/utils.cpp.o -c /home/xian/local/ChessGo/src/utils.cpp

CMakeFiles/Strategos.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Strategos.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xian/local/ChessGo/src/utils.cpp > CMakeFiles/Strategos.dir/src/utils.cpp.i

CMakeFiles/Strategos.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Strategos.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xian/local/ChessGo/src/utils.cpp -o CMakeFiles/Strategos.dir/src/utils.cpp.s

# Object files for target Strategos
Strategos_OBJECTS = \
"CMakeFiles/Strategos.dir/src/board.cpp.o" \
"CMakeFiles/Strategos.dir/src/game.cpp.o" \
"CMakeFiles/Strategos.dir/src/main.cpp.o" \
"CMakeFiles/Strategos.dir/src/utils.cpp.o"

# External object files for target Strategos
Strategos_EXTERNAL_OBJECTS =

Strategos: CMakeFiles/Strategos.dir/src/board.cpp.o
Strategos: CMakeFiles/Strategos.dir/src/game.cpp.o
Strategos: CMakeFiles/Strategos.dir/src/main.cpp.o
Strategos: CMakeFiles/Strategos.dir/src/utils.cpp.o
Strategos: CMakeFiles/Strategos.dir/build.make
Strategos: /usr/lib/x86_64-linux-gnu/libcurses.so
Strategos: /usr/lib/x86_64-linux-gnu/libform.so
Strategos: CMakeFiles/Strategos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/xian/local/ChessGo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Strategos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Strategos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Strategos.dir/build: Strategos
.PHONY : CMakeFiles/Strategos.dir/build

CMakeFiles/Strategos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Strategos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Strategos.dir/clean

CMakeFiles/Strategos.dir/depend:
	cd /home/xian/local/ChessGo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xian/local/ChessGo /home/xian/local/ChessGo /home/xian/local/ChessGo/build /home/xian/local/ChessGo/build /home/xian/local/ChessGo/build/CMakeFiles/Strategos.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Strategos.dir/depend

