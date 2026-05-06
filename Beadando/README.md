# Semester Project Plan — Isaac Artifact Calibration Chamber

This folder contains the semester project implemented in C using SDL2 + legacy OpenGL.

## What should stay in Git
The committed project should be limited to the minimum submission set:
- source files in `src/` and interface headers in `include/`,
- the bundled OBJ loader in `lib/obj/`,
- `third_party/stb_easy_font.h`, because the UI uses it at runtime,
- the runtime asset subset actually referenced by the code,
- `Makefile` and the README files.

## What should not stay in Git
The following belong to the local working environment only:
- `../c_sdk_220203/`, because it is the external course SDK/toolchain,
- `build/`, because it is generated,
- `assets/import/`, because those are source/import files rather than runtime assets,
- `tools/`, because generators are optional development helpers and not needed to run the committed project,
- unused asset experiments that are not referenced by the code.

This keeps the repository defensible: every committed file is either required for build/run, or required for submission documentation.

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

## Current MVP already covers
- Camera control with mouse orbit and keyboard movement.
- Imported OBJ models from `assets/models/`.
- Textures loaded from `assets/textures/`.
- Object selection and repositioning.
- Movable light source and adjustable light intensity.
- Help overlay in the application.

## Planned improvements before the final presentation
These are the concrete extensions that should turn the current MVP into a stronger semester project:

1. Build an actual chamber around the current ground plane: walls, focal props, and clearer visual composition.
2. Add collision limits / bounding boxes so the player and moved artifacts cannot leave the intended play area.
3. Add atmospheric fog to strengthen depth and improve the scene mood.
4. Add mouse-based object picking or a small status panel for the selected object.

With this scope, the project is no longer just "a few objects in empty space", but a defined interactive presentation scene.

## Planned internal structure
The final source layout should mirror the program logic instead of staying overly generic.

- `main.c`: application bootstrap only.
- `app.*`: SDL lifecycle, event loop, time step, high-level input routing.
- `camera.*`: orbit / follow camera behavior and view transforms.
- `scene.*`: temporary scene integration layer.
- `ui.*`: F1 help overlay and status text.
- `texture.*`: texture loading.

The next refactor step should split the current scene logic into topic-based modules:

- `player.*`: controllable character movement and follow-camera target.
- `artifact.*`: movable and animated exhibition objects.
- `lighting.*`: light state, presets, and intensity control.
- `world.*`: room geometry, collision bounds, and static environment props.

Object placement data should also move out of hardcoded C blocks into a small scene manifest (for example CSV), because repeated placement/configuration code should not stay embedded in source.

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

## Assets
Runtime assets are stored in the `assets/` directory.

If the final asset pack becomes too large, zip the `assets/` folder, upload it to cloud storage, and place the link here:
- Assets ZIP link: TODO
