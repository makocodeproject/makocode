//
// Created by justi on 7/23/2023.
//

#include "encoder_parameters.hpp"

EncoderParameters::EncoderParameters(uint64_t pageHeightDots, uint64_t pageWidthDots, uint16_t colorStates) {
    this->pageHeightDots = pageHeightDots;
    this->pageWidthDots = pageWidthDots;
    this->colorStates = colorStates;
}

EncoderParameters EncoderParameters::Builder::build() const {
    return {
        pageHeightDots,
        pageWidthDots,
        colorStates
    };
}