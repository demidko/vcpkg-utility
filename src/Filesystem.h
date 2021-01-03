#pragma once

#include <filesystem>
#include <fstream>
#include <fmt/core.h>

namespace Filesystem {

  void createDirectoryWithParents(const std::filesystem::path &path);

  template<typename... Args>
  void formatToFile(const std::filesystem::path &path, std::string_view text, Args &&... args) {
    createDirectoryWithParents(path.parent_path());
    std::ofstream(path) << fmt::format(text, args...);
  }
}
