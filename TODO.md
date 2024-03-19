# Task list

## Future ideas

- [ ] Create a python script to validate the code (ensure the usage of namespaces, ensure that private / public variable naming, etc...)
- [ ] Implement a sound system

## General

- [X] Add a single exception for when the engine is not initialized
- [X] Reorganize the exceptions
- [X] Add lazy pointers to the classes managed by the engine (Entity, Component, System, Resource)
- [ ] Add Window callbacks with order of execution (onResize, onMove, onMinimize, onMaximize, onRestore, onToggleFullscreen)

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

## Rendering with transparency
- [X] Implement Z indexing
- [ ] Implement Z sorting
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
- [ ] Add more engine material uniforms (window, camera, etc...)
- [ ] Validate the material uniforms (repeated names, invalid type)
- [ ] Add batch rendering (for the same material)
- [ ] Use uniform buffers for the shaders

## Entity system

- [X] Create a GameMode class
- [X] Create an Entity class
- [X] Create a Component class
- [ ] Create a System class (GameMode attachable)
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
