#include <Project.h>
#include <iostream>
#include <filesystem>


int main(int argc, char **argv) {
  const auto project = Project::fromArgs(argc, argv)
    .create_directory();
}