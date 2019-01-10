cmake_minimum_required(VERSION 3.12)

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory(boost-cmake)

add_executable(re_test main.cpp)

target_link_libraries(re_test PUBLIC Boost::boost Boost::regex)
