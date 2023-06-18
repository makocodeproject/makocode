//
// Created by justi on 6/17/2023.
//

#include "encoder.hpp"

#include "constants.hpp"
#include "../pcg/pcg_random.hpp"

#include <iostream>
#include <fstream>

void encode(EncoderParameters encoderParameters) {
    pcg64 rng(0);

    std::ofstream file;
    file.open ("image.ppm");
    int max_val = 255;

    file << "P3\n" << encoderParameters.pageWidthDots << "\n" << encoderParameters.pageHeightDots << "\n" << max_val;

    for (int i = 0; i < encoderParameters.pageWidthDots * encoderParameters.pageHeightDots * RGB_CHANNEL_COUNT; i++) {
        if (i % RGB_CHANNEL_COUNT == 0) {
            file << "\n";
        }

        file << uint64_t (rng(max_val + 1)) << " ";
    }

    file.close();

    std::cout << "Image file written." << std::endl;
}