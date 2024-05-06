# Task list

This is a file I use to keep track of the tasks I need to do in the project.
For a detailed list of implemented and upcoming features check the [FEATURES.md](FEATURES.md) file.

## Other tasks

- Use github actions to validate the code
- Check if the imgui-stdlib dependency can be used directly from the imgui submodule

## Documentation

- Use Doxygen to generate the documentation
- Add a link in the wiki to the generated documentation

## Github wiki

- Replace the std::shared_ptr with the TGL::SharedPtr in the wiki
- Talk about casting materials using the SharedPtr::CastTo method
- Talk about uniform creation
- Talk about the engine uniforms and the other automatic uniforms (texture matrix, texture resolution, etc...)
- Explain the existing entities and components (Camera, etc...)
- Explain how to use the callbacks

## Modern C++

- Use C++20 modules instead of regular headers and source files
  - Separate the declarations and definitions?
  - How to deal with cyclic dependencies?
  - Forward declare the methods of the classes?

## General

- Execute the callbacks after the ImGui NewFrame (to allow for example opening popups, but first check if it is possible already)
- Add the remaining window functionalities (is focused, can resize, etc...) (check glfw docs)
- Create a custom shared pointer class that can be reset even if there are still references to it

## Audio

- Add a duration method to the Audio class and a seek method to the AudioPlayer class
- Add a "PlayAndForget" static method to the AudioPlayer (the audio must be stored somewhere while being played to avoid being deleted)
- Add more settings to the sound and audio player (pitch, pan, etc...) (check the soloud docs)
- Add 3D audio support

## Input System

- Use raw mouse motion when the mouse is locked (if available)

## Rendering

- Add batch rendering (for the same material)
- Use uniform buffers for the shaders

## Entity system

- Create a Scene class
