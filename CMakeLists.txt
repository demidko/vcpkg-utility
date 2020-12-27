cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[Создаем проект утилиты]]
project(proj)
#[[Добавляем в сборку исходники]]
file(GLOB proj_src src/*.cpp)
add_executable(proj ${proj_src})
#[[Указываем компилятору путь поиска h файлов проекта]]
include_directories(src)
#[[Берем у vcpkg зависимость для парсинга аргументов командной строки]]
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(proj PRIVATE CLI11::CLI11)
#[[Берем у vcpkg зависимость для форматирования]]
find_package(fmt CONFIG REQUIRED)
target_link_libraries(proj PRIVATE fmt::fmt fmt::fmt-header-only)

#[[Создаем проект тестов]]
project(test)
#[[Подменяем для тестов точку входа]]
list(FILTER proj_src EXCLUDE REGEX ".*Main.cpp$")
#[[Добавляем исходники тестов]]
file(GLOB test_src test/*.cpp)
add_executable(test ${proj_src} ${test_src})
#[[Указываем компилятору путь поиска тестовых h файлов]]
include_directories(test)
#[[Берём у vcpkg библиотеку для тестирования]]
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test PRIVATE Catch2::Catch2)
#[[Добавляем в тестовый проект все зависимости основного]]
target_link_libraries(test PRIVATE CLI11::CLI11)
target_link_libraries(test PRIVATE fmt::fmt fmt::fmt-header-only)



