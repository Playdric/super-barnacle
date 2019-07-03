#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <omp.h>
#include "EasyBMP.h"

int main(int argc, char const *argv[]) {
    BMP bmpToGray;

    bmpToGray.ReadFromFile("bitmap.BMP");

    printf("%d", bmpToGray.TellWidth());

    return 0;
}
