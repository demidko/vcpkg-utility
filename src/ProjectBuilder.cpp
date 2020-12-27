#include <ProjectBuilder.h>
#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>
#include <string_view>
#include <iostream>
#include <fstream>
#include <fmt/core.h>

namespace {

  void executeOrMessage(std::string_view command, std::string_view message) {
    if (std::system(command.data()) != 0) {
      std::cout << fmt::format("Warning: {}\n", message);
    }
  }
}

ProjectBuilder ProjectBuilder::createProject(int argc, char **argv) {
  CLI::App utility("C++20 projects creator", "utility");
  std::string name, description;
  utility
    .add_option("-n,--name", name, "New project name")
    ->required();
  utility
    .add_option("-d,--description", description, "New project description")
    ->expected(1);
  try {
    utility.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    utility.exit(e);
  }
  auto directory = std::filesystem::current_path().append(name);
  std::filesystem::create_directory(directory);
  return ProjectBuilder(std::move(name), std::move(description), std::move(directory));
}

ProjectBuilder::ProjectBuilder(std::string name, std::string description, std::filesystem::path directory)
  : name(std::move(name)), description(std::move(description)), directory(std::move(directory)) {}

ProjectBuilder &ProjectBuilder::initRepository() {
  auto gitInit = fmt::format("git init {}", name);
  executeOrMessage(gitInit, "failed to initialize git repository");
  return *this;
}

ProjectBuilder &ProjectBuilder::createDocumentation() {
  auto readme = std::filesystem::path(directory).append("README.md");
  auto emptyLine = "\n\n";
  std::ofstream(readme) << fmt::format("");
  return *this;
}

ProjectBuilder &ProjectBuilder::createBuildConfiguration() {
  return *this;
}



