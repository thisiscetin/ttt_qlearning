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

void board::mark(marker m, int pos) {
  if (pos < 0 || pos > 8)
    throw std::out_of_range("out of range marking");
  if (space[pos] != '-')
    throw std::invalid_argument("slot already marked");
  if (m != turn)
    throw std::invalid_argument("wrong turn");

  space[pos] = m;
  marker_count++;
  turn = (turn == marker::x) ? marker::o : marker::x;
}

int board::get_marker_count() {
  return marker_count;
}

marker board::get_turn() {
  return turn;
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
    return game_result {false, marker::x};
  }

  for (int j = 0; j < 8; j++) {
    if (space[lanes[j][0]] == '-')
      continue;

    if (space[lanes[j][0]] != space[lanes[j][1]])
      continue;
    else if (space[lanes[j][1]] == space[lanes[j][2]])
      return game_result {true, space[lanes[j][0]]};
  }
  return game_result {false, marker::x};
}
