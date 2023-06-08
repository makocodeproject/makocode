//
// Created by justi on 6/7/2023.
//

#include <iostream>
#include <fstream>
using namespace std;

#ifndef MAKOCODE_DECODER_H
#define MAKOCODE_DECODER_H

void decode() {
    ifstream file;
    file.open ("image.ppm");

    int line_count = 0;
    string line;

    while (file >> line) {
        line_count++;
    }

    file.close();

    std::cout << "Image file read, " << line_count << " lines." << std::endl;
}

#endif //MAKOCODE_DECODER_H
