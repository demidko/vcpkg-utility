#include "Project.h"
#include "Filesystem.h"
#include "Command.h"
#include "Resources.h"

Project::Project(std::string name, std::string description) :
  description(std::move(description)),
  // directory should be declared before name, because of std::move(name)!
  directory(std::filesystem::current_path() / name),
  name(std::move(name)) {

  Filesystem::createDirectoryWithParents(directory);
}

using namespace Resources;

Project &Project::addGit() {
  fmt::print("dir: {}", std::string(directory));
  Command::execute(fmt::format("git init {}", directory.u8string()))
    .orWarning("failed to initialize git repository");
  return *this;
}

Project &Project::addCMakeLists() {
  Filesystem::formatToFile(directory / "CMakeLists.txt", CMAKE_CONFIG_TEXT, name);
  return *this;
}

Project &Project::addReadme() {
  Filesystem::formatToFile(directory / "README.md", README_TEXT, name, description);
  return *this;
}

Project &Project::addSources() {
  Filesystem::formatToFile(directory / "src/Main.cpp", MAIN_CPP_TEXT, name, description);
  Filesystem::formatToFile(directory / "test/Test.cpp", TEST_CPP_TEXT);
  return *this;
}





