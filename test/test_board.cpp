#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "board.hpp"

TEST_CASE("Initializes board with default values", "[board]") {
  board b = board();

  REQUIRE(b.status() == "\n---\n---\n---\n");
}

TEST_CASE("Marks the space according to type as expected", "[board]") {
  board b = board();

  b.mark(marker::x, 0);
  REQUIRE(b.status() == "\nx--\n---\n---\n");
  b.mark(marker::o, 1);
  REQUIRE(b.status() == "\nxo-\n---\n---\n");
  b.mark(marker::x, 8);
  REQUIRE(b.status() == "\nxo-\n---\n--x\n");
}

TEST_CASE("Keeps track of marker count", "[board]") {
  board b = board();
  REQUIRE(b.get_marker_count() == 0);

  b.mark(marker::x, 0);
  b.mark(marker::o, 1);
  b.mark(marker::x, 8);
  REQUIRE(b.get_marker_count() == 3);
}

TEST_CASE("Out of range marking throws", "[board]") {
  board b = board();

  REQUIRE_THROWS_WITH(b.mark(marker::x, 9), "out of range marking");
  REQUIRE_THROWS_WITH(b.mark(marker::x, -1), "out of range marking");
}

TEST_CASE("already market slot throws", "[board]") {
  board b = board();

  b.mark(marker::x, 3);
  REQUIRE_THROWS_WITH(b.mark(marker::o, 3), "slot already marked");
  REQUIRE_THROWS_WITH(b.mark(marker::x, 3), "slot already marked");
}

TEST_CASE("skipping ones turn throws", "[board]") {
  board b = board();

  b.mark(marker::x, 3);
  REQUIRE_THROWS_WITH(b.mark(marker::x, 2), "wrong turn");
}

TEST_CASE("returns available slots as expected", "[board]") {
  board b = board();
  REQUIRE(b.get_available_slots() == std::vector<int>{0, 1, 2, 3, 4, 5,
      6, 7, 8});

  b.mark(marker::x, 1);
  b.mark(marker::o, 2);
  b.mark(marker::x, 5);
  REQUIRE(b.get_available_slots() == std::vector<int>{0, 3, 4, 6, 7, 8});
}

TEST_CASE("returns false if game can't be finished", "[board/gameend]") {
  board b = board();
  REQUIRE(b.result().finished == false);

  b.mark(marker::x, 1);
  b.mark(marker::o, 2);
  b.mark(marker::x, 0);
  b.mark(marker::o, 8);
  REQUIRE(b.result().finished == false);
}

TEST_CASE("returns true and marker if game is finished 0", "[board/gameend]") {
  board b = board();

  b.mark(marker::x, 0);
  b.mark(marker::o, 3);
  b.mark(marker::x, 1);
  b.mark(marker::o, 4);
  REQUIRE(b.result().finished == false);

  b.mark(marker::x, 2);
  REQUIRE(b.result().finished == true);
  REQUIRE(b.result().mark == 'x');
}

TEST_CASE("returns true and marker if game is finished 1", "[board/gameend]") {
  board b = board();

  b.mark(marker::x, 0);
  b.mark(marker::o, 2);
  b.mark(marker::x, 1);
  b.mark(marker::o, 4);
  REQUIRE(b.result().finished == false);

  b.mark(marker::x, 5);
  REQUIRE(b.result().finished == false);

  b.mark(marker::o, 6);
  REQUIRE(b.result().finished == true);
  REQUIRE(b.result().mark == 'o');
}
