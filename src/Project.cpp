#include <Project.h>
#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

namespace {
  template<typename T>
  CLI::callback_t by(T &&handler) {
    return [&handler](auto &args) {
      for (auto &&x: args) {
        handler(x);
      };
      return true;
    };
  }
}

Project Project::fromArgs(int argc, char **argv) {

  CLI::App app("C++20 projects creator", "app");
  Project project(std::string(), std::string());

  app.add_option(
    "-n,--name",
    by([&project](std::string_view n) { project.name = n; }),
    "New project name"
  )->required();

  app.add_option(
    "-d,--description",
    by([&project](std::string_view d) { project.description = d; }),
    "New project description"
  )->expected(1);

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    app.exit(e);
  }

  return project;
}

Project::Project(std::string name, std::string description, std::filesystem::path directory)
  : name(std::move(name)), description(std::move(description)), directory(std::move(directory)) {}

Project::project_builder Project::create_directory() {
  auto project_path = std::filesystem::current_path().append(name);
  std::filesystem::create_directory(project_path);
  return Project::project_builder{project_path, description};
}

void Project::project_builder::create_readme() {

  return Project::repo_builder();
}
