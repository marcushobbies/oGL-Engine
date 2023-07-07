cmake_minimum_required(VERSION 3.0.0)
cmake_policy(VERSION 3.0)

project(oGL VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

link_directories(${CMAKE_SOURCE_DIR}/include)


find_package(glfw3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
find_package(X11 REQUIRED)


set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

set(SOURCES main.cpp ${CMAKE_SOURCE_DIR}/include)

#CPP Files
set(SOURCE_FILES main.cpp)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 

target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARY})

#NOTE: Assets must still be manually placed in the "assets" folder located adjacent to the binary


