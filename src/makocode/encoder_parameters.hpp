//
// Created by justi on 7/23/2023.
//

#ifndef MAKOCODE_ENCODER_PARAMETERS_HPP
#define MAKOCODE_ENCODER_PARAMETERS_HPP

#include <cstdint>

class EncoderParameters {
public:
    class Builder;

    uint64_t pageHeightDots;
    uint64_t pageWidthDots;
    uint16_t colorStates;

    EncoderParameters(
            uint64_t pageHeightDots,
            uint64_t pageWidthDots,
            uint16_t colorStates);
};

class EncoderParameters::Builder {
public:
    Builder& setPageHeightDots(uint64_t pPageHeightDots) { pageHeightDots = pPageHeightDots; return *this; };
    Builder& setPageWidthDots(uint64_t pPageWidthDots) { pageWidthDots = pPageWidthDots; return *this; };
    Builder& setColorStates(uint16_t cColorStates) { colorStates = cColorStates; return *this; };

    [[nodiscard]] EncoderParameters build() const;

private:
    uint64_t pageHeightDots;
    uint64_t pageWidthDots;
    uint16_t colorStates;
};

#endif //MAKOCODE_ENCODER_PARAMETERS_HPP
