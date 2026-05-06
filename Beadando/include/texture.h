#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

/**
 * Loads a texture from file using SDL_image.
 * Returns 0 on failure.
 */
GLuint load_texture(const char* filename);

#endif /* TEXTURE_H */
