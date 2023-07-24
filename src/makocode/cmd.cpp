#include "cmd.hpp"

#include "decoder.hpp"
#include "encoder.hpp"
#include "encoder_parameters.hpp"
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
                ("h,pageHeightDots", "Page Height Dots.", cxxopts::value<uint64_t>())
                ("w,pageWidthDots", "Page Width Dots.", cxxopts::value<uint64_t>())
                ("c,colorStates", "Color States.", cxxopts::value<uint16_t>()->default_value("2"));

        auto result_encode = options_encode.parse(argc, argv);

        uint64_t pageHeightDots = result_encode["pageHeightDots"].as<uint64_t>();
        uint64_t pageWidthDots = result_encode["pageWidthDots"].as<uint64_t>();
        uint16_t colorStates = result_encode["colorStates"].as<uint16_t>();

        if (colorStates != 2) {
            std::cout << "Currently only 2 color states (black and white) are supported.";

            return 1;
        }

        EncoderParameters encoderParameters = EncoderParameters::Builder()
                .setPageHeightDots(pageHeightDots)
                .setPageWidthDots(pageWidthDots)
                .setColorStates(colorStates)
                .build();

        encode(encoderParameters);
    } else if (subprogram == DECODE_SUBPROGRAM) {
        decode();
    } else {
        std::cout << "Unknown subprogram: " << subprogram << "\n";
        std::cout << USAGE_STRING;

        return 1;
    }

    return 0;
}
