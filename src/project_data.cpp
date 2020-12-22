#include <project_data.h>
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

project_data project_data::from_args(int argc, char **argv) {

  CLI::App app("C++20 projects creator", "app");
  project_data project;

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

project_data::readme_builder project_data::create_directory() {
  auto project_path = std::filesystem::current_path().append(name);
  std::filesystem::create_directory(project_path);
  return project_data::readme_builder{project_path, description};
}

project_data::repo_builder project_data::readme_builder::create_repo() {
  return project_data::repo_builder();
}
