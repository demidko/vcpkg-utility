## coexp

Кроссплатформенная утилита для быстрого разворачивания `C++20` проектов одной командой. Утилита создаёт
cmake-конфигурацию проекта и тестов, точки входа, подтягивает `vcpkg` и минимально неообходимые зависимости для утилит
командной строки, добавляет `README` и завершается все это созданием скрипта сборки проекта в один клик. Таким образом,
созданные проекты поддерживаются в `CLion`, `Visual Studio`, `VS Code` и могут быть легко дополнены любыми зависимостями
из `vcpkg`.

### Мотивация и цели?

Как только в голове возникает новая идея C++ проекта, хотелось бы просто задавать его имя, краткое описание, и сразу же
начинать писать код, собирая затем релизы одним кликом/командой и не потеряв при этом в производительности итоговой
сборки.  
Однако в реальности приходится копипастить или создавать вручную каждый раз типовые `CMakeLists.txt`, `README.md`,
структуру папок, либо допиливать созданный по шаблону IDE проект. Поэтому человечеству просто необходим инструмент для
быстрого разворачивания новых C++20 проектов.

### Преимущества и отличия от аналогов?

Утилита замахивается на универсальный способ создания проектов, по аналогии с `dotnet` для C# и `cargo` для Rust. Сейчас
CMake проект развернуть можно используя интерфейс IDE, либо вручную создав структуру и конфигурацию. Даже
если [ваша любимая] IDE кроссплатформенная, она все равно слишком тяжелая зависимость чтобы тащить ее за собой для
разворачивания проектов, ведь любимые IDE у всех разные, а кто-то вообще vim использует. Поэтому небольшая
кроссплатформенная утилита генерирующая проекты поддерживаемые любой IDE будет весьма кстати.

### Как установить?

[ссылка будет здесь]

### Как запускать?

`coexp -n project_name -d 'description of your project'`

### TODO

1. Перевести документацию проекта на английский.
1. Добавить утилиту в репозитории популярных менеджеров зависимостей.
1. Написать статьи на хабр, reddit, hackernews.
1. Добавить больше типов проектов.
1. Бесконечный цикл багфиксов.

### Как собирать исходный код утилиты?

Нам понадобится система сборки [`cmake`](https://cmake.org/download) и менеджер
библиотек [`vcpkg`](https://github.com/microsoft/vcpkg). Их легко можно установить пакетным менеджером, например `brew`.

1. Устанавливаем фреймворк для тестирования:  
   `vcpkg install` [`catch2`](https://github.com/catchorg/Catch2)
1. Устанавливаем зависимость для парсинга аргументов командной строки:  
   `vcpkg install` [`cli11`](https://github.com/CLIUtils/CLI11)
1. Подготавливаем проект для сборки с использованием зависимостей `vcpkg`:  
   ```cmake `vcpkg integrate install | tail -1 | cut -d \" -f2` -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B cmake-build-release```  
   На Windows вместо кода в кавычках, вручную подставьте параметр полученный вызовом `vcpkg integrate install`.
1. Собираем проект и тесты:  
   `cmake --build cmake-build-release --target all`  
   После этого в директории `cmake-build-release` основная self-executable утилита появится под именем `coexp`.  
   Тесты можно выполнить запустив расположенный рядом файл `test`.

### Сборка утилиты с использованием IDE?

1. Устанавливаем фреймворк для тестирования:  
   `vcpkg install catch2`
1. Устанавливаем зависимость для парсинга аргументов командной строки:  
   `vcpkg install cli11`
1. Установите для `CMake options` результат исполнения команды `vcpkg integrate install`.
1. Не забудьте выбрать релиз-конфигурацию. Дальше используйте обычный интерфейс сборки.

### Соглашения насчет исходного кода утилиты?

* Используем современную передачу параметров [по значению](https://habr.com/ru/post/460955/), а не по ссылке.
* В релизную сборку попадает только результат компиляции `*.cpp` файлов в папке `src`.
* Папка `src` содержит `*.cpp` и `*.h` файлы проекта совместно.
* Папка `test` содержит `*.cpp` и `*.h` файлы тестов проекта совместно.
* Каждый `*.h` файл должен определять в глобальном пространстве имен только одну сущность, название которой должно
  совпадать с именем файла.
* Содержимое `*.cpp` файлов не задекларированное в `*.h` файле должно быть защищено от `external linkage` из других
  едениц компиляции путём добавления в анонимное пространство имён или же добавления ключевого слова `static`.
