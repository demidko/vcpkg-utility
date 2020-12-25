#include <Project.h>
#include <iostream>
#include <filesystem>


int main(int argc, char **argv) {
  Project::Creator::From(argc, argv);
}