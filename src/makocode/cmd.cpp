#include "cmd.hpp"

#include "decoder.hpp"
#include "encoder.hpp"
#include "../cxxopts/cxxopts.hpp"

#include <iostream>

int cmd(int argc, const char** argv) {
    const std::string ENCODE_SUBPROGRAM = "encode";
    const std::string DECODE_SUBPROGRAM = "decode";

    const std::string USAGE_STRING =
            "Usage:\n" \
            "  makocode <encode|decode> [OPTION...]\n";

    const std::string MAKOCODE_DESCRIPTION =
            "MakoCode: A standard for color barcode printing with maximal density, maximal resiliency, and slow " \
            "eventual decoding.";

    if (argc < 2) {
        std::cout << USAGE_STRING;
        return 1;
    }

    std::string subprogram = argv[1];

    if (subprogram == ENCODE_SUBPROGRAM) {
        cxxopts::Options options_encode(
                "makocode encode",
                MAKOCODE_DESCRIPTION);

        options_encode.add_options()
                ("h,height", "Height.", cxxopts::value<int>())
                ("w,width", "Width.", cxxopts::value<int>());

        auto result_encode = options_encode.parse(argc, argv);

        int height;
        int width;

        height = result_encode["height"].as<int>();
        width = result_encode["width"].as<int>();

        encode(height, width);
    } else if (subprogram == DECODE_SUBPROGRAM) {
        decode();
    } else {
        std::cout << "Unknown subprogram: " << subprogram << "\n";
        std::cout << USAGE_STRING;

        return 1;
    }

    return 0;
}
