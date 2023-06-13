//
// Created by justi on 6/13/2023.
//

#include <cassert>

#include "../src/makocode/cmd.hpp"

int cmd_none() {
    return !cmd(0, nullptr);
}

int cmd_encode_10_10() {
    static const char* argv[] = {"makocode", "encode", "-w", "10", "-h", "10"};

    return cmd(6, argv);
}

int cmd_decode() {
    static const char* argv[] = {"makocode", "decode"};

    return cmd(2, argv);
}

int cmd_unknown() {
    static const char* argv[] = {"makocode", "unknown"};

    return !cmd(2, argv);
}

int main() {
    return
        cmd_none() ||
        cmd_encode_10_10() ||
        cmd_decode() ||
        cmd_unknown();
}