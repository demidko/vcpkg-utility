#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <fmt/core.h>
#include "../src/Project.h"


TEST_CASE("test project") {

  auto project = Project("test_project").createCrossPlatformToolSkeleton();

  //std::filesystem::remove_all(project.directory);
  REQUIRE(1 == 1);
}