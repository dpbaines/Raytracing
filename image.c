#include "image.h"

pixel_t *pixel_at (bitmap_t * bitmap, int x, int y) {
    return bitmap->pixels + bitmap->width * y + x;
}

int save_image(bitmap_t *bitmap, const char *path) {
    FILE *fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte **row_pointers = NULL;

    int status = -1;
    int pixel_size = 3;
    int depth = 8;
    
    fp = fopen(path, "wb");
    if(!fp) {
        printf("Failure to open file...\n");
        return status;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        printf("Failure to create image file...\n");
        fclose(fp);
        return status;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        printf("Failure to create image file...\n");
        fclose(fp);
        return status;
    }

    if(setjmp(png_jmpbuf(png_ptr))) {
        printf("Failure to create image file...\n");
        fclose(fp);
        return status;
    }

    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    row_pointers = png_malloc(png_ptr, bitmap->height * sizeof(png_byte *));
    for(y = 0; y<bitmap->height; y++) {
        png_byte *row = png_malloc(png_ptr, sizeof(uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        //printf("Width for %d", bitmap->width);
        for(x = 0; x < bitmap->width; x++) {
            pixel_t *pixel = pixel_at(bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
            //printf("Starting... %d\n", x);
        }
    }


    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    status = 0;

    for(y=0; y<bitmap->height; y++) {
        png_free(png_ptr, row_pointers[y]);
    }
    png_free(png_ptr, row_pointers);
    
    return status;
}

float HueToRGB(float v1, float v2, float vH) {
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
}

void generate_image(char* name, int *array, int size, int width1, int height1) {
    bitmap_t image;

    image.width = width1;
    image.height = height1;

    image.pixels = calloc (image.width * image.height, sizeof (pixel_t));

    for(int i = 0; i<size; i++) {
        pixel_t colour;
        generate_rainbow(&colour, array[i], size);

        int dx = image.width/size;
        draw_rect(&image, dx*i, dx*i + dx, 0, image.height, colour);
    }
    
    if (save_image(&image, name)) {
        fprintf (stderr, "Error writing file.\n");
    }

    free(image.pixels);
}

void HSLToRGB(int H, float S, float L, int *R, int *G, int *B) {
	if (S == 0)
	{
		*R = *G = *B = (unsigned char)(L * 255);
	}
	else
	{
		float v1, v2;
		float hue = (float)H / 360;

		v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
		v1 = 2 * L - v2;

		*R = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
		*G = (unsigned char)(255 * HueToRGB(v1, v2, hue));
		*B = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
	}
}

int pix (int value, int max) {
    if (value < 0) {
        return 0;
    }
    return (int) (256.0 *((double) (value)/(double) max));
}

void get_colour(pixel_t *colour, int red1, int green1, int blue1) {
    colour->red = red1;
    colour->green = green1;
    colour->blue = blue1;
}

void set_pixel(bitmap_t *bitmap, int x, int y, pixel_t colour) {
    pixel_t *pixel = pixel_at(bitmap, x, y);
    pixel->red = colour.red;
    pixel->green = colour.green;
    pixel->blue = colour.blue;
}

void draw_line(bitmap_t *bitmap, int x1, int x2, int y1, int y2, pixel_t colour) {
    if(x1 < 0 || x2 > bitmap->width || y1 < 0 || y2 > bitmap->height) {
        printf("Invalid draw line\n");
        return;
    }

    double m = ((double)y2 - (double)y1)/((double)x2 - (double)x1);
    int dx = (x2-x1)/abs(x2-x1);
    printf("(%d, %d) to (%d, %d) m = %lf", x1, y1, x2, y2, m);
    for(int x = x1; abs(x)<abs(x2); x += dx) {
        //printf("%d %lf\n", x, (x-x1)*m + y1);
        pixel_t *pixel = pixel_at(bitmap, x, floor((x-x1)*m) + y1);
        pixel->red = colour.red;
        pixel->green = colour.green;
        pixel->blue = colour.blue;
    }
}

void draw_rect(bitmap_t *bitmap, int x1, int x2, int y1, int y2, pixel_t colour) {
    if(x1 < 0 || x2 > bitmap->width || y1 < 0 || y2 > bitmap->height) {
        printf("Invalid draw rect\n");
        return;
    }

    for(int y = y1; abs(y)<abs(y2); y++) {
        for(int x = x1; abs(x)<abs(x2); x++) {
            pixel_t *pixel = pixel_at(bitmap, x, y);
            pixel->red = colour.red;
            pixel->green = colour.green;
            pixel->blue = colour.blue;
        }
    }
}