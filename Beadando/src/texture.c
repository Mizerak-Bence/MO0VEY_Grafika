#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

GLuint load_texture(const char* filename)
{
    SDL_Surface* loaded = NULL;
    SDL_Surface* surface = NULL;
    GLuint texture_name = 0;

    loaded = IMG_Load(filename);
    if (loaded == NULL) {
        printf("[ERROR] IMG_Load failed for '%s': %s\n", filename, IMG_GetError());
        return 0;
    }

    surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(loaded);

    if (surface == NULL) {
        printf("[ERROR] SDL_ConvertSurfaceFormat failed for '%s': %s\n", filename, SDL_GetError());
        return 0;
    }

    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        surface->w,
        surface->h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    return texture_name;
}
