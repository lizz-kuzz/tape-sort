#include "external_sort.h"

#include "tape.h"

External_sort::External_sort(Tape& input, Tape& output, size_t ram_size)
    : input_(input), output_(output), ram_size(ram_size) {
  if (input_.get_len() != output_.get_len()) {
    std::cout << "Lens shoud be similar" << std::endl;
  }  //исключение

  tape_len = input_.get_len();
}

const std::string tmp_file_name = "../tmp/tmp_";

int External_sort::tape() {
  Tape tmp_1(tmp_file_name + "1", tape_len);
  Tape tmp_2(tmp_file_name + "2", tape_len);

  std::vector<int32_t> ram_memory;

  size_t count_numbers = 0;

  sort_stage(ram_memory, count_numbers);

  for (int32_t number : ram_memory) {
    tmp_1.write_tape(number);
  }

  bool tmp_1_free = false;
  bool tmp_2_free = true;

  while (count_numbers < tape_len) {
    if (!tmp_1_free) {
      merge_stage(ram_memory, tmp_1, tmp_2, count_numbers);
      tmp_2_free = false;
      tmp_1_free = true;
    } else if (!tmp_2_free) {
      merge_stage(ram_memory, tmp_2, tmp_1, count_numbers);
      tmp_2_free = true;
      tmp_1_free = false;
    }
  }

  if (!tmp_1_free) {
    output_.copy(tmp_1);
  } else if (!tmp_2_free) {
    output_.copy(tmp_2);
  }

  tmp_1.bin_file_to_text();
  tmp_2.bin_file_to_text();

  return 0;
}

void External_sort::sort_stage(std::vector<int32_t>& ram_memory, size_t& i) {
  ram_memory.clear();

  for (size_t j = 0; j < ram_size - 1 && i != tape_len; ++j, ++i) {
    ram_memory.push_back(input_.read_tape());
  }
  std::sort(ram_memory.begin(), ram_memory.end());
}

void External_sort::merge_stage(std::vector<int32_t>& ram_memory, Tape& tmp_1,
                                Tape& tmp_2, size_t& i) {
  sort_stage(ram_memory, i);
  size_t capacity = tmp_1.get_cur_position();

  tmp_1.rewind(0, std::ios_base::beg);
  tmp_2.rewind(0, std::ios_base::beg);

  int32_t num_1 = tmp_1.read_tape();
  for (size_t k = 0; k < capacity + ram_size - 1; ++k) {
    if (!ram_memory.empty() && num_1 >= *ram_memory.begin()) {
      tmp_2.write_tape(*ram_memory.begin());
      ram_memory.erase(ram_memory.begin());
    } else {
      tmp_2.write_tape(num_1);
      num_1 = tmp_1.read_tape();
    }
  }
}