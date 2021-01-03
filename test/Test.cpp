#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <fmt/core.h>
#include "../src/Project.h"


TEST_CASE("test project") {
  auto testProject = Project("test_project")
    .addReadme();
  std::filesystem::remove(testProject.directory);
  REQUIRE(1 == 1);
}