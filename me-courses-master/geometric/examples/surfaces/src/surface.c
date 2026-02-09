#include "surface.h"

#include <GL/gl.h>

#include <math.h>

void update_surface(Surface* surface)
{
  update_surface_vertices(surface);
  update_surface_normals(surface);
}

void update_surface_vertices(Surface* surface)
{
  for (int i = 0; i < N_ROWS; ++i) {
    double x = (double)i / (N_ROWS - 1);
    for (int j = 0; j < N_COLUMNS; ++j) {
      double y = (double)j / (N_ROWS - 1);
      double z = sin(5.0 * x) * sin(5.0 * y);
      surface->vertices[i][j].x = x;
      surface->vertices[i][j].y = y;
      surface->vertices[i][j].z = z;
    }
  }
}

void update_surface_normals(Surface* surface)
{
  for (int i = 1; i < N_ROWS - 1; ++i) {
    for (int j = 1; j < N_COLUMNS - 1; ++j) {
        vec3 d_i;
        d_i.x = surface->vertices[i + 1][j].x - surface->vertices[i - 1][j].x;
        d_i.y = surface->vertices[i + 1][j].y - surface->vertices[i - 1][j].y;
        d_i.z = surface->vertices[i + 1][j].z - surface->vertices[i - 1][j].z;
        vec3 d_j;
        d_j.x = surface->vertices[i][j + 1].x - surface->vertices[i][j - 1].x;
        d_j.y = surface->vertices[i][j + 1].y - surface->vertices[i][j - 1].y;
        d_j.z = surface->vertices[i][j + 1].z - surface->vertices[i][j - 1].z;
        vec3 normal;
        normal.x = d_i.y * d_j.z - d_i.z * d_j.y;
        normal.y = d_i.z * d_j.x - d_i.x * d_j.z;
        normal.z = d_i.x * d_j.y - d_i.y * d_j.x;
        double length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        if (length > 0.0) {
            normal.x /= length;
            normal.y /= length;
            normal.z /= length;
        }
        surface->normals[i][j].x = normal.x;
        surface->normals[i][j].y = normal.y;
        surface->normals[i][j].z = normal.z;
    }
  }
}

void draw_surface(Surface* surface)
{
  
  for (int i = 0; i < N_ROWS - 1; ++i) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j < N_COLUMNS; ++j) {
        glNormal3f(surface->normals[i][j].x, surface->normals[i][j].y, surface->normals[i][j].z);
        glVertex3f(surface->vertices[i][j].x, surface->vertices[i][j].y, surface->vertices[i][j].z);
        glNormal3f(surface->normals[i + 1][j].x, surface->normals[i + 1][j].y, surface->normals[i + 1][j].z);
        glVertex3f(surface->vertices[i + 1][j].x, surface->vertices[i + 1][j].y, surface->vertices[i + 1][j].z);
    }
    glEnd();
  }
}

