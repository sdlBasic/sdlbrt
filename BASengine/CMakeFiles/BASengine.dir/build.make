# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/vroby/Progetti/sdlbasic/sdlbrt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vroby/Progetti/sdlbasic/sdlbrt

# Include any dependencies generated for this target.
include BASengine/CMakeFiles/BASengine.dir/depend.make

# Include the progress variables for this target.
include BASengine/CMakeFiles/BASengine.dir/progress.make

# Include the compile flags for this target's objects.
include BASengine/CMakeFiles/BASengine.dir/flags.make

BASengine/CMakeFiles/BASengine.dir/datafunction.c.o: BASengine/CMakeFiles/BASengine.dir/flags.make
BASengine/CMakeFiles/BASengine.dir/datafunction.c.o: BASengine/datafunction.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vroby/Progetti/sdlbasic/sdlbrt/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object BASengine/CMakeFiles/BASengine.dir/datafunction.c.o"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/BASengine.dir/datafunction.c.o   -c /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/datafunction.c

BASengine/CMakeFiles/BASengine.dir/datafunction.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BASengine.dir/datafunction.c.i"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/datafunction.c > CMakeFiles/BASengine.dir/datafunction.c.i

BASengine/CMakeFiles/BASengine.dir/datafunction.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BASengine.dir/datafunction.c.s"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/datafunction.c -o CMakeFiles/BASengine.dir/datafunction.c.s

BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.requires:
.PHONY : BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.requires

BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.provides: BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.requires
	$(MAKE) -f BASengine/CMakeFiles/BASengine.dir/build.make BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.provides.build
.PHONY : BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.provides

BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.provides.build: BASengine/CMakeFiles/BASengine.dir/datafunction.c.o

BASengine/CMakeFiles/BASengine.dir/membank.c.o: BASengine/CMakeFiles/BASengine.dir/flags.make
BASengine/CMakeFiles/BASengine.dir/membank.c.o: BASengine/membank.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vroby/Progetti/sdlbasic/sdlbrt/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object BASengine/CMakeFiles/BASengine.dir/membank.c.o"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/BASengine.dir/membank.c.o   -c /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/membank.c

BASengine/CMakeFiles/BASengine.dir/membank.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BASengine.dir/membank.c.i"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/membank.c > CMakeFiles/BASengine.dir/membank.c.i

BASengine/CMakeFiles/BASengine.dir/membank.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BASengine.dir/membank.c.s"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/membank.c -o CMakeFiles/BASengine.dir/membank.c.s

BASengine/CMakeFiles/BASengine.dir/membank.c.o.requires:
.PHONY : BASengine/CMakeFiles/BASengine.dir/membank.c.o.requires

BASengine/CMakeFiles/BASengine.dir/membank.c.o.provides: BASengine/CMakeFiles/BASengine.dir/membank.c.o.requires
	$(MAKE) -f BASengine/CMakeFiles/BASengine.dir/build.make BASengine/CMakeFiles/BASengine.dir/membank.c.o.provides.build
.PHONY : BASengine/CMakeFiles/BASengine.dir/membank.c.o.provides

BASengine/CMakeFiles/BASengine.dir/membank.c.o.provides.build: BASengine/CMakeFiles/BASengine.dir/membank.c.o

BASengine/CMakeFiles/BASengine.dir/dir.c.o: BASengine/CMakeFiles/BASengine.dir/flags.make
BASengine/CMakeFiles/BASengine.dir/dir.c.o: BASengine/dir.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vroby/Progetti/sdlbasic/sdlbrt/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object BASengine/CMakeFiles/BASengine.dir/dir.c.o"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/BASengine.dir/dir.c.o   -c /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/dir.c

BASengine/CMakeFiles/BASengine.dir/dir.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BASengine.dir/dir.c.i"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/dir.c > CMakeFiles/BASengine.dir/dir.c.i

BASengine/CMakeFiles/BASengine.dir/dir.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BASengine.dir/dir.c.s"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/dir.c -o CMakeFiles/BASengine.dir/dir.c.s

