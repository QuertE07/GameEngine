# Game Engine

A component-based 2D game engine written in **C++20**, built around a lightweight actor/component architecture. The engine ships with its own audio, input, physics, and rendering systems, and includes a demo game showcasing actors, components, tilemaps, and UI.

## Features

- **Component-based architecture** — actors are lightweight containers composed of reusable components, allowing behavior to be built declaratively rather than through deep inheritance hierarchies.
- **Renderer system** — built on SDL3 for cross-platform 2D rendering.
- **Audio system** — powered by FMOD for sound effects and music playback.
- **Physics system** — powered by Box2D for rigid body simulation and collision detection.
- **Input system** — unified handling of keyboard, mouse, and controller input via SDL3.
- **Serialization** — game and scene data is loaded/saved using RapidJSON.
- **Self-contained build** — all required third-party files are vendored in the repository, so no external package manager is required to compile.

## Dependencies

| Library     | Purpose                          |
|-------------|-----------------------------------|
| [SDL3](https://github.com/libsdl-org/SDL)     | Windowing, rendering, input |
| [FMOD](https://www.fmod.com/)                 | Audio playback and mixing |
| [Box2D](https://github.com/erincatto/box2d)   | 2D physics simulation |
| [RapidJSON](https://github.com/Tencent/rapidjson) | JSON parsing/serialization |

All dependencies are included in the `ThirdParty/` directory of this repository, so a fresh clone should build without needing to install anything separately.

## Project Structure

```
.
├── Engine/                # Core engine source
│   ├── Audio/
│   ├── Components/
│   ├── Core/
│   ├── Framework/
│   ├── Input/
│   ├── Math/
│   ├── Physics/
│   ├── Renderer/
│   ├── Resources/
│   └── Serialization/
├── Game/                  # Demo game(s) built on the engine
│   ├── FlowerGame/
│   ├── Other/
│   └── SpriteGame/
├── ThirdParty/            # Vendored third-party dependencies
│   ├── SDL3/
│   ├── box2d/
│   ├── fmod/
│   └── rapidjson/
├── build/                 # Build output (binaries, assets, runtime DLLs)
└── GameEngine.slnx        # Visual Studio solution
```

## Building

### Prerequisites

- **Visual Studio** (2022 or later recommended) with the "Desktop development with C++" workload installed
- Windows, since the project targets the MSVC toolchain

### Build Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/QuertE07/GameEngine.git
   ```
2. Open `GameEngine.slnx` in Visual Studio.
3. Select your desired configuration (e.g. `Debug` or `Release`) and platform (e.g. `x64`).
4. Build the solution (`Ctrl+Shift+B`) or press **Local Windows Debugger** to build and run.

Since all required dependency files (SDL3, FMOD, Box2D, RapidJSON) are already included in the repository, the solution should build out of the box with no external package manager or additional downloads required.

## Demo Game

The `Game/` directory contains demo game projects (`FlowerGame`, `SpriteGame`) that exercise the engine's core features, including:

- **Actors** — entities placed and updated in the game world
- **Components** — modular behaviors (movement, collision, rendering, etc.) attached to actors
- **Tilemaps** — grid-based level layout and rendering
- **UI** — in-game interface elements

Build and run one of the game projects to see the engine in action.

# Controls

SpriteGame:
- Move with arrow keys
- Jump with Z
- Attack with X

## Architecture Overview

The engine follows a component-based design:

- **Actor** — a container object representing an entity in the world (position, name, identity).
- **Component** — a modular piece of behavior or data (e.g. sprite, collider, audio source) attached to an actor.
- **Systems** — engine-level managers (Renderer, Audio, Input, Physics) that operate over actors/components each frame.

This separation keeps gameplay logic decoupled from engine internals, making it straightforward to extend the engine or the demo game with new component types.

## Acknowledgments

- [SDL3](https://github.com/libsdl-org/SDL)
- [FMOD by Firelight Technologies](https://www.fmod.com/)
- [Box2D by Erin Catto](https://github.com/erincatto/box2d)
- [RapidJSON](https://github.com/Tencent/rapidjson)
