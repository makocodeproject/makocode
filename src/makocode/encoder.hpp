//
// Created by justi on 6/7/2023.
//

#ifndef MAKOCODE_ENCODER_H
#define MAKOCODE_ENCODER_H

#include <cstdint>

class EncoderParameters {
    public:
        uint64_t pageHeightDots;
        uint64_t pageWidthDots;
        uint16_t colorStates;

        EncoderParameters(
                uint64_t pageHeightDots,
                uint64_t pageWidthDots,
                uint16_t colorStates) {
            this->pageHeightDots = pageHeightDots;
            this->pageWidthDots = pageWidthDots;
            this->colorStates = colorStates;
        }
};

void encode(EncoderParameters encoderParameters);

#endif //MAKOCODE_ENCODER_H
