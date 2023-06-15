//
// Created by justi on 6/13/2023.
//

#include "cassert"

#include "../../src/makocode/cmd.hpp"

void cmd_none() {
    assert(cmd(0, nullptr) == 1);
}

void cmd_encode_10_10() {
    const char* argv[] = {"makocode", "encode", "-w", "10", "-h", "10"};

    assert(!cmd(6, argv));
}

void cmd_decode() {
    const char* argv[] = {"makocode", "decode"};

    assert(!cmd(2, argv));
}

void cmd_unknown() {
    const char* argv[] = {"makocode", "unknown"};

    assert(cmd(2, argv) == 1);
}

int main() {
    cmd_none();
    cmd_encode_10_10();
    cmd_decode();
    cmd_unknown();
}