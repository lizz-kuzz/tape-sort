#include "generate_tests.h"

static size_t num_tape = 1;

void Generator_Tape::random_generate() {
    std::srand(std::time(nullptr));
    size_t random_len = std::rand() % 10000;

    std::ofstream file_in{PATH_TEST_IN + std::to_string(num_tape),
                            std::ios::trunc};
    std::ofstream file_out{PATH_TEST_OUT + std::to_string(num_tape),
                            std::ios::trunc};

    file_in << random_len << std::endl;
    file_out << random_len << std::endl;

    for (size_t i = 0; i < random_len; ++i) {
        file_in << std::rand() << std::endl;
    }

    ++num_tape;
    file_in.close();
    file_out.close();
}

bool Generator_Tape::compare(Tape& tape_in, Tape& tape_out) {
    std::vector<int32_t> v_in;
    std::vector<int32_t> v_out;

    tape_in.rewind(0, std::ios_base::beg);
    tape_out.rewind(0, std::ios_base::beg);
    for (size_t i = 0; i < tape_in.get_len(); ++i) {
        v_in.push_back(tape_in.read_tape());
        v_out.push_back(tape_out.read_tape());
    }

    std::sort(v_in.begin(), v_in.end());
    std::sort(v_out.begin(), v_out.end());

    for (size_t i = 0; i < tape_in.get_len(); ++i) {
        if (v_in[i] != v_out[i]) {
        return false;
        }
    }
    return true;
}