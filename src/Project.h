#include <string>
#include <filesystem>

struct Project {

  const std::string description;
  const std::filesystem::path directory;
  const std::string name;

  explicit Project(std::string name, std::string description = "");

  Project &addGit();

  Project &addReadme();

  Project &addCMakeLists();

  Project &addSources();
};