#include <stdio.h>
#include "vector.h"

#define _PI 3.141592658

pixel_t trace(Ray ray, Sphere sphere, Light light) {
    double d_near;
    Vector pHit;

    if(intersect_circle(sphere, ray, &pHit)) {
        Ray shadowRay;
        shadowRay.vector = minus(light.plane.origin, pHit);
        bool isShadow = false;

        Vector hit;

        if(intersect_circle(sphere, shadowRay, &hit)) isShadow = true;

        pixel_t colour;
        colour.red = 0;
        colour.green = 0;
        colour.blue = 0;

        //if(isShadow) return colour;
        //else {
            colour.red = sphere.colour.red * light.brightness;
            colour.green = sphere.colour.green * light.brightness;
            colour.blue = sphere.colour.green * light.brightness;

            printf("%d %d %d\n", colour.red, colour.green, colour.blue);
            return colour;
        //}
    }
}

void render(Sphere sphere, Light light, int width, int height) {

    double iWidth = 1/(float) width;
    double iHeight = 1/(float) height;
    double fov = 30;
    double aspect = width/(float) height;
    double angle = tan(_PI * 0.5 * fov / 180);

    bitmap_t bitmap;
    bitmap.pixels = calloc (width * height, sizeof (pixel_t));
    bitmap.height = height;
    bitmap.width = width;

    for(int y = 0; y<height; y++) {
        for(int x = 0; x<width; x++) {
            double xx = (2 * ((x+0.5) * iWidth) - 1) * angle * aspect;
            double yy = (1 - 2* ( (y + 0.5) * iHeight ) ) * angle;

            Ray ray;
            ray.origin.x = 0;
            ray.origin.y = 0;
            ray.origin.z = 0;

            ray.vector.x = xx;
            ray.vector.y = yy;
            ray.vector.z = -1;

            ray.vector = normalize(ray.vector);

            pixel_t pixel = trace(ray, sphere, light);
            set_pixel(&bitmap, x, y, pixel);
            //printf("Intersection :%d\n", pixel.red);
        }
        printf("%d\n", y);
    }

    printf("Saving image...\n");

    save_image(&bitmap, "render1.png");
    free(bitmap.pixels);
}

int main() {
    const int width = 640;
    const int height = 480;

    Sphere sphere;
    sphere.colour.red = 255;
    sphere.colour.green = 255;
    sphere.colour.blue = 255;
    sphere.radius = 3;
    sphere.position.x = 5;
    sphere.position.y = 0;
    sphere.position.z = -20;

    Light light;
    light.brightness = 1;
    light.plane.origin.x = 0;
    light.plane.origin.y = 20;
    light.plane.origin.z = -30;
    light.plane.radius = 5;
    render(sphere, light, width, height);

    return 0;
}