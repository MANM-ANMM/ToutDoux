# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = D:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = D:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Data\Document\Cpp\ToutDoux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Data\Document\Cpp\ToutDoux\bin

# Include any dependencies generated for this target.
include CMakeFiles/ToutDouxTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ToutDouxTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ToutDouxTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ToutDouxTest.dir/flags.make

CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj: CMakeFiles/ToutDouxTest.dir/flags.make
CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj: CMakeFiles/ToutDouxTest.dir/includes_CXX.rsp
CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj: ../source/modele/ToutDoux.cpp
CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj: CMakeFiles/ToutDouxTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Data\Document\Cpp\ToutDoux\bin\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj -MF CMakeFiles\ToutDouxTest.dir\source\modele\ToutDoux.cpp.obj.d -o CMakeFiles\ToutDouxTest.dir\source\modele\ToutDoux.cpp.obj -c D:\Data\Document\Cpp\ToutDoux\source\modele\ToutDoux.cpp

CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.i"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Data\Document\Cpp\ToutDoux\source\modele\ToutDoux.cpp > CMakeFiles\ToutDouxTest.dir\source\modele\ToutDoux.cpp.i

CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.s"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Data\Document\Cpp\ToutDoux\source\modele\ToutDoux.cpp -o CMakeFiles\ToutDouxTest.dir\source\modele\ToutDoux.cpp.s

CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj: CMakeFiles/ToutDouxTest.dir/flags.make
CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj: CMakeFiles/ToutDouxTest.dir/includes_CXX.rsp
CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj: ../source/vueOrdi1/mainPage.cpp
CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj: CMakeFiles/ToutDouxTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Data\Document\Cpp\ToutDoux\bin\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj -MF CMakeFiles\ToutDouxTest.dir\source\vueOrdi1\mainPage.cpp.obj.d -o CMakeFiles\ToutDouxTest.dir\source\vueOrdi1\mainPage.cpp.obj -c D:\Data\Document\Cpp\ToutDoux\source\vueOrdi1\mainPage.cpp

CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.i"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Data\Document\Cpp\ToutDoux\source\vueOrdi1\mainPage.cpp > CMakeFiles\ToutDouxTest.dir\source\vueOrdi1\mainPage.cpp.i

CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.s"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Data\Document\Cpp\ToutDoux\source\vueOrdi1\mainPage.cpp -o CMakeFiles\ToutDouxTest.dir\source\vueOrdi1\mainPage.cpp.s

CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj: CMakeFiles/ToutDouxTest.dir/flags.make
CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj: CMakeFiles/ToutDouxTest.dir/includes_CXX.rsp
CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj: ../entrypoints/tests/testProjet.cpp
CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj: CMakeFiles/ToutDouxTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Data\Document\Cpp\ToutDoux\bin\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj -MF CMakeFiles\ToutDouxTest.dir\entrypoints\tests\testProjet.cpp.obj.d -o CMakeFiles\ToutDouxTest.dir\entrypoints\tests\testProjet.cpp.obj -c D:\Data\Document\Cpp\ToutDoux\entrypoints\tests\testProjet.cpp

CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.i"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Data\Document\Cpp\ToutDoux\entrypoints\tests\testProjet.cpp > CMakeFiles\ToutDouxTest.dir\entrypoints\tests\testProjet.cpp.i

CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.s"
	D:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Data\Document\Cpp\ToutDoux\entrypoints\tests\testProjet.cpp -o CMakeFiles\ToutDouxTest.dir\entrypoints\tests\testProjet.cpp.s

# Object files for target ToutDouxTest
ToutDouxTest_OBJECTS = \
"CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj" \
"CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj" \
"CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj"

# External object files for target ToutDouxTest
ToutDouxTest_EXTERNAL_OBJECTS =

ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/source/modele/ToutDoux.cpp.obj
ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/source/vueOrdi1/mainPage.cpp.obj
ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/entrypoints/tests/testProjet.cpp.obj
ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/build.make
ToutDouxTest.exe: ../lib/libnana.a
ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/linklibs.rsp
ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/objects1.rsp
ToutDouxTest.exe: CMakeFiles/ToutDouxTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Data\Document\Cpp\ToutDoux\bin\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ToutDouxTest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ToutDouxTest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ToutDouxTest.dir/build: ToutDouxTest.exe
.PHONY : CMakeFiles/ToutDouxTest.dir/build

CMakeFiles/ToutDouxTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ToutDouxTest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ToutDouxTest.dir/clean

CMakeFiles/ToutDouxTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Data\Document\Cpp\ToutDoux D:\Data\Document\Cpp\ToutDoux D:\Data\Document\Cpp\ToutDoux\bin D:\Data\Document\Cpp\ToutDoux\bin D:\Data\Document\Cpp\ToutDoux\bin\CMakeFiles\ToutDouxTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ToutDouxTest.dir/depend

