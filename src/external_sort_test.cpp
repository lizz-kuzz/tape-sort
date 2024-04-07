#include "external_sort.h"

#include <gtest/gtest.h>

#include <ctime>

#include "generate_tests.h"
#include "tape.h"

static size_t num_tape = 1;

TEST(test_1, ram_20) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;
    External_sort sort(tape_in, tape_out, 20);

    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}

TEST(test_2, ram_30) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;

    External_sort sort(tape_in, tape_out, 30);
    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}

TEST(test_3, ram_50) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;

    External_sort sort(tape_in, tape_out, 50);
    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}

TEST(test_4, ram_100) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;

    External_sort sort(tape_in, tape_out, 100);
    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}

TEST(test_5, ram_110) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;

    External_sort sort(tape_in, tape_out, 110);
    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}

TEST(test_6, ram_121) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;

    External_sort sort(tape_in, tape_out, 121);
    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}

TEST(test_7, ram_10000) {
    Generator_Tape::random_generate();
    Tape tape_in(PATH_TEST_IN + std::to_string(num_tape));
    Tape tape_out(PATH_TEST_OUT + std::to_string(num_tape));
    ++num_tape;

    External_sort sort(tape_in, tape_out, 10000);
    sort.tape();
    tape_out.bin_file_to_text();
    EXPECT_EQ(Generator_Tape::compare(tape_in, tape_out), true);
}