# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion-2019.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ziyan/Dropbox/mylibrary/dpdk_tools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mynetwork_library.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mynetwork_library.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mynetwork_library.dir/flags.make

CMakeFiles/mynetwork_library.dir/main.c.o: CMakeFiles/mynetwork_library.dir/flags.make
CMakeFiles/mynetwork_library.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mynetwork_library.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mynetwork_library.dir/main.c.o   -c /home/ziyan/Dropbox/mylibrary/dpdk_tools/main.c

CMakeFiles/mynetwork_library.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mynetwork_library.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ziyan/Dropbox/mylibrary/dpdk_tools/main.c > CMakeFiles/mynetwork_library.dir/main.c.i

CMakeFiles/mynetwork_library.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mynetwork_library.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ziyan/Dropbox/mylibrary/dpdk_tools/main.c -o CMakeFiles/mynetwork_library.dir/main.c.s

CMakeFiles/mynetwork_library.dir/lib/ip.c.o: CMakeFiles/mynetwork_library.dir/flags.make
CMakeFiles/mynetwork_library.dir/lib/ip.c.o: ../lib/ip.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mynetwork_library.dir/lib/ip.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mynetwork_library.dir/lib/ip.c.o   -c /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/ip.c

CMakeFiles/mynetwork_library.dir/lib/ip.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mynetwork_library.dir/lib/ip.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/ip.c > CMakeFiles/mynetwork_library.dir/lib/ip.c.i

CMakeFiles/mynetwork_library.dir/lib/ip.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mynetwork_library.dir/lib/ip.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/ip.c -o CMakeFiles/mynetwork_library.dir/lib/ip.c.s

CMakeFiles/mynetwork_library.dir/lib/mac.c.o: CMakeFiles/mynetwork_library.dir/flags.make
CMakeFiles/mynetwork_library.dir/lib/mac.c.o: ../lib/mac.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mynetwork_library.dir/lib/mac.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mynetwork_library.dir/lib/mac.c.o   -c /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/mac.c

CMakeFiles/mynetwork_library.dir/lib/mac.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mynetwork_library.dir/lib/mac.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/mac.c > CMakeFiles/mynetwork_library.dir/lib/mac.c.i

CMakeFiles/mynetwork_library.dir/lib/mac.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mynetwork_library.dir/lib/mac.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/mac.c -o CMakeFiles/mynetwork_library.dir/lib/mac.c.s

CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.o: CMakeFiles/mynetwork_library.dir/flags.make
CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.o: ../lib/dpdk_init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.o   -c /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/dpdk_init.c

CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/dpdk_init.c > CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.i

CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/dpdk_init.c -o CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.s

# Object files for target mynetwork_library
mynetwork_library_OBJECTS = \
"CMakeFiles/mynetwork_library.dir/main.c.o" \
"CMakeFiles/mynetwork_library.dir/lib/ip.c.o" \
"CMakeFiles/mynetwork_library.dir/lib/mac.c.o" \
"CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.o"

# External object files for target mynetwork_library
mynetwork_library_EXTERNAL_OBJECTS =

mynetwork_library: CMakeFiles/mynetwork_library.dir/main.c.o
mynetwork_library: CMakeFiles/mynetwork_library.dir/lib/ip.c.o
mynetwork_library: CMakeFiles/mynetwork_library.dir/lib/mac.c.o
mynetwork_library: CMakeFiles/mynetwork_library.dir/lib/dpdk_init.c.o
mynetwork_library: CMakeFiles/mynetwork_library.dir/build.make
mynetwork_library: CMakeFiles/mynetwork_library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable mynetwork_library"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mynetwork_library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mynetwork_library.dir/build: mynetwork_library

.PHONY : CMakeFiles/mynetwork_library.dir/build

CMakeFiles/mynetwork_library.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mynetwork_library.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mynetwork_library.dir/clean

CMakeFiles/mynetwork_library.dir/depend:
	cd /home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ziyan/Dropbox/mylibrary/dpdk_tools /home/ziyan/Dropbox/mylibrary/dpdk_tools /home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug /home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug /home/ziyan/Dropbox/mylibrary/dpdk_tools/cmake-build-debug/CMakeFiles/mynetwork_library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mynetwork_library.dir/depend

