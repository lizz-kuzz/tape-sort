#pragma once 

#include <iostream>
#include <fstream>
#include "tape.h"


class External_sort {
public:
    External_sort(Tape& input, Tape& output): input_(input), output_(output) {

    };
    ~External_sort() = default;
    int tape_sort();
private:
    Tape& input_;
    Tape& output_;
};