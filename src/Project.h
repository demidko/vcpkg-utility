#include <string>
#include <string_view>
#include <filesystem>

struct Project {

  const std::string name;
  const std::string description;
  const std::filesystem::path directory;

  Project &addGit();

  Project &addReadme();

  Project &addCMakeLists();

  Project &addSources();

  explicit Project(std::string name, std::string description = "");
};