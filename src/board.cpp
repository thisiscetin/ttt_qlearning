#include "board.hpp"

std::string board::status() {
  std::string result = "\n";
  for (int i = 0; i < 9; i++) {
    result += space[i];

    if (i % 3 == 2)
      result += "\n";
  }
  return result;
}

void board::mark(marker m, int coord) {
  if (coord < 0 || coord > 8)
    throw std::out_of_range("out of range marking");
  if (space[coord] != '-')
    throw std::invalid_argument("slot already marked");
  if (m != turn)
    throw std::invalid_argument("wrong turn");

  space[coord] = m;
  marker_count++;
  if (turn == marker::x)
    turn = marker::o;
  else
    turn = marker::x;
}

int board::get_marker_count() {
  return marker_count;
}

std::vector<int> board::get_available_slots() {
  std::vector<int> result;
  for (int i = 0; i < 9; i++) {
    if (space[i] == '-')
      result.push_back(i);
  }
  return result;
}

game_result board::result() {
  // min 5 markers should be on the board
  if (marker_count < 5) {
    return game_result{false, marker::x};
  }

  for (int j = 0; j < 8; j++) {
    if (space[lanes[j][0]] == '-')
      continue;
    if (space[lanes[j][0]] != space[lanes[j][1]])
      continue;
    else if (space[lanes[j][1]] == space[lanes[j][2]])
      return game_result{true, space[lanes[j][0]]};
  }
  return game_result{false, marker::x};
}
