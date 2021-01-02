#pragma once

#include <filesystem>
#include <initializer_list>

namespace Filesystem {

  void createDirectoryWithParents(const std::filesystem::path &path);

  void createTextFile(
    const std::filesystem::path &path,
    std::string_view textTemplate,
    const std::initializer_list<std::string_view> &args
  );
}
