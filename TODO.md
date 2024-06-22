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

- Add screenshots to the readme file
- Explain the existing entities and components (Camera, etc...)
- Mention the Util classes (Random only for now)

## Modern C++

- Use C++20 modules instead of regular headers and source files
  - Separate the declarations and definitions?
  - How to deal with cyclic dependencies?
  - Forward declare the methods of the classes?

## General

- Move the spawning and lookup methods to global functions (and update the wiki)
- Execute the callbacks after the ImGui NewFrame (to allow for example opening popups, but first check if it is possible already)
- Add the remaining window functionalities (is focused, can resize, etc...) (check glfw docs)
- Create a custom shared pointer class that can be reset even if there are still references to it

## Particles

- Separate the materials into SpriteMaterial and ParticleMaterial
- Add custom particle systems with user defined data (and opt-out cpu update)
- Allow resizing the particle system
- Add multi threading to the update loop

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
- Validate the shader attributes

## Entity system

- Create a Scene class
