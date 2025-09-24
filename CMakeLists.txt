cmake_minimum_required(VERSION 3.25)
project(template_metaprogramming_with_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Apple libc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++")

add_subdirectory(chapter01)
add_subdirectory(chapter02)

#add_executable(template_metaprogramming_with_cpp main.cpp)
