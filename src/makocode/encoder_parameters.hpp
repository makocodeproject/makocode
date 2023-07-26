//
// Created by Justin Bass on 7/23/2023.
//

#ifndef MAKOCODE_ENCODER_PARAMETERS_HPP
#define MAKOCODE_ENCODER_PARAMETERS_HPP

#include <cstdint>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

class EncoderParameters {
public:
    class Builder;

    uint64_t pageHeightDots;
    uint64_t pageWidthDots;
    uint16_t colorStates;
    std::vector<uint8_t> dataPayload;

    EncoderParameters(
            uint64_t pageHeightDots,
            uint64_t pageWidthDots,
            uint16_t colorStates,
            std::vector<uint8_t> dataPayload);
};

class EncoderParameters::Builder {
public:
    Builder& setPageHeightDots(uint64_t pPageHeightDots) { pageHeightDots = pPageHeightDots; return *this; };
    Builder& setPageWidthDots(uint64_t pPageWidthDots) { pageWidthDots = pPageWidthDots; return *this; };
    Builder& setColorStates(uint16_t cColorStates) { colorStates = cColorStates; return *this; };

    // Useful for testing
    Builder& setDataPayload(std::vector<uint8_t> dDataPayload) { dataPayload = std::move(dDataPayload); return *this; };

    Builder& setDataPayload(const std::string& dataPayloadFileLocation) {
        std::ifstream file (dataPayloadFileLocation, std::ios::binary);
        if (file.is_open()) {
            std::streampos size;

            char * fileData;

            size = file.tellg();
            fileData = new char[size];

            file.seekg(0, std::ios::beg);
            file.read(fileData, size);
            file.close();

            for(int i = 0; i < size; i++) {
                dataPayload.push_back((uint8_t) (*(fileData + i)));
            }

            delete[] fileData;
        } else {
            std::cout << "ERROR: Cannot read file at " << dataPayloadFileLocation;
        }

        return *this;
    };

    [[nodiscard]] EncoderParameters build() const;

private:
    uint64_t pageHeightDots;
    uint64_t pageWidthDots;
    uint16_t colorStates;
    std::vector<uint8_t> dataPayload;
};

#endif //MAKOCODE_ENCODER_PARAMETERS_HPP
