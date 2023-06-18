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

    file << PPM_HEADER_MAGIC_NUMBER << "\n";
    file << encoderParameters.pageWidthDots << "\n";
    file << encoderParameters.pageHeightDots << "\n";
    file << encoderParameters.colorStates - 1 << "\n";

    uint64_t dotCount = encoderParameters.pageWidthDots * encoderParameters.pageHeightDots;
    for (int i = 0; i < dotCount; i++) {
        uint64_t dotValue = (rng(encoderParameters.colorStates));

        for (int j = 0; j < RGB_CHANNEL_COUNT; j++) {
            file << dotValue << " ";
        }
        file << "\n";
    }

    file.close();

    std::cout << "Image file written." << std::endl;
}