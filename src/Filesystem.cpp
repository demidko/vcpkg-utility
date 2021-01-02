#include <Filesystem.h>
#include <fstream>
#include <fmt/core.h>

void Filesystem::createDirectoryWithParents(const std::filesystem::path &path) {

  if (auto p = path.parent_path(); !std::filesystem::exists(p)) {
    createDirectoryWithParents(p);
  }
  std::filesystem::create_directory(path);
}

void Filesystem::createTextFile(
  const std::filesystem::path &path,
  std::string_view textTemplate,
  const std::initializer_list<std::string_view> &args) {

  createDirectoryWithParents(path.parent_path());
  std::ofstream(path) << fmt::format(textTemplate, args);
}


