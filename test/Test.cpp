#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <Project.h>

TEST_CASE("test project") {

  auto x = Project("test_project", "short description")
   .addGit();


  REQUIRE(1 == 1);
}