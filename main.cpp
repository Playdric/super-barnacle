#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <iostream>
#include <omp.h>
#include "EasyBMP.h"
using namespace std;

int main(int argc, char const *argv[]) {
    BMP bmpToGrey;
    BMP bmpToNeg;
    BMP bmpToRescale;
    BMP bmpRescaled;
    int width, w;
    int height, h;
    int R, G, B;
    int negR, negG, negB;
    int grey;
    double start, end;

    //omp_set_num_threads(4);
    //cout << "Nombre de threads : " << omp_get_num_threads() << endl;

    if (argc == 1) { return 0;}
    bmpToGrey.ReadFromFile(argv[1]);
    bmpToNeg.ReadFromFile(argv[1]);
    bmpToRescale.ReadFromFile(argv[1]);
    width = bmpToGrey.TellWidth();
    height = bmpToGrey.TellHeight();

    printf("w=%d,h=%d\n", width, height);
    start = omp_get_wtime();
    #pragma omp parallel for private(h, R, G, B, negR, negG, negB, grey)
    for (w = 0; w < width; w++) {
        for (h = 0; h < height; h++) {
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
 
    if (argc > 2) {
        Rescale(bmpToRescale, 'p', atoi(argv[2]));
    }

    end = omp_get_wtime();

    printf("Time: %fs\n", (end-start));

    bmpToGrey.WriteToFile("grey.bmp");
    bmpToNeg.WriteToFile("negative.bmp");
    bmpToRescale.WriteToFile("rescale.bmp");
    


    return 0;
}
