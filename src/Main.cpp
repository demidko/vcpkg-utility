#include <ProjectBuilder.h>
#include <array>
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

using fmt::color;

int main(int argc, char **argv) {
  fmt::print(fg(color::dark_orange), "ooo {}", 4);
}