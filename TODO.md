# Task list

## Future ideas

- [ ] Create a python script to validate the code (ensure the usage of namespaces, ensure that private / public variable naming, etc...)
- [ ] Enable attaching entities to other entities
- [ ] Implement a garbage collector like the one from UE5 (with strong and weak pointers)
- [ ] Create a layer of abstraction for ImGui (and use it to display debug info)
- [ ] Try unit testing

## Input System

- [ ] Create the Input System class
- [ ] Create an abstraction over the keycodes, mouse buttons, etc
- [ ] Create the methods to check for key down, key press and key release
- [ ] Create methods to change the mouse behaviour (visible, hidden, locked)

## Rendering

- [X] Texture Renderer class
- [X] Add the default mesh
- [ ] Add the default shader (as a file)
- [ ] Custom material system (with instances)
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