#include "tape.h"
#include "external_sort.h"
#include <ctime>

int main(int argc, char **argv) {
    if (argc < 3) {
        Tape tape_in(argv[1], argv[3]);
        Tape tape_out(argv[2], argv[3]);
        for (size_t i = 0; i < tape_in.get_len(); ++i) {
            tape_out.write_tape(tape_in.read_tape());
        }
        tape_in.bin_file_to_text();
        tape_out.bin_file_to_text();
    } else {
        Tape tape_in(argv[1]);
        Tape tape_out(argv[2]);
        for (size_t i = 0; i < tape_in.get_len(); ++i) {
            tape_out.write_tape(tape_in.read_tape());
        }
        tape_in.bin_file_to_text();
        tape_out.bin_file_to_text();
    }
   
   
    // External_sort sort(tape_in, tape_out);
}

