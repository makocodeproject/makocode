//
// Created by justi on 6/8/2023.
//

#include <cassert>

#include "../decoder.h"
#include "../encoder.h"

int main() {
    int width = 1000;
    int height = 1000;

    encode(height, width);
    int line_count = decode();
    assert(line_count == RGB_CHANNEL_COUNT * width * height + PPM_HEADER_WORDS);

    return 0;
}
