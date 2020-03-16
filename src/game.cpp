#include "game.hpp"

const result game::play(marker m, int pos) {
  std::lock_guard<std::mutex> guard(game_mutex);

  if (m == last_played)
    throw std::invalid_argument("its not your turn");

  brd->mark(m, pos);
  last_played = m;
  return brd->get_result();
}

const marker game::get_last_played() {
  return last_played;
}

std::string game::render_board() {
  const std::vector<char> space = brd->get_space();

  std::string res = "";
  for (int i = 0; i < space.size(); i++) {

    if (i % 3 == 0 && i > 0)
      res += "\n";
    res += space[i];
  }
  return res + "\n";
}

const std::vector<int> game::get_available_slots() {
  std::lock_guard<std::mutex> guard(game_mutex);

  return brd->get_available_slots();
}
