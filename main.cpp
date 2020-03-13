#include <iostream>
#include <string>
#include "game.hpp"

int main() {
  std::cout << "Welcome to XOX" << std::endl;

  game g = game();
  bool finished = false;

  int pos;
  char m;
  result res;

  while (!finished) {
    std::cout << "Enter marker and pos: ";
    std::cin >> m;
    std::cin >> pos;

    res = g.play(marker(m), pos);
    finished = res.finished;
  }

  std::cout << (res.winner == marker::x ? "X" : "O");
  std::cout << " won." << std::endl;
  return 0;
}
