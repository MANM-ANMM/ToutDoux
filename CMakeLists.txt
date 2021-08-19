cmake_minimum_required(VERSION 3.21)
SET(ProjetName ToutDoux)

project(${ProjetName} VERSION 1.0)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${ProjetName} ${MY_SOURCES})

if(MSVC)
  target_compile_options(${ProjetName} PRIVATE /W4 /WX)
else()
  target_compile_options(${ProjetName} PRIVATE -Wall -Wextra -pedantic -Wconversion --diagnostics-color=always)
endif()

target_include_directories(${ProjetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(${ProjetName} PRIVATE cxx_std_20)
