#ifndef SRC_BOARD_HPP_
#define SRC_BOARD_HPP_

#include <vector>

enum marker { x = 'x', o = 'o', n = '-' };

struct cross {
  cross(int x_in, int y_in, int z_in) : x(x_in),
    y(y_in), z(z_in) {}
  int x, y, z;
};

struct result {
  bool finished;
  marker winner;
};

static cross* lanes[8] {
  new cross(0, 1, 2),
  new cross(0, 3, 6),
  new cross(0, 4, 8),
  new cross(1, 4, 7),
  new cross(2, 5, 8),
  new cross(2, 4, 6),
  new cross(3, 4, 5),
  new cross(6, 7, 8),
};

class board {
 public:
  board() {
    space = new char[9];
    std::fill_n(space, 9, marker::n);
  }
  ~board() {
    delete space;
  }
  void mark(marker m, int pos);
  char* get_space();
  const std::vector<int> get_available_slots();
  const result get_result();

 private:
  char* space;
};

#endif // SRC_BOARD_HPP_
