# Task list

This is a file I use to keep track of the tasks I need to do in the project.
For a detailed list of implemented and upcoming features check the [FEATURES.md](FEATURES.md) file.

## Other tasks

- Use github actions to validate the code
- Check ig the imgui-stdlib dependency can be used directly from the imgui submodule

## Documentation

- Use Doxygen to generate the documentation
- Add a link in the wiki to the generated documentation

## Github wiki

- Explain the existing entities and components (Camera, etc...)
- Explain how to render ImGui windows (and say that it is debug only)
- Explain how to use the callbacks
- Add every new feature to the wiki

## General

- Execute the callbacks after the ImGui NewFrame (to allow for example opening popups)
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
