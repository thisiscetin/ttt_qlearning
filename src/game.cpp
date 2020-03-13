#include "game.hpp"

const result game::play(marker m, int pos) {
  if (m == last_played)
    throw std::invalid_argument("its not your turn");

  brd->mark(m, pos);
  last_played = m;
  return brd->get_result();
}

const marker game::get_last_played() {
  return last_played;
}
