#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include <string>
#include "board.hpp"

class game {
 public:
  game() {
    brd = new board();
  }
  ~game() {
    delete brd;
  }

  game_result play(marker mrk, int pos);
  std::string status();
 private:
  board* brd;
};

#endif // SRC_GAME_HPP_
