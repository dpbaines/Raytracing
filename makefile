rtc:
	gcc main.c image.c vector.c -o rtc -llibpng3 -lzlib1 -m32

rtc-debug:
	gcc -g main.c image.c vector.c -llibpng3 -lzlib1 -m32