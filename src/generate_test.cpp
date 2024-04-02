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
    num_tape++;
    file_in.close();
    file_out.close();
}