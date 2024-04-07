#pragma once
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "tape.h"
const std::string PATH_TEST_IN = "../res/tape_test_in";
const std::string PATH_TEST_OUT = "../res/tape_test_out";

namespace Generator_Tape {
void random_generate();
bool compare(Tape& tape_in, Tape& tape_out);
}  // namespace Generator_Tape