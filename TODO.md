# Task list

## Future ideas

- [ ] Create a python script to validate the code (ensure the usage of namespaces, ensure that private / public variable naming, etc...)
- [ ] Implement a sound system
- [ ] List all the libraries used in the project (and their licenses)

## Github wiki

- [ ] Add a useful readme file
- [ ] Add a wiki with the engine documentation
- [ ] Explain how to create a game (create the Application, set the game mode, etc...)
- [ ] Explain the Game classes and how to create / destroy them
- [ ] Explain how and why to use the Execution Order
- [ ] Explain that the execution order should always return the same value (or the user will experience undefined behaviour)
- [ ] Explain that the game mode should not delete anything in the destructor
- [ ] Explain how the resources work (talk about the shared pointers)
- [ ] Explain that the resources should not outlive the game mode (for example when stored in static variables)
- [ ] Explain the public core systems (Clock, Input, Window, etc...)
- [ ] Explain the existing entities and components (Camera, Texture Renderer, etc...)
- [ ] Explain the lazy pointers and how to use them
- [ ] Explain how to render ImGui windows (and say that it is debug only)
- [ ] Explain how to use the callbacks
- [ ] Add every new feature to the wiki

## General

- [X] Add a single exception for when the engine is not initialized
- [X] Reorganize the exceptions
- [X] Add lazy pointers to the classes managed by the engine (Entity, Component, System, Resource)
- [X] World to Screen and Screen to World methods
- [X] Add Window callbacks with order of execution (onResize, onMove, onMinimize, onMaximize, onRestore, onToggleFullscreen)
- [ ] Execute the callbacks after the ImGui NewFrame (to allow for example opening popups)
- [ ] Add the remaining window functionalities (is focused, can resize, etc...) (check glfw docs)
- [ ] Add a project generator script

## Audio

- [X] Add the audio engine
- [X] Add the Sound class
- [ ] Add the Music class
- [X] Add the AudioPlayer class (play, pause and stop, loop, etc...)
- [X] Add volume settings to the Sound and AudioPlayer classes (multiply the volumes to get the real volume)
- [ ] Add a "PlayAndForget" static method to the AudioPlayer (the sound must be stored somewhere while being played to avoid being deleted)
- [ ] Add more settings to the sound and audio player (pitch, pan, etc...) (check the soloud docs)
- [ ] Add 3D audio support

## Resource Manager

- [X] Create a resource manager class
- [X] Automatically delete resources when the application is closed
- [X] Create a method to load textures
- [X] Create a method to load materials
- [X] Move the static methods to the respective classes

## Input System

- [X] Create the Input System class
- [X] Create the methods to check for key down, key press and key release
- [X] Create the methods to check for mouse down, mouse press and mouse release
- [X] Create the methods to check for mouse movement and scroll
- [X] Create methods to change the mouse behaviour (visible, hidden, locked)
- [ ] Use raw mouse motion when the mouse is locked (if available)

## Debug Rendering (ImGui)
- [X] Add an abstract class for ImGui rendering
- [X] Add ImGui menu overlay abstraction
- [X] Add custom ordering for the ImGui menu overlay
- [ ] Add Gizmos (World Grid, TextureRenderer Rect, TextureRenderer Pivot, etc...)

## Rendering with transparency
- [X] Implement Z indexing
- [X] Implement Z sorting
- [ ] Implement custom axis sorting
- [ ] Enable / disable alpha blending dynamically

## Rendering

- [X] Texture Renderer class
- [X] Shader class (internal)
- [X] Material class (abstract)
- [X] Material Uniform class
- [X] Material instances (using the same shader but different uniforms)
- [X] Add the default mesh
- [X] Add the default material
- [X] Implement automatic rendering
- [X] Add a transform to the Renderable class
- [X] Add a pivot to the Texture Renderer class
- [X] Use shared pointers for the resources
- [X] Add a way to slice textures (texture sheet)
- [X] Allow flipping the texture renderer (using the scale)
- [ ] Implement View Frustum Culling
- [ ] Validate the material uniforms (repeated names, invalid type)
- [ ] Add batch rendering (for the same material)
- [ ] Use uniform buffers for the shaders

## Entity system

- [X] Create a GameMode class
- [X] Create an Entity class
- [X] Create a Component class
- [ ] Create a Scene class
- [X] Create Instancing methods and automatic update
- [X] Allow passing arguments to the instancing methods (to match the constructor)
- [X] Create lookup methods for the entities and components
- [X] Add the delta time to the update methods
- [X] Move the static methods to the respective classes
- [ ] Allow parenting entities to each other (for Transform relationships, and auto memory management)

## Project setup

- [X] Add all the dependencies (if needed)
- [X] Set the engine as a static lib and change the startup project
- [X] Remove unnecessary filters from the lib premake files
- [X] Fixed 32 bit version not working
- [X] Only include ImGui in DEBUG config (use macros)
- [X] Copy the asset folders to the output directory instead of modifying the working directory
