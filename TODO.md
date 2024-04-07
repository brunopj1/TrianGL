# Task list

This is a file I use to keep track of the tasks I need to do in the project.
For a detailed list of implemented and upcoming features check the [FEATURES.md](FEATURES.md) file.

## Other tasks

- [ ] Use github actions to validate the code
- [ ] Check ig the imgui-stdlib dependency can be used directly from the imgui submodule

## Documentation

- [ ] Use Doxygen to generate the documentation
- [ ] Add a link in the wiki to the generated documentation

## Github wiki

- [ ] Explain the Game classes and how to create / destroy them
- [ ] Explain how and why to use the Execution Order
- [ ] Explain that the execution order should always return the same value (or the user will experience undefined behaviour)
- [ ] Explain that the game mode should not delete anything in the destructor
- [ ] Explain how the assets work (talk about the shared pointers) (talk about how the asset folder is copied to the output directory)
- [ ] Explain that the assets should not outlive the game mode (for example when stored in static variables)
- [ ] Explain the public core systems (Clock, Input, Window, etc...)
- [ ] Explain the existing entities and components (Camera, Texture Renderer, etc...)
- [ ] Explain the lazy pointers and how to use them
- [ ] Explain how to render ImGui windows (and say that it is debug only)
- [ ] Explain how to use the callbacks
- [ ] Add every new feature to the wiki

## General

- [ ] Execute the callbacks after the ImGui NewFrame (to allow for example opening popups)
- [ ] Add the remaining window functionalities (is focused, can resize, etc...) (check glfw docs)

## Audio

- [ ] Add a duration method to the Audio class and a seek method to the AudioPlayer class
- [ ] Add a "PlayAndForget" static method to the AudioPlayer (the audio must be stored somewhere while being played to avoid being deleted)
- [ ] Add more settings to the sound and audio player (pitch, pan, etc...) (check the soloud docs)
- [ ] Add 3D audio support

## Input System

- [ ] Use raw mouse motion when the mouse is locked (if available)

## Rendering

- [ ] Add batch rendering (for the same material)
- [ ] Use uniform buffers for the shaders

## Entity system

- [ ] Create a Scene class
