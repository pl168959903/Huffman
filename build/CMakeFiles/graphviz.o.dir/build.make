# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\User\Desktop\cm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\User\Desktop\cm\build

# Include any dependencies generated for this target.
include CMakeFiles/graphviz.o.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/graphviz.o.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/graphviz.o.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graphviz.o.dir/flags.make

CMakeFiles/graphviz.o.dir/graphviz.c.obj: CMakeFiles/graphviz.o.dir/flags.make
CMakeFiles/graphviz.o.dir/graphviz.c.obj: C:/Users/User/Desktop/cm/graphviz.c
CMakeFiles/graphviz.o.dir/graphviz.c.obj: CMakeFiles/graphviz.o.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\User\Desktop\cm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/graphviz.o.dir/graphviz.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/graphviz.o.dir/graphviz.c.obj -MF CMakeFiles\graphviz.o.dir\graphviz.c.obj.d -o CMakeFiles\graphviz.o.dir\graphviz.c.obj -c C:\Users\User\Desktop\cm\graphviz.c

CMakeFiles/graphviz.o.dir/graphviz.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graphviz.o.dir/graphviz.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\User\Desktop\cm\graphviz.c > CMakeFiles\graphviz.o.dir\graphviz.c.i

CMakeFiles/graphviz.o.dir/graphviz.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graphviz.o.dir/graphviz.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\User\Desktop\cm\graphviz.c -o CMakeFiles\graphviz.o.dir\graphviz.c.s

# Object files for target graphviz.o
graphviz_o_OBJECTS = \
"CMakeFiles/graphviz.o.dir/graphviz.c.obj"

# External object files for target graphviz.o
graphviz_o_EXTERNAL_OBJECTS =

libgraphviz.o.a: CMakeFiles/graphviz.o.dir/graphviz.c.obj
libgraphviz.o.a: CMakeFiles/graphviz.o.dir/build.make
libgraphviz.o.a: CMakeFiles/graphviz.o.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\User\Desktop\cm\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libgraphviz.o.a"
	$(CMAKE_COMMAND) -P CMakeFiles\graphviz.o.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\graphviz.o.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graphviz.o.dir/build: libgraphviz.o.a
.PHONY : CMakeFiles/graphviz.o.dir/build

CMakeFiles/graphviz.o.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\graphviz.o.dir\cmake_clean.cmake
.PHONY : CMakeFiles/graphviz.o.dir/clean

CMakeFiles/graphviz.o.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\User\Desktop\cm C:\Users\User\Desktop\cm C:\Users\User\Desktop\cm\build C:\Users\User\Desktop\cm\build C:\Users\User\Desktop\cm\build\CMakeFiles\graphviz.o.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graphviz.o.dir/depend
