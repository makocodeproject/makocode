//
// Created by justi on 6/7/2023.
//

#include <iostream>
#include <fstream>
using namespace std;

#ifndef MAKOCODE_DECODER_H
#define MAKOCODE_DECODER_H

int decode() {
    ifstream file;
    file.open ("image.ppm");

    int word_count = 0;
    string line;

    while (file >> line) {
        word_count++;
    }

    file.close();

    std::cout << "Image file read, " << word_count << " words." << std::endl;

    return word_count;
}

#endif //MAKOCODE_DECODER_H
