# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.21
cmake_policy(SET CMP0009 NEW)

# MY_MAIN_SOURCES at CMakeLists.txt:13 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/Data/Document/Cpp/ToutDoux/entrypoints/main/*.cpp")
set(OLD_GLOB
  "D:/Data/Document/Cpp/ToutDoux/entrypoints/main/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/Data/Document/Cpp/ToutDoux/bin/CMakeFiles/cmake.verify_globs")
endif()

# MY_TEST_SOURCES at CMakeLists.txt:10 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/Data/Document/Cpp/ToutDoux/entrypoints/tests/*.cpp")
set(OLD_GLOB
  "D:/Data/Document/Cpp/ToutDoux/entrypoints/tests/testProjet.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/Data/Document/Cpp/ToutDoux/bin/CMakeFiles/cmake.verify_globs")
endif()

# MY_SOURCES at CMakeLists.txt:8 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/Data/Document/Cpp/ToutDoux/source/*.cpp")
set(OLD_GLOB
  "D:/Data/Document/Cpp/ToutDoux/source/modele/ToutDoux.cpp"
  "D:/Data/Document/Cpp/ToutDoux/source/vueOrdi1/mainPage.cpp"
  "D:/Data/Document/Cpp/ToutDoux/source/vueOrdi1/scrollPanel.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/Data/Document/Cpp/ToutDoux/bin/CMakeFiles/cmake.verify_globs")
endif()
