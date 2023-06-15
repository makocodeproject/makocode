//
// Created by justi on 6/8/2023.
//

#include "cassert"

#include "../../src/makocode/decoder.hpp"
#include "../../src/makocode/encoder.hpp"

void encode_decode_1000_1000() {
    int width = 1000;
    int height = 1000;

    encode(height, width);
    int line_count = decode();

    assert(line_count == RGB_CHANNEL_COUNT * width * height + PPM_HEADER_WORDS);
}

void encode_decode_100_100() {
    int width = 100;
    int height = 100;

    encode(height, width);
    int line_count = decode();

    assert(line_count == RGB_CHANNEL_COUNT * width * height + PPM_HEADER_WORDS);
}

int main() {
    encode_decode_1000_1000();
    encode_decode_100_100();
}