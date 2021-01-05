#include "Project.h"
#include "Command.h"
#include "Resources.h"

using namespace Resources;

// directory should be declared before name, because of std::move(name)!
Project::Project(std::string name, std::string description)
  : directory(std::filesystem::current_path() / name),
    name(move(name)),
    description(move(description)) {}

Project &Project::initRepository() {
  Command::execute(fmt::format("git init {}", directory.u8string()))
    .orWarning("failed to initialize git repository");
  return *this;
}

Project &Project::makeCommit(std::string_view comment) {
  Command::execute(fmt::format("git makeCommit -a -m {}", comment))
    .orWarning("failed to make makeCommit");
  return *this;
}

Project &Project::addCMakeConfigForTool() {
  formatTo("CMakeLists.txt", CMAKE_CONFIG_FOR_TOOL_TEXT, name);
  return *this;
}

Project &Project::addReadmeFile() {
  formatTo("README.md", README_TEXT, name, description);
  return *this;
}

Project &Project::addTestEntryPoint() {
  formatTo("test/Test.cpp", TEST_CPP_TEXT);
  return *this;
}

Project &Project::addEntryPointForTool() {
  formatTo("src/Main.cpp", MAIN_CPP_FOR_TOOL_TEXT, name, description);
  return *this;
}

Project &Project::addEditorConfig() {
  formatTo(".editorconfig", EDITORCONFIG_TEXT);
  return *this;
}

Project &Project::createDirectory() {
  std::filesystem::create_directories(directory);
  return *this;
}

Project &Project::addGitIgnoreConfig() {
  formatTo(".gitignore", GITIGNORE_TEXT);
  return *this;
}

Project &Project::createCrossPlatformToolSkeleton() {
  createDirectory();
  addReadmeFile();
  addCMakeConfigForTool();
  addEditorConfig();
  addTestEntryPoint();
  addEntryPointForTool();
  addGitIgnoreConfig();
  initRepository();
  return makeCommit(
    fmt::format("Project {} created by <proj> tool", name)
  );
}





