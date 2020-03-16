#include "catch.hpp"
#include "trainer.hpp"
#include "game.hpp"

TEST_CASE("returns marker as expected", "[trainer/agent]") {
  agent a = agent(marker::x, new strategy {0, 0, 0});

  REQUIRE(a.get_marker() == marker::x);
}

TEST_CASE("play returns first slot when epsilon is -1", "[trainer/agent]"){
  agent a = agent(marker::x, new strategy {0, 0, -1});

  REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
}

TEST_CASE("play returns random slot when epsilon is not -1", "[trainer/agent]"){
  agent a = agent(marker::x, new strategy {0, 0, 1});
  srand(2);

  REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
}

TEST_CASE("play returns maxQ slot after training", "[trainer/agent]") {
  agent a = agent(marker::x, new strategy {1, 0.5, -1});

  REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
  a.learn("ds", "nds", 3, -1);
  REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 2);
  a.learn("ds", "nds", 2, -2);
  REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 1);
  a.learn("ds", "nds", 3, 1);
  REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
}

TEST_CASE("play returns a random move", "[trainer/dummy_agent]") {
  dummy_agent d = dummy_agent();
  srand(-1);

  REQUIRE(d.play(std::vector<int>{1, 2, 3, 4, 5}) == 3);
}

TEST_CASE("trainer_stats returns draws as expected", "[trainer/trainer_stats]") {
  trainer_stats stats = trainer_stats {5, 2, 2 };

  REQUIRE(stats.draw_count() == 1);
}

TEST_CASE("trainer plays a game as expected without exploration", "[trainer/play]") {
  agent* a = new agent(marker::x, new strategy {1, 0.5, -1});
  dummy_agent* d = new dummy_agent();
  // override dummy agent's seeding with time
  srand(0);

  trainer t = trainer(a, d);
  t.play();

  trainer_stats s = t.get_stats();
  REQUIRE(s.game_count == 1);
  REQUIRE(s.agent_won == 1);
  REQUIRE(s.dummy_agent_won == 0);
  REQUIRE(s.draw_count() == 0);
}

TEST_CASE("agent should win over dummy agent over time", "[trainer/play]") {
  strategy* s = new strategy {0.5, 0.2, 1};
  agent* a = new agent(marker::x, s);
  dummy_agent* d = new dummy_agent();

  trainer* t = new trainer(a, d);
  t->play();

/*   trainer_stats s = t.get_stats(); */
  // REQUIRE(s.game_count == 1);
  // REQUIRE(s.dummy_agent_won == 1);

  // t = trainer(a, d);
  // for (int i = 0; i < 100; i++) {
    // t.play();
  // }
  // s = t.get_stats();
  // REQUIRE(s.agent_won == 65);
  // REQUIRE(s.game_count == 100);

  // for (int i = 0; i < 1000; i++) {
    // t.play();
  // }
  // s = t.get_stats();
  // REQUIRE(s.agent_won == 652);
  // REQUIRE(s.game_count == 1100);

  // for (int i = 0; i < 1000; i++) {
    // t.play();
  // }
  // s = t.get_stats();
  // REQUIRE(s.agent_won == 652);
  /* REQUIRE(s.game_count == 1100); */
}
