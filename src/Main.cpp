#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>
#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/color.h>


int main(int argc, char **argv) {

  CLI::App utility("C++20 projects", "utility");

  std::string name, description;

  utility.add_option(
    "-n,--name",
    name,
    "New project name"
  )->required();
  utility.add_option(
    "-d,--description",
    description,
    "New project description"
  )->expected(1);

  CLI11_PARSE(utility, argc, argv)

  using fmt::color;

  fmt::print(
    fg(color::dark_orange),
    "name: {}\ndescription: {}\n", name, description
  );
}