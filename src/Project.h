#pragma once

#include <string>
#include <filesystem>

struct Project {

  struct Builder {
    const std::string name;
    const std::string description;
    const std::filesystem::path directory;

    static Builder fromArgs(int argc, char **argv);

  private:
    Builder(std::string name, std::string description, std::filesystem::path directory);
  };

  const std::string name;
  const std::string description;
  const std::filesystem::path directory;

private:
  Project(std::string name, std::string description, std::filesystem::path directory);
};

