# xvk2de

**Under development...**

## Description

A 2D Vulkan game engine for personal study and interests.

This project was initially created by following the tutorial
of [Little Vulkan Engine](https://youtu.be/Y9U9IE0gVHA?si=42keJCaEPE-R697P) for learning Vulkan and Game Engine.
More features will be added soon.

## Installation

### Prerequisites

- CMake
- C++ compiler: g++ or clang++ or msvc
- Vulkan SDK: https://vulkan.lunarg.com/sdk/home
- GLFW3
- GLM

### Install Dependencies(Linux)

```bash    
sudo apt update
sudo apt install -y libvulkan-dev vulkan-tools glslang-tools libglfw3-dev libeigen3-dev libglm-dev
```

### Install Dependencies(Windows)

You can use [vcpkg](https://vcpkg.io/en/) or [MSYS2](https://www.msys2.org/) to install the dependencies.

If you use vcpkg on Clion, follow the [official guide](https://www.jetbrains.com/help/clion/package-management.html) to integrate vcpkg with Clion.


## External Libraries

The following libraries are used and pre-installed in this project.

| File              | Version | Project Link                                   |
|-------------------|---------|------------------------------------------------|
| stb_image.h       | v2.29   | https://github.com/nothings/stb                |
| tiny_obj_loader.h | v2.0.0  | https://github.com/tinyobjloader/tinyobjloader |

## TODO

- [ ] Physics Engine (Currently working on)
- [ ] GUI: ImGUI
- [ ] Mouse Input

## Problems
1. There are some ghost images in the rendering. It seems that the image is not cleared correctly.

## Reference

- Little Vulkan Engine: https://youtu.be/Y9U9IE0gVHA?si=42keJCaEPE-R697P
- ECS: https://austinmorlan.com/posts/entity_component_system/
- Game Loop: https://gameprogrammingpatterns.com/game-loop.html
