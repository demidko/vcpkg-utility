#include <ProjectBuilder.h>
#include <array>

#include <iostream>

int execute(std::string_view command) {
  return std::system(command.data());
}

#include <filesystem>

int main(int argc, char **argv) {
  std::filesystem::path x("aaa");
  auto y = std::filesystem::path{x}.append("ooo");
  std::cout << x;
}