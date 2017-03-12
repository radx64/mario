set(projectName "Mario")
cmake_minimum_required (VERSION 2.6)
project (${projectName})

enable_testing()

include(cppcheck.cmake)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
					src
                    libs)

add_definitions(-std=c++11)
add_definitions(-O3)

add_subdirectory(src)
add_subdirectory(libs)

add_executable(${projectName} main.cpp)

target_link_libraries(${projectName} game_core SDL2 SDL2_mixer externalLibs)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
