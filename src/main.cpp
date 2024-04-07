#include <ctime>

#include "external_sort.h"
#include "generate_tests.h"
#include "tape.h"

int main(int argc, char** argv) {
    if (argc == 3) {
        Tape tape_in(argv[1]);
        Tape tape_out(argv[2]);
        External_sort sort(tape_in, tape_out);
        sort.tape();
        tape_in.bin_file_to_text();
        tape_out.bin_file_to_text();
    } else if (argc == 4) {
        Tape tape_in(argv[1], argv[3]);
        Tape tape_out(argv[2], argv[3]);
        External_sort sort(tape_in, tape_out);
        sort.tape();
        tape_in.bin_file_to_text();
        tape_out.bin_file_to_text();

    } else if (argc == 5) {
        Tape tape_in(argv[1], argv[3]);
        Tape tape_out(argv[2], argv[3]);
        External_sort sort(tape_in, tape_out, std::atoll(argv[4]));
        sort.tape();
        tape_in.bin_file_to_text();
        tape_out.bin_file_to_text();

    } else {
        std::cout << "Few arguments command line";
    }
}
