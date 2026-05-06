# Semester Project Plan — Isaac Artifact Calibration Chamber


## Chosen task
The project is an interactive 3D calibration chamber in which the player controls the `ISAAC2` character inside a small sci-fi inspection area. The scene is built around three core elements:

1. a controllable player character (`ISAAC2.obj`),
2. movable artifacts that can be repositioned during the demonstration,
3. a manually adjustable inspection light used to study surface details and textures.

The point of the program is not a generic "3D demo", but a compact presentation scene where the user can walk around the chamber, inspect imported textured models from different angles, move the main artifacts, and deliberately change the lighting conditions.

## What the final submission should demonstrate
- A traversable 3D space with mouse + keyboard camera handling.
- Imported OBJ models with textured surfaces.
- Interactive manipulation of scene objects.
- Time-based animation on at least one highlighted artifact.
- Light movement and visible light-intensity changes with `+` / `-`.
- On-screen usage help via `F1`.

## Controls
### General
- `Esc`: quit
- `F1`: toggle help overlay

### Player and camera
- `W/A/S/D`: move the player character
- `Mouse (hold left button)`: orbit the camera

### Objects
- `1/2`: select object
- `I/J/K/L`: move selected object on X/Y
- `U/O`: move selected object on Z
- `R`: toggle auto-rotation for selected object

### Light
- `Arrow keys`: move light on X/Y
- `PageUp/PageDown`: move light on Z
- `+` / `-`: increase/decrease light intensity

## Build

### Windows (course SDK kept outside Git)
1. Keep the course SDK next to the repository as `../c_sdk_220203/`.
2. If `SDL2_image` reports a missing `libpng16-16.dll`, copy that DLL into `../c_sdk_220203/MinGW/bin/`.
3. Build from this folder:

```bat
..\c_sdk_220203\MinGW\bin\mingw32-make.exe
```

You can also start `..\c_sdk_220203\shell.bat` first and then run `make`.

### Linux
```sh
cd Beadando
make linux
```
