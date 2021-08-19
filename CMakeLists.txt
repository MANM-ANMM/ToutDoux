cmake_minimum_required(VERSION 3.21)

if (${TEST})
	SET(ProjetName ToutDouxTest)
else()
	SET(ProjetName ToutDoux)
endif()

project(${ProjetName} VERSION 1.0)

if (${TEST})
	file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
	add_executable(${ProjetName} ${MY_SOURCES})
else()
	file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
	add_executable(${ProjetName} ${MY_SOURCES})
endif()

if(MSVC)
  target_compile_options(${ProjetName} PRIVATE /W4 /WX)
else()
  target_compile_options(${ProjetName} PRIVATE -Wall -Wextra -pedantic -Wconversion --diagnostics-color=always -lgdi32 -lcomdlg32 -DNANA_FILESYSTEM_FORCE)
endif()

target_include_directories(${ProjetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include D:/msys64/mingw64/include)
target_compile_features(${ProjetName} PRIVATE cxx_std_20)
target_link_libraries(${ProjetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libnana.a)
