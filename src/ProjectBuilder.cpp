#include <ProjectBuilder.h>
#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>
#include <fstream>
#include <Command.h>
#include <fmt/core.h>

namespace {
  template<typename... Args>
  void format(std::string_view file, std::string_view text, Args &&... args) {
    std::ofstream(file) << fmt::format(text, args...);
  }
}

ProjectBuilder ProjectBuilder::createProject(int argc, char **argv) {
  CLI::App utility("C++20 projects creator", "utility");
  std::string name, description;
  utility
    .add_option("-n,--name", name, "New project name")
    ->required();
  utility
    .add_option("-d,--description", description, "New project description")
    ->expected(1);
  try {
    utility.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    utility.exit(e);
  }
  auto directory = std::filesystem::current_path().append(name);
  std::filesystem::create_directory(directory);
  return ProjectBuilder(std::move(name), std::move(description), std::move(directory));
}

ProjectBuilder::ProjectBuilder(std::string name, std::string description, std::filesystem::path directory)
  : name(std::move(name)), description(std::move(description)), directory(std::move(directory)) {}

ProjectBuilder &ProjectBuilder::initRepository() {
  auto code = fmt::format("git init {}", name);
  Command::execute(code).orWarning("failed to initialize git repository");
  return *this;
}

ProjectBuilder &ProjectBuilder::createBuildConfiguration() {
  return *this;
}

ProjectBuilder &ProjectBuilder::createDocumentation() {
  auto readme = std::filesystem::path(directory).append("README.md");
  auto text = fmt::format(
    "## {}\n"
    "\n"
    "{}\n"
    "\n"
    " ### Как собирать?\n"
    "\n"
    "Нам понадобится система сборки [`cmake`](https://cmake.org/download) и менеджер\n"
    "библиотек [`vcpkg`](https://github.com/microsoft/vcpkg). Их легко можно установить пакетным менеджером, например `brew`.\n"
    "\n"
    "1. Устанавливаем фреймворк для тестирования:  \n"
    "   `vcpkg install` [`catch2`](https://github.com/catchorg/Catch2)\n"
    "1. Устанавливаем зависимость для парсинга аргументов командной строки:  \n"
    "   `vcpkg install` [`cli11`](https://github.com/CLIUtils/CLI11)\n"
    "1. Подготавливаем проект для сборки с использованием зависимостей `vcpkg`:  \n"
    "   ```cmake `vcpkg integrate install | tail -1 | cut -d \\\" -f2` -DCMAKE_BUILD_TYPE=Release -G \"Unix Makefiles\" -B cmake-build-release```  \n"
    "   На Windows вместо кода в кавычках, вручную подставьте параметр полученный вызовом `vcpkg integrate install`.\n"
    "1. Собираем проект и тесты:  \n"
    "   `cmake --build cmake-build-release --target all`  \n"
    "   После этого в директории `cmake-build-release` утилита появится под именем `{}`.  \n"
    "   Тесты можно выполнить запустив расположенный рядом файл `test`.\n"
    "\n"
    "### Сборка с использованием IDE?\n"
    "\n"
    "1. Устанавливаем фреймворк для тестирования:  \n"
    "   `vcpkg install catch2`\n"
    "1. Устанавливаем зависимость для парсинга аргументов командной строки:  \n"
    "   `vcpkg install cli11`\n"
    "1. Установите для `CMake options` результат исполнения команды `vcpkg integrate install`.\n"
    "1. Не забудьте выбрать релиз-конфигурацию. Дальше используйте обычный интерфейс сборки.\n"
    "\n"
    "### Соглашения насчет исходного кода?\n"
    "\n"
    "* Точка входа обязательно должна быть расположена в файле `Main.cpp` для корректной сборки.",
    name, description, name
  );
  std::ofstream(readme) << text;
  return *this;
}



