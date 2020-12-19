cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[Собираем основную утилиту]]
project(coexp)
#[[Добавляем в сборку исходники]]
file(GLOB src src/*.cpp)
add_executable(coexp ${src})
#[[Указываем компилятору путь поиска своих h файлов]]
include_directories(src)
#[[Берем у vcpkg зависимость для парсинга аргументов командной строки]]
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(coexp PRIVATE CLI11::CLI11)

#[[Создаем тестовый проект]]
project(test)
#[[Подменяем для тестов точку входа]]
list(FILTER src EXCLUDE REGEX ".*main.cpp$")
#[[Добавляем исходники тестов]]
file(GLOB test_src test/*.cpp)
add_executable(test ${src} ${test_src})
#[[Указываем компилятору путь поиска тестовых h файлов]]
include_directories(test)
#[[Берём у vcpkg библиотеку для тестирования]]
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test PRIVATE Catch2::Catch2)



