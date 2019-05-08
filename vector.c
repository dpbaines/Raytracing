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

Vector normalize(Vector v) {
    Vector v1;

    v1.x = v.x / magnitude(v);
    v1.y = v.y / magnitude(v);
    v1.z = v.z / magnitude(v);
    return v1;
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

bool intersect_plane(Plane plane, Ray ray, Vector pHit) {
    double denom = dot(ray.vector, plane.normal);
    double num = dot(minus(plane.origin, ray.origin), plane.normal);
    double d = num/denom;

    Vector point;
    point.x = ray.origin.x + ray.vector.x * d;
    point.y = ray.origin.y + ray.vector.y * d;
    point.z = ray.origin.z + ray.vector.z * d;

    if(magnitude(minus(plane.origin, point)) > plane.radius) return false;
    pHit = point;

    return true;
}