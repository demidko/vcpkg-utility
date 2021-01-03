cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(proj)
file(GLOB proj_sources src/*.cpp)
add_executable(proj ${proj_sources})
find_package(fmt CONFIG REQUIRED)
target_link_libraries(proj PRIVATE fmt::fmt fmt::fmt-header-only)
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(proj PRIVATE CLI11::CLI11)

project(test)
#[[Changing the entry point for tests]]
list(FILTER proj_sources EXCLUDE REGEX ".*Main.cpp$")
file(GLOB test_sources test/*.cpp)
add_executable(test ${proj_sources} ${test_sources})
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test PRIVATE Catch2::Catch2)
target_link_libraries(test PRIVATE CLI11::CLI11)
target_link_libraries(test PRIVATE fmt::fmt fmt::fmt-header-only)



