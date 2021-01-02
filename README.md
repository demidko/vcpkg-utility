## proj

[[Documentation in Russian here | Документация на русском здесь]](README.ru.md)

A cross-platform tool for quickly creating `C++ 20` projects with one command. The utility creates
`CMakeLists.txt`, entry points, pulls up `vcpkg` and the minimum required dependencies for command line projects,
adds `README.md` and finishes all this by creating a build script. In this way, created projects are supported
in `CLion`, `Visual Studio`, `VS Code` and can be easily extended with any dependencies from `vcpkg`.

### Motivation and goals?

As soon as a new idea of a C++ project appears in my head, I would just like to set its name, a short description, and
immediately start writing code, then collecting releases with one click/command without losing the final assembly
performance. However, in reality, you have to copy-paste or create manually each time the typical `CMakeLists.txt`
, `README.md`, source directories structure. Therefore, humanity just needs a tool to fast deployment of new C ++ 20
projects.

### How to get?

Check in your package manager or [download here](https://github.com/demidko/proj/releases)

### How to use

```shell
proj -n name -d 'short description of your project'
```

### How to build?

We need a build system [`cmake`](https://cmake.org/download) and a manager
libraries [`vcpkg`](https://github.com/microsoft/vcpkg). They can be easily installed with a package manager such
as `brew`.

1. Install the dependencies:  
   `vcpkg install` [`catch2`](https://github.com/catchorg/Catch2)  
   `vcpkg install` [`cli11`](https://github.com/CLIUtils/CLI11)  
   `vcpkg install` [`fmt`](https://github.com/fmtlib/fmt)
1. If you are using an IDE, you can stop at this step simply by setting `CMake options` as the result
   of `vcpkg integrate install` command.
1. Prepare the directory for building using the dependencies `vcpkg`:  
   ```cmake `vcpkg integrate install | tail -1 | cut -d \" -f2` -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B cmake-build-release```  
   On Windows, instead of the quotes, manually substitute the parameter obtained by calling `vcpkg integrate install`.
1. Putting together the directory and tests:
   `cmake --build cmake-build-release --target all`
   After that, the main self-executable utility will appear in the `cmake-build-release` directory under the name `proj`
   . Tests can be run by running the `test` file located nearby.

### TODO

1. Add vcpkg to utility resources
1. Create macOS, Linux, Windows universal build scripts