#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "stdlib.h"
#include "tape.h"
const size_t DEFAULT_RAM_SIZE = 100;

class External_sort {
    public:
    External_sort(Tape& input, Tape& output, size_t ram_size = DEFAULT_RAM_SIZE);
    ~External_sort() = default;
    void sort_stage(std::vector<int32_t>& ram_memory, size_t& i);
    void merge_stage(std::vector<int32_t>& ram_memory, Tape& tmp_1, Tape& tmp_2,
                    size_t& i);
    int tape();

    private:
    Tape& input_;
    Tape& output_;
    size_t ram_size;
    size_t tape_len;
};