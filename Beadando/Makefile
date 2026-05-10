# Semester project build (SDL2 + OpenGL)
#
# Windows uses the provided course SDK at ../c_sdk_220203/MinGW

APP_NAME := beadando
BUILD_DIR := build
EXE_EXT :=
BIN = $(APP_NAME)$(EXE_EXT)

SDK_DIR := ../c_sdk_220203/MinGW

CC := gcc
RUN_BIN = ./$(BIN)

ifeq ($(OS),Windows_NT)
EXE_EXT := .exe
SDK_BIN := $(abspath $(SDK_DIR))/bin
# Ensure gcc's helper executables can find their dependent DLLs.
export PATH := $(SDK_BIN);$(PATH)
CC := $(SDK_DIR)/bin/gcc
RUN_BIN = $(BIN)

# cmd.exe is happier with backslashes and relative paths for builtins like copy
SDK_BIN_WIN := $(subst /,\,$(SDK_DIR))\bin
BUILD_DIR_WIN := $(subst /,\,$(BUILD_DIR))
BIN_WIN := $(subst /,\,$(BIN))

define COPY_RUNTIME_DLLS
	copy /Y "$(SDK_BIN_WIN)\\SDL2.dll" "SDL2.dll"
	copy /Y "$(SDK_BIN_WIN)\\SDL2_image.dll" "SDL2_image.dll"
	if exist "$(SDK_BIN_WIN)\\libpng16-16.dll" copy /Y "$(SDK_BIN_WIN)\\libpng16-16.dll" "libpng16-16.dll"
	if exist "$(SDK_BIN_WIN)\\zlib1.dll" copy /Y "$(SDK_BIN_WIN)\\zlib1.dll" "zlib1.dll"
	if exist "$(SDK_BIN_WIN)\\libjpeg-9.dll" copy /Y "$(SDK_BIN_WIN)\\libjpeg-9.dll" "libjpeg-9.dll"
endef

define DELETE_FILE
	if exist "$(1)" del /q "$(1)"
endef
else
define DELETE_FILE
	rm -f "$(1)"
endef
endif

CFLAGS := -std=c11 -O2 -Wall -Wextra -Wpedantic \
	-Iinclude -Ilib/obj/include -I$(SDK_DIR)/include

LDFLAGS := -L$(SDK_DIR)/lib
LDLIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm

APP_SRCS := \
	src/main.c \
	src/app.c \
	src/camera.c \
	src/scene.c \
	src/texture.c \
	src/ui.c \
	src/utils.c

OBJ_SRCS := \
	lib/obj/src/model.c \
	lib/obj/src/load.c \
	lib/obj/src/info.c \
	lib/obj/src/draw.c \
	lib/obj/src/transform.c

APP_OBJS := $(APP_SRCS:src/%.c=$(BUILD_DIR)/%.o)
OBJ_OBJS := $(OBJ_SRCS:lib/obj/src/%.c=$(BUILD_DIR)/obj_%.o)

all: $(BIN)

ifeq ($(OS),Windows_NT)
MKDIR_BUILD = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
RMDIR_BUILD = if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
else
MKDIR_BUILD = mkdir -p $(BUILD_DIR)
RMDIR_BUILD = rm -rf $(BUILD_DIR)
endif

$(BUILD_DIR):
	@$(MKDIR_BUILD)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/obj_%.o: lib/obj/src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(APP_OBJS) $(OBJ_OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

ifeq ($(OS),Windows_NT)
	$(COPY_RUNTIME_DLLS)
endif

run: $(BIN)
	$(RUN_BIN)

clean:
	$(RMDIR_BUILD)
	$(call DELETE_FILE,$(BIN))
	$(call DELETE_FILE,SDL2.dll)
	$(call DELETE_FILE,SDL2_image.dll)
	$(call DELETE_FILE,libpng16-16.dll)
	$(call DELETE_FILE,zlib1.dll)
	$(call DELETE_FILE,libjpeg-9.dll)

rebuild: clean all

# A simple linux target (requires system SDL2 + SDL2_image)
linux:
	gcc -std=c11 -O2 -Wall -Wextra -Wpedantic \
		-Iinclude -Ilib/obj/include \
		$(APP_SRCS) $(OBJ_SRCS) \
		-lSDL2 -lSDL2_image -lGL -lm \
		-o $(APP_NAME)

.PHONY: all clean rebuild run linux
