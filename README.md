# TrianGL

[![Build Status](https://github.com/brunopj1/TrianGL/actions/workflows/Build-and-Test.yml/badge.svg)](https://github.com/brunopj1/TrianGL/actions/workflows/Build-and-Test.yml)

**TrianGL** is a 2D game engine written in C++ and OpenGL.
It's main goal is to be as easy to use as possible, allowing developers to quickly create games without worrying about low-level tasks such as engine initialization, rendering, input handling, etc...

This is a project that I have been working on in my free time, so it may still have missing features.
If you find any bugs or have any suggestions feel free to open an issue.

![](Misc/preview.gif)

## Platform Support

Currently, **TrianGL** only supports Windows. Support for other platforms may be added in the future.

## Installation

When cloning this repository, make sure to use the `--recurse-submodules` flag to also clone the dependencies.
If you have already cloned the repository without this flag, use the command `git submodule update --init --recursive` to clone the missing dependencies.

## Tutorials

To learn how to use the **TrianGL** engine, make sure to check the [Wiki](https://github.com/brunopj1/TrianGL/wiki).

## Dependencies

**TrianGL** uses the following dependencies:

- [glad](https://github.com/Dav1dde/glad): A loader-generator based on the official specs for OpenGL, used for managing OpenGL function pointers.
- [glfw](https://github.com/glfw/glfw): A multi-platform library for OpenGL, used for creating the window, reading input, handling events, etc.
- [glm](https://github.com/g-truc/glm): A mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
- [googletest](https://github.com/google/googletest): An easy-to-use unit test framework for C++.
- [imgui](https://github.com/ocornut/imgui): A bloat-free graphical user interface library for C++, used for creating graphical interfaces for debugging.
- [soloud](https://github.com/jarikomppa/soloud): A high-level audio API, used for loading, managing and playing audio files.
- [stb_image](https://github.com/nothings/stb): A header-only library for C/C++, used for image loading.

Each dependency is licensed under its own terms. Please check the respective repositories for more information.

## License

This project is licensed under the terms of the MIT license. For more details, see the [LICENSE](LICENSE.md) file.
