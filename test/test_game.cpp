#include "catch.hpp"
#include "game.hpp"

TEST_CASE("playing not in your turn throws an exception", "[board/mark]") {
  game g = game();

  g.play(marker::x, 3);
  REQUIRE_THROWS_WITH(g.play(marker::x, 5), "its not your turn");
}

TEST_CASE("game is played as expected", "[game]") {
  game g = game();

  REQUIRE(g.play(marker::x, 0).finished == false);
  REQUIRE(g.play(marker::o, 1).finished == false);
  REQUIRE(g.play(marker::x, 3).finished == false);
  REQUIRE(g.play(marker::o, 2).finished == false);

  result expected_end = g.play(marker::x, 6);
  REQUIRE(expected_end.finished == true);
  REQUIRE(expected_end.winner == marker::x);
}


