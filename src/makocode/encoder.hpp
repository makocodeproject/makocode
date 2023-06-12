//
// Created by justi on 6/7/2023.
//

#include "../mt19937/mt19937.hpp"

#include <iostream>
#include <fstream>

#ifndef MAKOCODE_ENCODER_H
#define MAKOCODE_ENCODER_H

int RGB_CHANNEL_COUNT = 3;
int PPM_HEADER_WORDS = 4;

void encode(int height, int width) {
    seed(0);

    ofstream file;
    file.open ("image.ppm");
    unsigned int max_val = 255;

    file << "P3\n" << width << "\n" << height << "\n" << max_val;

    for (unsigned int i = 0; i < width * height * RGB_CHANNEL_COUNT; i++) {
        if (i % RGB_CHANNEL_COUNT == 0) {
            file << "\n";
        }

        file << (unsigned int) (rand_u32() % (max_val + 1)) << " ";
    }

    file.close();

    std::cout << "Image file written." << std::endl;
}

#endif //MAKOCODE_ENCODER_H
