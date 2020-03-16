#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include <string>
#include <vector>
#include <mutex> // NOLINT
#include "board.hpp"

class game {
 public:
  game() {
    brd = new board();
    last_played = marker::n;
  }
  ~game() {
    delete brd;
  }

  const result play(marker mrk, int pos);
  const marker get_last_played();
  const std::vector<int> get_available_slots();
  std::string render_board();
 private:
  board* brd;
  marker last_played;
  std::mutex game_mutex;
};

#endif // SRC_GAME_HPP_
