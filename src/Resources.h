#include <string_view>

namespace Resources {

  constexpr inline std::string_view EDITORCONFIG_TEXT =
    "[*.{c++,cc,cpp,cxx,h,h++,hh,hpp,hxx,inl,ipp,tlh,tli}]\n"
    "max_line_length = 120\n"
    "indent_size = 2\n"
    "continuation_indent_size = 2";

  constexpr inline std::string_view CMAKE_CONFIG_FOR_TOOL_TEXT =
    "cmake_minimum_required(VERSION 3.17)\n"
    "set(CMAKE_CXX_STANDARD 20)\n"
    "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
    "\n"
    "project({0})\n"
    "file(GLOB proj_sources src/*.cpp)\n"
    "add_executable({0} $\{proj_sources\})\n"
    "find_package(fmt CONFIG REQUIRED)\n"
    "target_link_libraries(proj PRIVATE fmt::fmt fmt::fmt-header-only)\n"
    "find_package(CLI11 CONFIG REQUIRED)\n"
    "target_link_libraries(proj PRIVATE CLI11::CLI11)\n"
    "\n"
    "project(test)\n"
    "#[[Changing the entry point for tests]]\n"
    "list(FILTER proj_sources EXCLUDE REGEX \".*Main.cpp$\")\n"
    "file(GLOB test_sources test/*.cpp)\n"
    "add_executable(test $\{proj_sources\} $\{test_sources\})\n"
    "find_package(Catch2 CONFIG REQUIRED)\n"
    "target_link_libraries(test PRIVATE Catch2::Catch2)\n"
    "target_link_libraries(test PRIVATE CLI11::CLI11)\n"
    "target_link_libraries(test PRIVATE fmt::fmt fmt::fmt-header-only)";

  constexpr inline std::string_view README_TEXT =
    "## {0}\n"
    "\n"
    "{1}\n"
    "\n"
    "### How to use\n"
    "\n"
    "```shell\n"
    "{0}\n"
    "```\n"
    "\n"
    "### How to build\n"
    "\n"
    "We need a build system [`cmake`](https://cmake.org/download) and a manager\n"
    "libraries [`vcpkg`](https://github.com/microsoft/vcpkg). They can be easily installed with a package manager such\n"
    "as `brew`.\n"
    "\n"
    "1. Install the dependencies:\n"
    "   `vcpkg install` [`catch2`](https://github.com/catchorg/Catch2)\n"
    "   `vcpkg install` [`cli11`](https://github.com/CLIUtils/CLI11)\n"
    "   `vcpkg install` [`fmt`](https://github.com/fmtlib/fmt)\n"
    "1. If you are using an IDE, you can stop at this step simply by setting `CMake options` as the result\n"
    "   of `vcpkg integrate install` command.  \n"
    "   Without IDE prepare the directory for building using the dependencies `vcpkg`:  \n"
    "   ```cmake `vcpkg integrate install | tail -1 | cut -d \\\" -f2` -DCMAKE_BUILD_TYPE=Release -G \"Unix Makefiles\" -B cmake-build-release```  \n"
    "   On Windows, instead of the code in quotes, manually substitute the parameter obtained by\n"
    "   calling `vcpkg integrate install`.\n"
    "1. Putting together the directory and tests:\n"
    "   `cmake --build cmake-build-release --target all`\n"
    "   After that, the main self-executable utility will appear in the `cmake-build-release` directory under the name `{0}`\n"
    "   . Tests can be run by running the `test` file located nearby.";

  constexpr inline std::string_view MAIN_CPP_FOR_TOOL_TEXT =
    //language=cpp
    "#include <CLI/App.hpp>\n"
    "#include <CLI/Formatter.hpp>\n"
    "#include <CLI/Config.hpp>\n"
    "#include <fmt/core.h>\n"
    "#include <fmt/color.h>\n"
    "\n"
    "int main(int argc, char **argv) {\n"
    "  CLI::App utility(\"{1}\", \"{0}\");\n"
    "  CLI11_PARSE(utility, argc, argv)\n"
    "}";

  constexpr inline std::string_view TEST_CPP_TEXT =
    "#define CATCH_CONFIG_MAIN\n"
    "\n"
    "#include <catch.hpp>\n"
    "\n"
    "TEST_CASE(\"test\") {\n"
    "  REQUIRE(1 == 1);\n"
    "}";

  constexpr inline std::string_view GITIGNORE_TEXT =
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
    ".editorconfig";
}



