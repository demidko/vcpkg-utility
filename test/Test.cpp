#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <Project.h>
#include <fmt/core.h>

constexpr std::string_view x = "dfs";

TEST_CASE("test project") {
  Project("test_project").addReadme();
  REQUIRE(1 == 1);
}