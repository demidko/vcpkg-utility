cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[Находим зависимости с помощью vcpkg]]
find_package(CLI11 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

#[[Создаем проект утилиты]]
project(proj)
file(GLOB proj_src src/*.cpp)
add_executable(proj ${proj_src})
include_directories(src)
target_link_libraries(proj PRIVATE CLI11::CLI11)
target_link_libraries(proj PRIVATE fmt::fmt fmt::fmt-header-only)

#[[Создаем проект тестов]]
project(test)
#[[Подменяем для тестов точку входа]]
list(FILTER proj_src EXCLUDE REGEX ".*Main.cpp$")
file(GLOB test_src test/*.cpp)
add_executable(test ${proj_src} ${test_src})
include_directories(test)
target_link_libraries(test PRIVATE Catch2::Catch2)
target_link_libraries(test PRIVATE CLI11::CLI11)
target_link_libraries(test PRIVATE fmt::fmt fmt::fmt-header-only)



