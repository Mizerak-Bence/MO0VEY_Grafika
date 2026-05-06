#include "load.h"

#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024

#define MAX_FACE_POINTS 64

static int count_face_points(const char* text);
static int read_face_points(FacePoint* out_points, int max_points, const char* text);

int load_model(Model* model, const char* filename)
{
    FILE* obj_file;
    int success;

    obj_file = fopen(filename, "r");
    printf("Load model '%s' ...\n", filename);
    if (obj_file == NULL) {
        printf("ERROR: Unable to open '%s' file!\n", filename);
        return FALSE;
    }
    printf("Count the elements ...\n");
    count_elements(model, obj_file);
    printf("Allocate memory for model ...\n");
    allocate_model(model);
    printf("Read model data ...\n");
    fseek(obj_file, 0, SEEK_SET);
    success = read_elements(model, obj_file);
    if (success == FALSE) {
        printf("ERROR: Unable to read the model data!\n");
        return FALSE;
    }
    return TRUE;
}

void count_elements(Model* model, FILE* file)
{
    char line[LINE_BUFFER_SIZE];

    init_model(model);
    while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
        switch (calc_element_type(line)) {
        case NONE:
            break;
        case VERTEX:
            ++model->n_vertices;
            break;
        case TEXTURE_VERTEX:
            ++model->n_texture_vertices;
            break;
        case NORMAL:
            ++model->n_normals;
            break;
        case FACE:
            {
                const int n_points = count_face_points(line);
                if (n_points >= 3) {
                    model->n_triangles += (n_points - 2);
                }
            }
            break;
        }
    }
}

int read_elements(Model* model, FILE* file)
{
    char line[LINE_BUFFER_SIZE];
    int vertex_index;
    int texture_index;
    int normal_index;
    int triangle_index;
    int success;

    vertex_index = 1;
    texture_index = 1;
    normal_index = 1;
    triangle_index = 0;
    while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
        switch (calc_element_type(line)) {
        case NONE:
            break;
        case VERTEX:
            success = read_vertex(&(model->vertices[vertex_index]), line);
            if (success == FALSE) {
                printf("Unable to read vertex data!\n");
                return FALSE;
            }
            ++vertex_index;
            break;
        case TEXTURE_VERTEX:
            success = read_texture_vertex(&(model->texture_vertices[texture_index]), line);
            if (success == FALSE) {
                printf("Unable to read texture vertex data!\n");
                return FALSE;
            }
            ++texture_index;
            break;
        case NORMAL:
            success = read_normal(&(model->normals[normal_index]), line);
            if (success == FALSE) {
                printf("Unable to read normal vector data!\n");
                return FALSE;
            }
            ++normal_index;
            break;
        case FACE:
            {
                FacePoint points[MAX_FACE_POINTS];
                const int n_points = read_face_points(points, MAX_FACE_POINTS, line);
                if (n_points < 3) {
                    printf("Unable to read face data!\n");
                    return FALSE;
                }

                // Fan triangulation: (0, i, i+1)
                for (int i = 1; i < n_points - 1; ++i) {
                    model->triangles[triangle_index].points[0] = points[0];
                    model->triangles[triangle_index].points[1] = points[i];
                    model->triangles[triangle_index].points[2] = points[i + 1];
                    ++triangle_index;
                }
            }
            break;
        }
    }
    return TRUE;
}

static int count_face_points(const char* text)
{
    // Count whitespace-separated tokens after the leading 'f'.
    int count = 0;
    const char* p = text;

    while (*p != 0 && (*p == ' ' || *p == '\t')) {
        ++p;
    }
    if (*p != 'f') {
        return 0;
    }
    ++p;

    while (*p != 0) {
        while (*p != 0 && (*p == ' ' || *p == '\t')) {
            ++p;
        }
        if (*p == 0 || *p == '\n' || *p == '\r') {
            break;
        }
        ++count;
        while (*p != 0 && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
            ++p;
        }
    }

    return count;
}

