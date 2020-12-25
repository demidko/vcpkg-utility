#include <Project.h>
#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

Project::Creator Project::Creator::From(int argc, char **argv) {

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

  return Creator(std::move(name), std::move(description), std::move(directory));
}

Project::Project(std::string name, std::string description, std::filesystem::path directory)
  : name(std::move(name)), description(std::move(description)), directory(std::move(directory)) {}

Project::Creator::Creator(std::string name, std::string description, std::filesystem::path directory)
  : name(std::move(name)), description(std::move(description)), directory(std::move(directory)) {}
