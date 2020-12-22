#include <project_data.h>
#include <iostream>
#include <filesystem>



int main(int argc, char **argv) {
  const auto project = project_data::from_args(argc, argv)
    .create_directory();
}