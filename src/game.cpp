#include "game.hpp"

game_result game::play(marker m, int pos) {
  brd->mark(m, pos);
  return brd->result();
}

std::string game::status() {
  std::string result = brd->status() + "turn:";
  result += brd->get_turn() == marker::x ? "x\n" : "y\n";
  return result;
}
