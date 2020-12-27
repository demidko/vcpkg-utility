#pragma once

#include <string>
#include <filesystem>

struct ProjectBuilder {

  const std::string name;
  const std::string description;
  const std::filesystem::path directory;

  static ProjectBuilder createProject(int argc, char **argv);

  ProjectBuilder &initRepository();

  ProjectBuilder &createDocumentation();

  ProjectBuilder &createBuildConfiguration();

private:
  ProjectBuilder(std::string name, std::string description, std::filesystem::path directory);
};

