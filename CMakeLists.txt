cmake_minimum_required(VERSION 3.7)
project(ik)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-misleading-indentation")
set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    include_directories(D:\\tmp\\dlib)
    find_library(DLIB_LIBRARY dlib HINTS D:\\tmp\\dlib\\cmake-build-release\\dlib)

    set(LIBS imm32 winmm comctl32)
endif (WIN32)

if (UNIX)
    set(DLIB_LIBRARY dlib)
endif (UNIX)

set(LIBS ${DLIB_LIBRARY} ${LIBS})

set(SOURCE_FILES main.cpp world.cpp world.h drawables.h drawables.cpp updatable.h tentacle.cpp tentacle.h)
add_executable(ik ${SOURCE_FILES})
target_link_libraries(ik ${LIBS})
