//
// Created by Justin Bass on 6/17/2023.
//

#include "decoder.hpp"

#include <iostream>
#include <fstream>

int decode() {
    std::ifstream file;
    file.open ("image.ppm");

    int word_count = 0;
    std::string line;

    while (file >> line) {
        word_count++;
    }

    file.close();

    std::cout << "Image file read, " << word_count << " words." << std::endl;

    return word_count;
}