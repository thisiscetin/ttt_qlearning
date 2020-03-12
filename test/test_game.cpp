#include "catch.hpp"
#include "game.hpp"

TEST_CASE("game is played as expected, play 0", "[game]") {
  game g = game();

  REQUIRE(g.play(marker::x, 0).finished == false);
  REQUIRE(g.status() == "\nx--\n---\n---\nturn:y\n");
  REQUIRE(g.play(marker::o, 1).finished == false);
  REQUIRE(g.status() == "\nxo-\n---\n---\nturn:x\n");
  REQUIRE(g.play(marker::x, 3).finished == false);
  REQUIRE(g.status() == "\nxo-\nx--\n---\nturn:y\n");
  REQUIRE(g.play(marker::o, 2).finished == false);
  REQUIRE(g.status() == "\nxoo\nx--\n---\nturn:x\n");

  game_result expected_end = g.play(marker::x, 6);
  REQUIRE(g.status() == "\nxoo\nx--\nx--\nturn:y\n");
  REQUIRE(expected_end.finished == true);
  REQUIRE(expected_end.mark == marker::x);
}


