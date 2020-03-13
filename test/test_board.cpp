#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "board.hpp"

TEST_CASE("Out of range marking throws", "[board/mark]") {
  board b = board();

  REQUIRE_THROWS_WITH(b.mark(marker::x, 9), "out of range marking");
  REQUIRE_THROWS_WITH(b.mark(marker::x, -1), "out of range marking");
}

TEST_CASE("already market slot throws", "[board/mark]") {
  board b = board();

  b.mark(marker::x, 3);
  REQUIRE_THROWS_WITH(b.mark(marker::o, 3), "slot already marked");
  REQUIRE_THROWS_WITH(b.mark(marker::x, 3), "slot already marked");
}

TEST_CASE("returns available slots as expected", "[board/get_avaliable_slots]") {
  board b = board();
  REQUIRE(b.get_available_slots() == std::vector<int>{0, 1, 2, 3, 4, 5,
      6, 7, 8});

  b.mark(marker::x, 1);
  b.mark(marker::o, 2);
  b.mark(marker::x, 5);
  REQUIRE(b.get_available_slots() == std::vector<int>{0, 3, 4, 6, 7, 8});
}

TEST_CASE("return result when draw as expected", "[board/get_result]") {
  board b = board();

  b.mark(marker::x, 1);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::o, 0);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::x, 3);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::o, 2);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::x, 4);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::o, 5);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::x, 6);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::o, 7);
  REQUIRE(b.get_result().finished == false);
  b.mark(marker::x, 8);

  REQUIRE(b.get_result().finished == true);
  REQUIRE(b.get_result().winner == marker::n);
}

TEST_CASE("return result when x won as expected", "[board/get_result]") {
  board b = board();

  b.mark(marker::x, 0);
  b.mark(marker::o, 1);
  b.mark(marker::x, 4);
  b.mark(marker::o, 7);
  b.mark(marker::x, 8);

  REQUIRE(b.get_result().finished == true);
  REQUIRE(b.get_result().winner == marker::x);
}

TEST_CASE("return result when o won as expected", "[board/get_result]") {
  board b = board();

  b.mark(marker::o, 0);
  b.mark(marker::x, 1);
  b.mark(marker::o, 3);
  b.mark(marker::x, 5);
  b.mark(marker::o, 6);

  REQUIRE(b.get_result().finished == true);
  REQUIRE(b.get_result().winner == marker::o);
}
