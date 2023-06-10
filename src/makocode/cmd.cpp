#include "decoder.hpp"
#include "encoder.hpp"
#include "../cxxopts/cxxopts.hpp"

int main(int argc, char** argv) {
    const string ENCODE_SUBPROGRAM = "encode";
    const string DECODE_SUBPROGRAM = "decode";

    const string USAGE_STRING =
            "Usage:\n" \
            "  makocode <encode|decode> [OPTION...]\n";

    const string MAKOCODE_DESCRIPTION =
            "MakoCode: A standard for color barcode printing with maximal density, maximal resiliency, and slow " \
            "eventual decoding.";

    if (argc < 2) {
        cout << USAGE_STRING;
        return 1;
    }

    string subprogram = argv[1];

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
        try {
            height = result_encode["height"].as<int>();
            width = result_encode["width"].as<int>();
        } catch (cxxopts::exceptions::option_has_no_value& e) {
            std::cout << "Error:\n" << e.what() << "\n\n" << options_encode.help() << std::endl;
            return 1;
        }

        encode(height, width);
    } else if (subprogram == DECODE_SUBPROGRAM) {
        decode();
    } else {
        cout << "Unknown subprogram: " << subprogram << "\n";
        cout << USAGE_STRING;
    }

    return 0;
}
