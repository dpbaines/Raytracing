#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <math.h>
#include "image.h"

typedef struct vector  {
    double x;
    double y;
    double z;
} Vector;

typedef struct ray {
    Vector origin;
    Vector vector;
} Ray;

typedef struct sphere {
    Vector position;
    double radius;
    pixel_t colour;
} Sphere;

typedef struct disc {
    Vector origin;
    Vector normal;
    double radius;
} Plane;

typedef struct light {
    Plane plane;
    double brightness;
} Light;

bool intersect_circle(Sphere sphere, Ray ray, Vector *pHit);
Vector minus(Vector vector1, Vector vector2);
Vector normalize(Vector v);

#endif