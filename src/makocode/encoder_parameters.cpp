//
// Created by Justin Bass on 7/23/2023.
//

#include "encoder_parameters.hpp"

#include <utility>

EncoderParameters::EncoderParameters(
        uint64_t pageHeightDots,
        uint64_t pageWidthDots,
        uint16_t colorStates,
        std::vector<uint8_t> dataPayload) {

    this->pageHeightDots = pageHeightDots;
    this->pageWidthDots = pageWidthDots;
    this->colorStates = colorStates;
    this->dataPayload = std::move(dataPayload);
}

EncoderParameters EncoderParameters::Builder::build() const {
    if (dataPayload.empty()) {
        std::cout << "Warning: No data payload.\n";
    }

    return {
        pageHeightDots,
        pageWidthDots,
        colorStates,
        dataPayload
    };
}