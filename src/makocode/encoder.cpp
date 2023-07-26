//
// Created by Justin Bass on 6/17/2023.
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

    // Write data
    for(uint8_t data : encoderParameters.dataPayload) {
        for (int j = 0; j < RGB_CHANNEL_COUNT; j++) {
            file << data << " ";
        }
        file << "\n";
    }

    // Pad with 1's
    for(int i = 0; i < dotCount - encoderParameters.dataPayload.size(); i++) {
        for (int j = 0; j < RGB_CHANNEL_COUNT; j++) {
            file << 1 << " ";
        }
        file << "\n";
    }

    file.close();

    std::cout << "Image file written." << std::endl;
}