#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <fmt/core.h>
#include "../src/Project.h"
#include <streambuf>

std::string readAllText(std::filesystem::path)

using namespace Catch::Matchers;

TEST_CASE("ExampleProject") {
  std::ifstream("df").rdbuf()

  auto p = Project("ExampleProject", "Little project for example").createToolSkeleton();
  REQUIRE_THAT(, Equals());
  std::filesystem::remove_all(p.directory);
}