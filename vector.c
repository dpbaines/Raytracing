#include "vector.h"

double magnitude(Vector vector) {
    return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z+vector.z);
}

double dot(Vector vector1, Vector vector2) {
    double x = vector1.x * vector2.x;
    double y = vector1.y * vector2.y;
    double z = vector1.z * vector2.z;

    return x + y + z;
}

Vector minus(Vector vector1, Vector vector2) {
    Vector newVector;
    newVector.x = vector1.x - vector2.x;
    newVector.y = vector1.y - vector2.y;
    newVector.x = vector1.z - vector2.z;
    return newVector;
}

bool intersect_circle(Sphere sphere, Ray ray, Vector *pHit) {
    double determinant = pow(dot( ray.vector,  minus(ray.origin, sphere.position) ), 2)  -
            (  pow(magnitude(minus(ray.origin, sphere.position)) , 2) - 
            sphere.radius*sphere.radius);

    if(determinant == 0) {
        double quad = dot(ray.vector, minus( ray.origin, sphere.position ));
        double d = -quad;

        pHit->x = ray.vector.x * d + ray.origin.x;
        pHit->y = ray.vector.y * d + ray.origin.y;
        pHit->z = ray.vector.z * d + ray.origin.z;

        return true;
    } else if(determinant > 0) {
        double quad = dot(ray.vector, minus( ray.origin, sphere.position ));
        double d = -quad - sqrt(determinant);

        pHit->x = ray.vector.x * d + ray.origin.x;
        pHit->y = ray.vector.y * d + ray.origin.y;
        pHit->z = ray.vector.z * d + ray.origin.z;

        return true;
    }

    return false;
}