#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <omp.h>
#include "EasyBMP.h"

int main(int argc, char const *argv[]) {
    BMP bmpToGrey;
    BMP bmpToNeg;
    BMP bmpToRescale;
    BMP bmpRescaled;
    int width, nWidth;
    int height, nHeight;
    int R, G, B;
    int negR, negG, negB;
    int grey;
    double start, end;

    bmpToGrey.ReadFromFile("MARBLES.BMP");
    bmpToNeg.ReadFromFile("MARBLES.BMP");
    bmpToRescale.ReadFromFile("MARBLES.BMP");
    width = bmpToGrey.TellWidth();
    height = bmpToGrey.TellHeight();

    printf("w=%d,h=%d\n", width, height);
    start = omp_get_wtime();
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            R = bmpToGrey(w, h)->Red;
            G = bmpToGrey(w, h)->Green;
            B = bmpToGrey(w, h)->Blue;

            grey = (R + G + B) / 3;
            bmpToGrey(w, h)->Red = bmpToGrey(w, h)->Green = bmpToGrey(w, h)->Blue = grey;

            negR = 255 - R;
            negG = 255 - G;
            negB = 255 - B;
            bmpToNeg(w, h)->Red = negR;
            bmpToNeg(w, h)->Green = negG;
            bmpToNeg(w, h)->Blue = negB;
        }
    }

    nWidth = width * 30 / 100;
    nHeight = height * 30 / 100;

    bmpRescaled.SetSize(nWidth, nHeight);

    

    end = omp_get_wtime();

    printf("Time: %fs\n", (end-start));

    bmpToGrey.WriteToFile("grey.bmp");
    bmpToNeg.WriteToFile("negative.bmp");
    bmpToRescale.WriteToFile("rescale.bmp");
    


    return 0;
}
