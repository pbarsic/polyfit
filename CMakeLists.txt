cmake_minimum_required(VERSION 3.10)

project(opencv_demo)

project(polyfit_demo VERSION 3.14)
project(simplecv VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(polyfit_demo demo.cpp)
add_executable(simplecv simpleCV.cpp)

add_subdirectory(math)

find_package(PkgConfig REQUIRED)

pkg_check_modules(OPENCV REQUIRED opencv)

target_link_libraries(polyfit_demo Math ${OPENCV_LIBRARIES})
target_include_directories(polyfit_demo PUBLIC ${OPENCV_INCLUDE_DIRS} math)
target_compile_options(polyfit_demo PUBLIC ${OPENCV_CFLAGS_OTHER})

target_link_libraries(simplecv ${OPENCV_LIBRARIES})
target_include_directories(simplecv PUBLIC ${OPENCV_INCLUDE_DIRS})
target_compile_options(simplecv PUBLIC ${OPENCV_CFLAGS_OTHER})

