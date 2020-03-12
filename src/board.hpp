#ifndef SRC_BOARD_HPP_
#define SRC_BOARD_HPP_

#include <string>
#include <vector>

static std::vector<int> lanes[8] {
  std::vector<int> {0, 1, 2},
  std::vector<int> {0, 3, 6},
  std::vector<int> {0, 4, 8},
  std::vector<int> {1, 4, 7},
  std::vector<int> {2, 5, 8},
  std::vector<int> {2, 4, 6},
  std::vector<int> {3, 4, 5},
  std::vector<int> {6, 7, 8},
};

enum marker { x = 'x', o = 'o' };

struct game_result {
  bool finished;
  char mark;
};

class board {
 public:
  board() : marker_count(0), turn(marker::x) {
    space = new char[9]{};
    std::fill_n(space, 9, '-');
  }
  ~board() {
    delete space;
  }

  void mark(marker m, int pos);
  std::vector<int> get_available_slots();
  int get_marker_count();
  marker get_turn();
  std::string status();
  game_result result();

 private:
  char* space;
  int marker_count;
  marker turn;
};
#endif // SRC_BOARD_HPP_
