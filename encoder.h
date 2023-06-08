//
// Created by justi on 6/7/2023.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#ifndef MAKOCODE_ENCODER_H
#define MAKOCODE_ENCODER_H

void encode() {
    srand(0);

    ofstream file;
    file.open ("image.ppm");
    int w = 1000;
    int h = 1000;
    int depth = 255;
    file << "P3\n" << w << "\n" << h << "\n" << depth;

    for (int i = 0; i < w * h * 3; i++) {
        if (i % 3 == 0) {
            file << "\n";
        }

        file << rand() % (depth + 1) << " ";
    }

    file.close();

    std::cout << "Image file written." << std::endl;
}

#endif //MAKOCODE_ENCODER_H
