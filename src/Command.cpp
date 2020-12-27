#include "Command.h"
#include <fmt/core.h>
#include <fmt/color.h>

using fmt::color;

Command::Command(int code) : code(code) {}

Command Command::execute(std::string_view command) {
  return Command(std::system(command.data()));
}

void Command::orError(std::string_view message) const {
  if (code != 0) {
    fmt::print(
      fg(color::dark_red),
      "Error: {}\n", message.empty() ? std::to_string(code) : message
    );
    std::exit(code);
  }
}

void Command::orWarning(std::string_view message) const {
  if (code != 0) {
    fmt::print(
      fg(color::dark_orange),
      "Warning: {}\n", message.empty() ? std::to_string(code) : message
    );
  }
}