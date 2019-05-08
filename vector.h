#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <math.h>

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
} Sphere;

typedef struct plane {
    Vector vector1;
    Vector vector2;
} Plane;

typedef struct light {
    Plane plane;
    double brightness;
} Light;

#endif VECTOR_H