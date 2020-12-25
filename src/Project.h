#pragma once

#include <string>
#include <filesystem>

struct Project {

  struct Creator {
    const std::string name;
    const std::string description;
    const std::filesystem::path directory;

    static Creator From(int argc, char **argv);

  private:
    Creator(std::string name, std::string description, std::filesystem::path directory);
  };

  const std::string name;
  const std::string description;
  const std::filesystem::path directory;

private:
  Project(std::string name, std::string description, std::filesystem::path directory);
};

