cmake_minimum_required (VERSION 3.00...3.31)
project(GLCanvas VERSION 1.0
              LANGUAGES CXX)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
# https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (src_dir "${PROJECT_SOURCE_DIR}/GLCanvas")
set (vendor_dir "${PROJECT_SOURCE_DIR}/vendor")
set (glbox_dir "${PROJECT_SOURCE_DIR}/GLBox")

file(GLOB_RECURSE src_files ${src_dir}/*.cpp ${src_dir}/*.h)

add_subdirectory(${glbox_dir})
add_executable(${PROJECT_NAME} ${src_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${src_dir} ${glbox_dir} ${vendor_dir} ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} GLBox)
