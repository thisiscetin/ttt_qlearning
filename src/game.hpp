#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include <string>
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
 private:
  board* brd;
  marker last_played;
};

#endif // SRC_GAME_HPP_
