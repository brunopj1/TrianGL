# Task list

This is a file I use to keep track of the tasks I need to do in the project.
For a detailed list of implemented and upcoming features check the [FEATURES.md](FEATURES.md) file.

## Documentation

- Use Doxygen to generate the documentation
- Add a link in the wiki to the generated documentation

## Github wiki

- Refactor the new way of modifying the execution order in the wiki
- Mention the animations and animators in the wiki
- Mention the custom datatypes in the wiki (and use them in every code snippet)
- Explain the existing entities and components (Camera, etc...)
- Mention the Util classes (Random only for now)

## Modern C++

- Use C++20 modules instead of regular headers and source files
  - Separate the declarations and definitions?
  - How to deal with cyclic dependencies?
  - Forward declare the methods of the classes?

## Testing

- Use google mock 
- Check if the tests can use a coroutine for the GameMode::OnUpdate method
  - Add the WaitSeconds() and WaitFrames() methods, that should mock the passing of time

## General

- Move the spawning and lookup methods to global functions (and update the wiki)
- Execute the callbacks after the ImGui NewFrame (to allow for example opening popups, but first check if it is possible already)
- Add the remaining window functionalities (is focused, can resize, etc...) (check glfw docs)
- Fix the warnings in the Google Test project
- Run python validation scripts in the CI
- Add glad as a submodule and build it in the build script
- Add clang-tidy files to the project (run it on the CI)

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
