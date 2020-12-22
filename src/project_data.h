#pragma once

#include <string>

struct project_data {

  std::string name;
  std::string description;

  static project_data from_args(int argc, char **argv);
};

