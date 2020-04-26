set(projectName "Mario")
project (${projectName})

cmake_minimum_required (VERSION 3.6)

enable_testing()
include(cppcheck.cmake)

option(STATIC_LINKING "Link statically all dependenices into binary" ON)

if (STATIC_LINKING)
    message(STATUS "Configured to link static  libraries")

    set(SDL2_DIR .) #location of sdl2 cmake file (taken from this project)
    set(SDL2-MIXER_DIR .) #location of sdl2-mixer cmake file (taken from this project)

    if(WIN32)
        set(SDL2_PATH "C:/libs/SDL2-2.0.12")
        set(SDL2-MIXER_PATH "C:/libs/SDL2_mixer-2.0.4")
    else(WIN32)
        set(SDL2_PATH "usr/libs/SDL2")
        set(SDL2-MIXER_PATH "usr/libs/SDL2_mixer")
    endif(WIN32)

endif(STATIC_LINKING)

find_package(SDL2 REQUIRED)
find_package(SDL2-MIXER REQUIRED)
find_package(threads)

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
                    ${SDL2_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIRS}/SDL2
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    src
                    libs)

add_definitions(-std=c++17)
add_definitions(-O3)

add_subdirectory(src)
add_subdirectory(libs)

add_executable(${projectName} main.cpp)

if (STATIC_LINKING)
    if(WIN32)
        set(SDL2_STATIC_LINKING_LIBS
            -lwinmm
            -limm32
            -lversion
            -lsetupapi
            )
    else(WIN32)
        set(SDL2_STATIC_LINKING_LIBS)
    endif(WIN32)

    set(COMMON_STATIC_LINKING_LIBS
        -static
        -static-libgcc
        -static-libstdc++)
endif(STATIC_LINKING)

target_link_libraries(${projectName}
    game_core
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_STATIC_LINKING_LIBS}
    ${COMMON_STATIC_LINKING_LIBS} externalLibs)

set (CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")

message(STATUS "Install path:" ${INSTALL_DIR})
set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX})

install (TARGETS ${projectName} DESTINATION ${INSTALL_DIR})
install (DIRECTORY img/ DESTINATION ${INSTALL_DIR}/img)
install (DIRECTORY levels/ DESTINATION ${INSTALL_DIR}/levels)
install (DIRECTORY audio/ DESTINATION ${INSTALL_DIR}/audio)
