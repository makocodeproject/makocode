#include "decoder.hpp"
#include "encoder.hpp"
#include "../cxxopts/cxxopts.hpp"

int main(int argc, char** argv) {
    cxxopts::Options options("MyProgram", "One line description of MyProgram");

    options.add_options()
            ("e,encode", "Encode data.", cxxopts::value<std::string>())
            ("d,decode", "Decode data.", cxxopts::value<std::string>())
            ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("encode")) {
        encode(1000, 1000);
    } else if (result.count("decode")) {
        decode();
    } else {
        std::cout << options.help() << std::endl;
    }

    return 0;
}
