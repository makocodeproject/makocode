//
// Created by Justin Bass on 6/8/2023.
//

#include "cassert"

#include "../../src/makocode/constants.hpp"
#include "../../src/makocode/decoder.hpp"
#include "../../src/makocode/encoder.hpp"

void encode_decode_1000_1000() {
    uint64_t pageHeightDots = 1000;
    uint64_t pageWidthDots = 1000;
    uint16_t colorStates = 2;

    EncoderParameters encoderParameters = EncoderParameters(
            pageHeightDots,
            pageWidthDots,
            colorStates,
            {0, 1, 0, 1, 0});

    encode(encoderParameters);
    int line_count = decode();

    assert(line_count == RGB_CHANNEL_COUNT * pageHeightDots * pageWidthDots + PPM_HEADER_WORDS);
}

void encode_decode_100_100() {
    uint64_t pageHeightDots = 100;
    uint64_t pageWidthDots = 100;
    uint16_t colorStates = 2;

    EncoderParameters encoderParameters = EncoderParameters(
            pageHeightDots,
            pageWidthDots,
            colorStates,
            {0, 1, 0, 1, 0});

    encode(encoderParameters);
    int line_count = decode();

    assert(line_count == RGB_CHANNEL_COUNT * pageHeightDots * pageWidthDots + PPM_HEADER_WORDS);
}

int main() {
    encode_decode_1000_1000();
    encode_decode_100_100();
}