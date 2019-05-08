#ifndef IMAGE_H
#define IMAGE_H

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

typedef struct {
    pixel_t *pixels;
    size_t width;
    size_t height;
} bitmap_t;

pixel_t *pixel_at (bitmap_t * bitmap, int x, int y);
int save_image(bitmap_t *bitmap, const char *path);
void draw_line(bitmap_t *bitmap, int x1, int x2, int y1, int y2, pixel_t colour);
void draw_rect(bitmap_t *bitmap, int x1, int x2, int y1, int y2, pixel_t colour);
void get_colour(pixel_t *colour, int red1, int green1, int blue1);
void HSLToRGB(int H, float S, float L, int *R, int *G, int *B);
void set_pixel(bitmap_t *bitmap, int x, int y, pixel_t colour);

#endif