static int read_face_points(FacePoint* out_points, int max_points, const char* text)
{
    int count = 0;
    const char* p = text;

    while (*p != 0 && (*p == ' ' || *p == '\t')) {
        ++p;
    }
    if (*p != 'f') {
        return 0;
    }
    ++p;

    while (*p != 0) {
        char* endptr;

        while (*p != 0 && (*p == ' ' || *p == '\t')) {
            ++p;
        }
        if (*p == 0 || *p == '\n' || *p == '\r') {
            break;
        }
        if (count >= max_points) {
            printf("Face has too many points (max %d)!\n", max_points);
            return 0;
        }

        out_points[count].vertex_index = (int)strtol(p, &endptr, 10);
        if (endptr == p) {
            return 0;
        }
        p = endptr;

        if (*p != '/') {
            return 0;
        }
        ++p;
        out_points[count].texture_index = (int)strtol(p, &endptr, 10);
        if (endptr == p) {
            return 0;
        }
        p = endptr;

        if (*p != '/') {
            return 0;
        }
        ++p;
        out_points[count].normal_index = (int)strtol(p, &endptr, 10);
        if (endptr == p) {
            return 0;
        }
        p = endptr;

        // Skip to next token
        while (*p != 0 && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
            ++p;
        }

        ++count;
    }

    return count;
}

ElementType calc_element_type(const char* text)
{
    int i;

    i = 0;
    while (text[i] != 0) {
        if (text[i] == 'v') {
            if (text[i + 1] == 't') {
                return TEXTURE_VERTEX;
            }
            else if (text[i + 1] == 'n') {
                return NORMAL;
            }
            else {
                return VERTEX;
            }
        }
        else if (text[i] == 'f') {
            return FACE;
        }
        else if (text[i] != ' ' && text[i] != '\t') {
            return NONE;
        }
        ++i;
    }
    return NONE;
}

int read_vertex(Vertex* vertex, const char* text)
{
    int i;

    i = 0;
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        vertex->x = atof(&text[i]);
    }
    else {
        printf("The x value of vertex is missing!\n");
        return FALSE;
    }
    while (text[i] != 0 && text[i] != ' ') {
        ++i;
    }
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        vertex->y = atof(&text[i]);
    }
    else {
        printf("The y value of vertex is missing!\n");
        return FALSE;
    }
    while (text[i] != 0 && text[i] != ' ') {
        ++i;
    }
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        vertex->z = atof(&text[i]);
    }
    else {
        printf("The z value of vertex is missing!\n");
        return FALSE;
    }
    return TRUE;
}

int read_texture_vertex(TextureVertex* texture_vertex, const char* text)
{
    int i;

    i = 0;
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        texture_vertex->u = atof(&text[i]);
    }
    else {
        printf("The u value of texture vertex is missing!\n");
        return FALSE;
    }
    while (text[i] != 0 && text[i] != ' ') {
        ++i;
    }
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        texture_vertex->v = atof(&text[i]);
    }
    else {
        printf("The v value of texture vertex is missing!\n");
        return FALSE;
    }
    return TRUE;
}

int read_normal(Vertex* normal, const char* text)
{
    int i;

    i = 0;
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        normal->x = atof(&text[i]);
    }
    else {
        printf("The x value of normal vector is missing!\n");
        return FALSE;
    }
    while (text[i] != 0 && text[i] != ' ') {
        ++i;
    }
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        normal->y = atof(&text[i]);
    }
    else {
        printf("The y value of normal vector is missing!\n");
        return FALSE;
    }
    while (text[i] != 0 && text[i] != ' ') {
        ++i;
    }
    while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
        ++i;
    }
    if (text[i] != 0) {
        normal->z = atof(&text[i]);
    }
    else {
        printf("The z value of normal vector is missing!\n");
        return FALSE;
    }
    return TRUE;
}

int read_triangle(Triangle* triangle, const char* text)
{
    int point_index;
    int i;

    i = 0;
    for (point_index = 0; point_index < 3; ++point_index) {
        while (text[i] != 0 && is_numeric(text[i]) == FALSE) {
            ++i;
        }
        if (text[i] != 0) {
            triangle->points[point_index].vertex_index = atoi(&text[i]);
        }
        else {
            printf("The vertex index of the %d. points is missing!\n", point_index + 1);
            return FALSE;
        }
        while (text[i] != 0 && text[i] != '/') {
            ++i;
        }
        ++i;
        if (text[i] != 0) {
            triangle->points[point_index].texture_index = atoi(&text[i]);
        }
        else {
            printf("The texture index of the %d. points is missing!\n", point_index + 1);
            return FALSE;
        }
        while (text[i] != 0 && text[i] != '/') {
            ++i;
        }
        ++i;
        if (text[i] != 0) {
            triangle->points[point_index].normal_index = atoi(&text[i]);
        }
        else {
            printf("The normal index of the %d. points is missing!\n", point_index + 1);
            return FALSE;
        }
        while (text[i] != 0 && text[i] != ' ') {
            ++i;
        }
    }
    return TRUE;
}

int is_numeric(char c)
{
    if ((c >= '0' && c <= '9') || c == '-' || c == '.') {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
