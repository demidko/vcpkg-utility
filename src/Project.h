#pragma once

#include <string>
#include <filesystem>

class Project {

public:
  class Builder {

  };

  const std::string name;
  const std::string description;
  const std::filesystem::path directory;

  static Builder fromArgs(int argc, char **argv);

private:
  Project(std::string name, std::string description, std::filesystem::path directory);
};

