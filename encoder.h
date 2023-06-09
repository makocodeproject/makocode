//
// Created by justi on 6/7/2023.
//

#include <iostream>
#include <fstream>
#include <random>

#ifndef MAKOCODE_ENCODER_H
#define MAKOCODE_ENCODER_H

void encode() {
    mt19937 generator (0);

    ofstream file;
    file.open ("image.ppm");
    int w = 1000;
    int h = 1000;
    int min_val = 0;
    int max_val = 255;

    uniform_real_distribution<double> dis(min_val, max_val + 1);

    file << "P3\n" << w << "\n" << h << "\n" << max_val;

    for (int i = 0; i < w * h * 3; i++) {
        if (i % 3 == 0) {
            file << "\n";
        }

        file << int(dis(generator)) << " ";
    }

    file.close();

    std::cout << "Image file written." << std::endl;
}

#endif //MAKOCODE_ENCODER_H