BASengine/CMakeFiles/BASengine.dir/dir.c.o.requires:
.PHONY : BASengine/CMakeFiles/BASengine.dir/dir.c.o.requires

BASengine/CMakeFiles/BASengine.dir/dir.c.o.provides: BASengine/CMakeFiles/BASengine.dir/dir.c.o.requires
	$(MAKE) -f BASengine/CMakeFiles/BASengine.dir/build.make BASengine/CMakeFiles/BASengine.dir/dir.c.o.provides.build
.PHONY : BASengine/CMakeFiles/BASengine.dir/dir.c.o.provides

BASengine/CMakeFiles/BASengine.dir/dir.c.o.provides.build: BASengine/CMakeFiles/BASengine.dir/dir.c.o

BASengine/CMakeFiles/BASengine.dir/file.c.o: BASengine/CMakeFiles/BASengine.dir/flags.make
BASengine/CMakeFiles/BASengine.dir/file.c.o: BASengine/file.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vroby/Progetti/sdlbasic/sdlbrt/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object BASengine/CMakeFiles/BASengine.dir/file.c.o"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/BASengine.dir/file.c.o   -c /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/file.c

BASengine/CMakeFiles/BASengine.dir/file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BASengine.dir/file.c.i"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/file.c > CMakeFiles/BASengine.dir/file.c.i

BASengine/CMakeFiles/BASengine.dir/file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BASengine.dir/file.c.s"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/file.c -o CMakeFiles/BASengine.dir/file.c.s

BASengine/CMakeFiles/BASengine.dir/file.c.o.requires:
.PHONY : BASengine/CMakeFiles/BASengine.dir/file.c.o.requires

BASengine/CMakeFiles/BASengine.dir/file.c.o.provides: BASengine/CMakeFiles/BASengine.dir/file.c.o.requires
	$(MAKE) -f BASengine/CMakeFiles/BASengine.dir/build.make BASengine/CMakeFiles/BASengine.dir/file.c.o.provides.build
.PHONY : BASengine/CMakeFiles/BASengine.dir/file.c.o.provides

BASengine/CMakeFiles/BASengine.dir/file.c.o.provides.build: BASengine/CMakeFiles/BASengine.dir/file.c.o

BASengine/CMakeFiles/BASengine.dir/strings.c.o: BASengine/CMakeFiles/BASengine.dir/flags.make
BASengine/CMakeFiles/BASengine.dir/strings.c.o: BASengine/strings.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vroby/Progetti/sdlbasic/sdlbrt/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object BASengine/CMakeFiles/BASengine.dir/strings.c.o"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/BASengine.dir/strings.c.o   -c /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/strings.c

BASengine/CMakeFiles/BASengine.dir/strings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BASengine.dir/strings.c.i"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/strings.c > CMakeFiles/BASengine.dir/strings.c.i

BASengine/CMakeFiles/BASengine.dir/strings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BASengine.dir/strings.c.s"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/strings.c -o CMakeFiles/BASengine.dir/strings.c.s

BASengine/CMakeFiles/BASengine.dir/strings.c.o.requires:
.PHONY : BASengine/CMakeFiles/BASengine.dir/strings.c.o.requires

BASengine/CMakeFiles/BASengine.dir/strings.c.o.provides: BASengine/CMakeFiles/BASengine.dir/strings.c.o.requires
	$(MAKE) -f BASengine/CMakeFiles/BASengine.dir/build.make BASengine/CMakeFiles/BASengine.dir/strings.c.o.provides.build
.PHONY : BASengine/CMakeFiles/BASengine.dir/strings.c.o.provides

BASengine/CMakeFiles/BASengine.dir/strings.c.o.provides.build: BASengine/CMakeFiles/BASengine.dir/strings.c.o

