#pragma once

#include <string>
#include <filesystem>

struct project_data {

  struct repo_builder {

  };

  struct readme_builder {
    std::filesystem::path directory;
    std::string description;

    repo_builder create_repo();
  };


  std::string name;
  std::string description;

  static project_data from_args(int argc, char **argv);

  readme_builder create_directory();
};

