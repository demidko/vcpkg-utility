## proj

A cross-platform `C++20` build system with dependency manager, powered by integration of [`cmake`](https://cmake.org/)
with [` vcpkg`](https://github.com/microsoft/vcpkg).

### Motivation and goals

In the С++ world, now...

* When an idea comes up, you have to createUtility manually `CMakeLists.txt`,` README.md`, a folder structure, or finish
  the project created by the IDE to a portable state.
* There is no dependency management without difficulties.
* There is no cross-platform build without Qt.
* These problems overlap, causing troubles for developers.

Therefore, `proj` is a tool for creating and building cross-platform C++ projects with external dependencies. `proj` is
a tool like `maven` for Java, `dotnet` for .NET and `cargo` for Rust.

### `proj` features and benefits

* Full compatibility with existing technologies. No build configuration files are added except for the
  traditional `CMakeLists.txt`.
* To create project, specify name, short description, and immediately get prepared repository with all configs and docs.
* Adding dependencies is done with one command through integration with [`vcpkg`](https://github.com/microsoft/vcpkg).
* A project with all dependencies can be built on different OS without configuration changes.
* Created projects are supported by all modern IDEs.

### How to install `proj`?

Check in your package manager or [download here](https://github.com/demidko/proj/releases).

### Examples of using `proj`

`proj -n name -d 'description of your project'`

This command create `CMakeLists.txt` configuration for project and tests, entry points, adds `vcpkg` and minimum
required dependencies for command-line tools, `README.md` documentation. Thus created projects are supported in `CLion`
,` Visual Studio`, `VS Code`.

### How to build `proj` source code?

We need [`cmake`](https://cmake.org/download) build system and [`vcpkg`](https://github.com/microsoft/vcpkg) manager
libraries. It's easy to install with system package manager, `brew` for example.

1. Install the dependencies:  
   `vcpkg install` [`catch2`](https://github.com/catchorg/Catch2)  
   `vcpkg install` [`cli11`](https://github.com/CLIUtils/CLI11)  
   `vcpkg install` [`fmt`](https://github.com/fmtlib/fmt)
1. If you are using an IDE, you can stop at this step simply by setting `CMake options` as the result
   of `vcpkg integrate install` command.
1. Prepare the directory for building using the dependencies `vcpkg`:  
   ```cmake `vcpkg integrate install | tail -1 | cut -d \" -f2` -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B cmake-build-release```  
   On Windows, instead of the code in ``` `` ``` quotes, manually substitute the parameter obtained by
   calling `vcpkg integrate install`.
1. Putting together the directory and tests:
   `cmake --build cmake-build-release --target all`
   After that, the main self-executable utility will appear in the `cmake-build-release` directory under the name `proj`
   . The tests can be run by launching the `test` file located nearby.

### Utility source code conventions?

* The entry point must be located in the `Main.cpp` file for correct build script work.
* To initialize resources, we using [modern parameter passing by value](https://habr.com/ru/post/460955/), rather than a
  constant link.
* Only the result of the compilation of `* .cpp` files in the` src` folder is included in the release assembly.
* The `src` folder contains the` *.cpp` and `*.h` project files together.
* The `test` folder contains the` *.cpp` and `*.h` project test files together.
* Each `*.h` file must define only one entity in the global namespace, whose name must match the file name.
* The contents of `*.cpp` files not declared in` *.h` file must be protected from `external linkage` from others
  compilation units by adding them to the anonymous namespace or adding the keyword `static`.

### TODO

1. The utility adds build scripts (for any OS) to each project.
1. Build scripts are based on `vcpkg` repository.
1. Build scripts check if `vcpkg` is installed and compiled.
1. Build scripts scan `CMakeLists.txt` and match all `find_package` calls and founds `vcpkg` deps.
1. Build scripts use local `vcpkg` to resolve dependencies.
1. Add the utility to the repositories of popular dependency managers.
1. Write publications to habr, reddit, hackernews.
1. Add more projects types.
