cmake_minimum_required(VERSION 3.21)

SET(ProjetName ToutDoux)
SET(TestTargetName ToutDouxTest)


project(${ProjetName} VERSION 1.0)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

file(GLOB_RECURSE MY_TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/entrypoints/tests/*.cpp)
add_executable(${TestTargetName} ${MY_SOURCES} ${MY_TEST_SOURCES})

file(GLOB_RECURSE MY_MAIN_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/entrypoints/main/*.cpp)
add_executable(${ProjetName} ${MY_SOURCES} ${MY_MAIN_SOURCES})

SET(WarningGCC -Wall -Wextra -pedantic -Wconversion)
target_compile_options(${ProjetName} PRIVATE ${WarningGCC} -Og -fdiagnostics-color=always -DNANA_FILESYSTEM_FORCE)
target_compile_options(${TestTargetName} PRIVATE ${WarningGCC} -fdiagnostics-color=always -DNANA_FILESYSTEM_FORCE)


target_include_directories(${ProjetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(${ProjetName} PRIVATE cxx_std_20)
target_link_libraries(${ProjetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libnana.a)
#D:/msys64/mingw64/include
target_include_directories(${TestTargetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(${TestTargetName} PRIVATE cxx_std_20)
target_link_libraries(${TestTargetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libnana.a)
