//
// Created by justi on 6/13/2023.
//

#include "cassert"

#include "../../src/makocode/cmd.hpp"

void cmd_none() {
    assert(cmd(0, nullptr) == 1);
}

void cmd_encode_no_color_states() {
    const char* argv[] = {"makocode", "encode", "-w", "10", "-h", "10"};

    assert(!cmd(6, argv));
}

void cmd_encode_all_arguments() {
    const char* argv[] = {"makocode", "encode", "-c", "2", "-w", "10", "-h", "10"};

    assert(!cmd(8, argv));
}

void cmd_encode_3_color_states() {
    const char* argv[] = {"makocode", "encode", "-c", "3", "-w", "10", "-h", "10"};

    assert(cmd(8, argv) == 1);
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
    cmd_encode_no_color_states();
    cmd_encode_all_arguments();
    cmd_encode_3_color_states();
    cmd_decode();
    cmd_unknown();
}