#include <Filesystem.h>

void Filesystem::createDirectoryWithParents(const std::filesystem::path &path) {
  if (auto parentPath = path.parent_path(); !std::filesystem::exists(parentPath)) {
    createDirectoryWithParents(parentPath);
  }
  std::filesystem::create_directory(path);
}

