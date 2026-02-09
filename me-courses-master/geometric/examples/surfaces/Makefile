all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c src/surface.c -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -o surface.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c src/surface.c -lSDL2 -lGL -lm -o surface -Wall -Wextra -Wpedantic

