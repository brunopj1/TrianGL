# Task list

## Future ideas

- [ ] Copy the asset folders to the output directory instead of modifying the working directory
- [ ] Create a python script to validate the code (ensure the usage of namespaces, ensure that private / public variable naming, etc...)
- [ ] Enable attaching entities to other entities
- [ ] Implement a garbage collector like the one from UE5 (with strong and weak pointers)
- [ ] Create a layer of abstraction for ImGui (and use it to display debug info)
- [ ] Try unit testing

## Resource Manager

- [X] Create a resource manager class
- [X] Automatically delete resources when the application is closed
- [X] Create a method to load textures
- [ ] Create a method to load shaders

## Input System

- [X] Create the Input System class
- [X] Create the methods to check for key down, key press and key release
- [X] Create the methods to check for mouse down, mouse press and mouse release
- [X] Create the methods to check for mouse movement and scroll
- [X] Create methods to change the mouse behaviour (visible, hidden, locked)
- [ ] Use raw mouse motion when the mouse is locked (if available)

## Rendering

- [X] Texture Renderer class
- [ ] Shader class (internal)
- [ ] Material class (abstract)
- [X] Add the default mesh
- [ ] Add the default material
- [ ] Use uniform buffers for the shaders
- [X] Implement automatic rendering
- [ ] Implement View Frustum Culling
- [ ] Add a transform to the Texture Renderer
- [ ] Add a pivot to the Texture Renderer

## Entity system

- [X] Create a GameMode class
- [X] Create an Entity class
- [X] Create a Component class
- [ ] Create a System class (GameMode attachable)
- [ ] Create a Scene class
- [X] Create Instancing methods and automatic update
- [ ] Allow passing arguments to the instancing methods (to match the constructor)
- [X] Create lookup methods for the entities and components
- [ ] Add the delta time to the update methods

## Project setup

- [X] Add all the dependencies (if needed)
- [X] Set the engine as a static lib and change the startup project
- [X] Remove unnecessary filters from the lib premake files
- [X] Fixed 32 bit version not working
- [X] Only include ImGui in DEBUG config (use macros)