BASengine/CMakeFiles/BASengine.dir/math.c.o: BASengine/CMakeFiles/BASengine.dir/flags.make
BASengine/CMakeFiles/BASengine.dir/math.c.o: BASengine/math.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vroby/Progetti/sdlbasic/sdlbrt/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object BASengine/CMakeFiles/BASengine.dir/math.c.o"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/BASengine.dir/math.c.o   -c /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/math.c

BASengine/CMakeFiles/BASengine.dir/math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BASengine.dir/math.c.i"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/math.c > CMakeFiles/BASengine.dir/math.c.i

BASengine/CMakeFiles/BASengine.dir/math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BASengine.dir/math.c.s"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/math.c -o CMakeFiles/BASengine.dir/math.c.s

BASengine/CMakeFiles/BASengine.dir/math.c.o.requires:
.PHONY : BASengine/CMakeFiles/BASengine.dir/math.c.o.requires

BASengine/CMakeFiles/BASengine.dir/math.c.o.provides: BASengine/CMakeFiles/BASengine.dir/math.c.o.requires
	$(MAKE) -f BASengine/CMakeFiles/BASengine.dir/build.make BASengine/CMakeFiles/BASengine.dir/math.c.o.provides.build
.PHONY : BASengine/CMakeFiles/BASengine.dir/math.c.o.provides

BASengine/CMakeFiles/BASengine.dir/math.c.o.provides.build: BASengine/CMakeFiles/BASengine.dir/math.c.o

# Object files for target BASengine
BASengine_OBJECTS = \
"CMakeFiles/BASengine.dir/datafunction.c.o" \
"CMakeFiles/BASengine.dir/membank.c.o" \
"CMakeFiles/BASengine.dir/dir.c.o" \
"CMakeFiles/BASengine.dir/file.c.o" \
"CMakeFiles/BASengine.dir/strings.c.o" \
"CMakeFiles/BASengine.dir/math.c.o"

# External object files for target BASengine
BASengine_EXTERNAL_OBJECTS =

BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/datafunction.c.o
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/membank.c.o
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/dir.c.o
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/file.c.o
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/strings.c.o
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/math.c.o
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/build.make
BASengine/libBASengine.a: BASengine/CMakeFiles/BASengine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libBASengine.a"
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && $(CMAKE_COMMAND) -P CMakeFiles/BASengine.dir/cmake_clean_target.cmake
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BASengine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
BASengine/CMakeFiles/BASengine.dir/build: BASengine/libBASengine.a
.PHONY : BASengine/CMakeFiles/BASengine.dir/build

BASengine/CMakeFiles/BASengine.dir/requires: BASengine/CMakeFiles/BASengine.dir/datafunction.c.o.requires
BASengine/CMakeFiles/BASengine.dir/requires: BASengine/CMakeFiles/BASengine.dir/membank.c.o.requires
BASengine/CMakeFiles/BASengine.dir/requires: BASengine/CMakeFiles/BASengine.dir/dir.c.o.requires
BASengine/CMakeFiles/BASengine.dir/requires: BASengine/CMakeFiles/BASengine.dir/file.c.o.requires
BASengine/CMakeFiles/BASengine.dir/requires: BASengine/CMakeFiles/BASengine.dir/strings.c.o.requires
BASengine/CMakeFiles/BASengine.dir/requires: BASengine/CMakeFiles/BASengine.dir/math.c.o.requires
.PHONY : BASengine/CMakeFiles/BASengine.dir/requires

BASengine/CMakeFiles/BASengine.dir/clean:
	cd /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine && $(CMAKE_COMMAND) -P CMakeFiles/BASengine.dir/cmake_clean.cmake
.PHONY : BASengine/CMakeFiles/BASengine.dir/clean

BASengine/CMakeFiles/BASengine.dir/depend:
	cd /home/vroby/Progetti/sdlbasic/sdlbrt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vroby/Progetti/sdlbasic/sdlbrt /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine /home/vroby/Progetti/sdlbasic/sdlbrt /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine /home/vroby/Progetti/sdlbasic/sdlbrt/BASengine/CMakeFiles/BASengine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : BASengine/CMakeFiles/BASengine.dir/depend

