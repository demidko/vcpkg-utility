#include <string>
#include <filesystem>
#include <fstream>
#include <fmt/core.h>

struct Project {

  const std::string description;
  const std::filesystem::path directory;
  const std::string name;

  explicit Project(std::string name, std::string description = "");

  Project &createCrossPlatformToolSkeleton();

private:

  Project &makeCommit(std::string_view comment = "");

  Project &initRepository();

  Project &addReadmeFile();

  Project &addCMakeConfigForTool();

  Project &addEntryPointForTool();

  Project &addTestEntryPoint();

  Project &addEditorConfig();

  Project &addGitIgnoreConfig();

  Project &createDirectory();

  template<typename... Args>
  void formatTo(const std::filesystem::path &file, std::string_view text, Args &&... args) {
    auto path = directory / file;
    if (auto dir = path.parent_path(); !std::filesystem::exists(dir)) {
      std::filesystem::create_directories(dir);
    }
    std::ofstream(path) << fmt::format(text, args...);
  }
};