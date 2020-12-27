#pragma once

#include <string_view>

struct Command {

  void orError(std::string_view message = "") const;

  void orWarning(std::string_view message = "") const;

  static Command execute(std::string_view command);

private:
  const int code;

  explicit Command(int code);
};



