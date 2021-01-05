#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <fmt/core.h>
#include "../src/Project.h"

TEST_CASE("Tool skeleton creation") {

  auto project = Project("ExampleTool", "Little tool for example").createToolSkeleton();

  auto textOf = [&project](const std::filesystem::path &path) -> std::string {
    std::ifstream file(project.directory / path);
    return {(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
  };

  REQUIRE(
    textOf("src/Main.cpp") ==
    "#include <CLI/App.hpp>\n"
    "#include <CLI/Formatter.hpp>\n"
    "#include <CLI/Config.hpp>\n"
    "#include <fmt/core.h>\n"
    "#include <fmt/color.h>\n"
    "\n"
    "int main(int argc, char **argv) {\n"
    "  CLI::App utility(\"Little tool for example\", \"ExampleTool\");\n"
    "  CLI11_PARSE(utility, argc, argv)\n"
    "  fmt::print(\n"
    "    fg(color::dark_orange),\n"
    "    \"ExampleTool works!\"\n"
    "  );\n"
    "}"
  );

  REQUIRE(
    textOf("test/Main.cpp") ==
    "#define CATCH_CONFIG_MAIN\n"
    "\n"
    "#include <catch.hpp>\n"
    "\n"
    "TEST_CASE(\"test\") {\n"
    "  REQUIRE(1 == 1);\n"
    "}"
  );

  REQUIRE(
    textOf(".editorconfig") ==
    "[*.{c++,cc,cpp,cxx,h,h++,hh,hpp,hxx,inl,ipp,tlh,tli}]\n"
    "max_line_length = 120\n"
    "indent_size = 2\n"
    "continuation_indent_size = 2"
  );

  REQUIRE(
    textOf(".gitignore") ==
    "# Prerequisites\n"
    "*.d\n"
    "\n"
    "# Compiled Object files\n"
    "*.slo\n"
    "*.lo\n"
    "*.o\n"
    "*.obj\n"
    "\n"
    "# Precompiled Headers\n"
    "*.gch\n"
    "*.pch\n"
    "\n"
    "# Compiled Dynamic libraries\n"
    "*.so\n"
    "*.dylib\n"
    "*.dll\n"
    "\n"
    "# Fortran module files\n"
    "*.mod\n"
    "*.smod\n"
    "\n"
    "# Compiled Static libraries\n"
    "*.lai\n"
    "*.la\n"
    "*.a\n"
    "*.lib\n"
    "\n"
    "# Executables\n"
    "*.exe\n"
    "*.out\n"
    "*.app\n"
    "\n"
    "cmake-build-release\n"
    ".idea\n"
    ".DS_Store\n"
    ".editorconfig"
  );

  REQUIRE(
    textOf("CMakeLists.txt") ==
    "cmake_minimum_required(VERSION 3.17)\n"
    "set(CMAKE_CXX_STANDARD 20)\n"
    "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
    "\n"
    "project(ExampleTool)\n"
    "file(GLOB proj_sources src/*.cpp)\n"
    "add_executable(ExampleTool ${proj_sources})\n"
    "find_package(fmt CONFIG REQUIRED)\n"
    "target_link_libraries(proj PRIVATE fmt::fmt fmt::fmt-header-only)\n"
    "find_package(CLI11 CONFIG REQUIRED)\n"
    "target_link_libraries(proj PRIVATE CLI11::CLI11)\n"
    "\n"
    "project(test)\n"
    "#[[Changing the entry point for tests]]\n"
    "list(FILTER proj_sources EXCLUDE REGEX \".*Main.cpp$\")\n"
    "file(GLOB test_sources test/*.cpp)\n"
    "add_executable(test ${proj_sources} ${test_sources})\n"
    "find_package(Catch2 CONFIG REQUIRED)\n"
    "target_link_libraries(test PRIVATE Catch2::Catch2)\n"
    "target_link_libraries(test PRIVATE CLI11::CLI11)\n"
    "target_link_libraries(test PRIVATE fmt::fmt fmt::fmt-header-only)"
  );

  REQUIRE(
    textOf("README.md") ==
    "## ExampleTool\n"
    "\n"
    "Little tool for example\n"
    "\n"
    "### How to use `ExampleTool`?\n"
    "\n"
    "```shell\n"
    "ExampleTool\n"
    "```\n"
    "\n"
    "### How to build `ExampleTool` source code manually?\n"
    "\n"
    "We need [`cmake`](https://cmake.org/download) build system and [`vcpkg`](https://github.com/microsoft/vcpkg) manager\n"
    "libraries. It's easy to install with system package manager, `brew` for example.\n"
    "\n"
    "1. Install the dependencies:  \n"
    "   `vcpkg install` [`catch2`](https://github.com/catchorg/Catch2)  \n"
    "   `vcpkg install` [`cli11`](https://github.com/CLIUtils/CLI11)  \n"
    "   `vcpkg install` [`fmt`](https://github.com/fmtlib/fmt)\n"
    "1. If you are using an IDE, you can stop at this step simply by setting `CMake options` as the result\n"
    "   of `vcpkg integrate install` command.\n"
    "1. Prepare the directory for building using the dependencies `vcpkg`:  \n"
    "   ```cmake `vcpkg integrate install | tail -1 | cut -d \\\" -f2` -DCMAKE_BUILD_TYPE=Release -G \"Unix Makefiles\" -B cmake-build-release```  \n"
    "   On Windows, instead of the code in ``` `` ``` quotes, manually substitute the parameter obtained by\n"
    "   calling `vcpkg integrate install`.\n"
    "1. Putting together the directory and tests:\n"
    "   `cmake --build cmake-build-release --target all`  \n"
    "   After that, the main self-executable utility will appear in the `cmake-build-release` directory under the name `ExampleTool`\n"
    "   . The tests can be run by launching the `test` file located nearby."
  );

  std::filesystem::remove_all(project.directory);
}