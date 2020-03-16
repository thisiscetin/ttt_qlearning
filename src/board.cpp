#include "board.hpp"
#include <iostream>

void board::mark(marker m, int pos) {
  if (pos < 0 || pos > 8)
    throw std::out_of_range("out of range marking");
  if (space[pos] != marker::n)
    throw std::invalid_argument("slot already marked");

  space[pos] = m;
}

const std::vector<char> board::get_space() {
  return space;
}

const std::vector<int> board::get_available_slots() {
  std::vector<int> result = std::vector<int>{};

  for (int i = 0; i < space.size(); i++) {
    if (space[i] == marker::n)
      result.push_back(i);
  }
  return result;
}

const result board::get_result() {
  bool finished = true;

  for (int i = 0; i < 8; i++) {
    if (space[i] == marker::n)
      finished = false;

    if (space[lanes[i]->x] == space[lanes[i]->y] &&
        space[lanes[i]->y] == space[lanes[i]->z]) {
      if (space[lanes[i]->x] == marker::n)
        continue;

      return result {
        true,
        (space[lanes[i]->x] == marker::x) ? marker::x : marker::o
      };
    }
  }
  // iteration is missing last piece as len(lanes) < len(space)
  if (space[8] == marker::n)
    finished = false;
  return result { finished, marker::n };
}
