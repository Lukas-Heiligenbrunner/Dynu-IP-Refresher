# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/lukas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lukas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lukas/CLionProjects/iprefresher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lukas/CLionProjects/iprefresher

# Include any dependencies generated for this target.
include CMakeFiles/iprefresher.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/iprefresher.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/iprefresher.dir/flags.make

CMakeFiles/iprefresher.dir/main.cpp.o: CMakeFiles/iprefresher.dir/flags.make
CMakeFiles/iprefresher.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lukas/CLionProjects/iprefresher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/iprefresher.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/iprefresher.dir/main.cpp.o -c /home/lukas/CLionProjects/iprefresher/main.cpp

CMakeFiles/iprefresher.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/iprefresher.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lukas/CLionProjects/iprefresher/main.cpp > CMakeFiles/iprefresher.dir/main.cpp.i

CMakeFiles/iprefresher.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/iprefresher.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lukas/CLionProjects/iprefresher/main.cpp -o CMakeFiles/iprefresher.dir/main.cpp.s

CMakeFiles/iprefresher.dir/API.cpp.o: CMakeFiles/iprefresher.dir/flags.make
CMakeFiles/iprefresher.dir/API.cpp.o: API.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lukas/CLionProjects/iprefresher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/iprefresher.dir/API.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/iprefresher.dir/API.cpp.o -c /home/lukas/CLionProjects/iprefresher/API.cpp

CMakeFiles/iprefresher.dir/API.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/iprefresher.dir/API.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lukas/CLionProjects/iprefresher/API.cpp > CMakeFiles/iprefresher.dir/API.cpp.i

CMakeFiles/iprefresher.dir/API.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/iprefresher.dir/API.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lukas/CLionProjects/iprefresher/API.cpp -o CMakeFiles/iprefresher.dir/API.cpp.s

# Object files for target iprefresher
iprefresher_OBJECTS = \
"CMakeFiles/iprefresher.dir/main.cpp.o" \
"CMakeFiles/iprefresher.dir/API.cpp.o"

# External object files for target iprefresher
iprefresher_EXTERNAL_OBJECTS =

iprefresher: CMakeFiles/iprefresher.dir/main.cpp.o
iprefresher: CMakeFiles/iprefresher.dir/API.cpp.o
iprefresher: CMakeFiles/iprefresher.dir/build.make
iprefresher: /usr/lib/x86_64-linux-gnu/libcurl.so
iprefresher: CMakeFiles/iprefresher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lukas/CLionProjects/iprefresher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable iprefresher"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iprefresher.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/iprefresher.dir/build: iprefresher

.PHONY : CMakeFiles/iprefresher.dir/build

CMakeFiles/iprefresher.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/iprefresher.dir/cmake_clean.cmake
.PHONY : CMakeFiles/iprefresher.dir/clean

CMakeFiles/iprefresher.dir/depend:
	cd /home/lukas/CLionProjects/iprefresher && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lukas/CLionProjects/iprefresher /home/lukas/CLionProjects/iprefresher /home/lukas/CLionProjects/iprefresher /home/lukas/CLionProjects/iprefresher /home/lukas/CLionProjects/iprefresher/CMakeFiles/iprefresher.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/iprefresher.dir/depend

