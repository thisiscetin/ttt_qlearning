
#include "catch.hpp"
#include "trainer.h"
#include "game.h"

TEST_CASE("returns marker as expected", "[trainer/agent]") {
    agent a = agent(marker::x, new strategy{0, 0, 0});

    REQUIRE(a.get_marker() == marker::x);
}

TEST_CASE("play returns first slot when epsilon is -1", "[trainer/agent]") {
    agent a = agent(marker::x, new strategy{0, 0, -1});

    REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 1);
}

TEST_CASE("play returns random slot when epsilon is not -1", "[trainer/agent]") {
    agent a = agent(marker::x, new strategy{0, 0, 1});
    srand(2);

    REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
}

TEST_CASE("play returns maxQ slot after training", "[trainer/agent]") {
    agent a = agent(marker::x, new strategy{1, 0.5, -1});

    REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 1);
    a.learn("ds", "nds", 1, -1);

    REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 2);
    a.learn("ds", "nds", 2, -2);
    REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
    a.learn("ds", "nds", 3, 1);
    REQUIRE(a.play("ds", std::vector<int>{1, 2, 3}) == 3);
}

TEST_CASE("play returns a random move", "[trainer/dummy_agent]") {
    dummy_agent d = dummy_agent();
    srand(-1);

    REQUIRE(d.play(std::vector<int>{1, 2, 3, 4, 5}) == 3);
}

TEST_CASE("trainer_stats returns draws as expected", "[trainer/trainer_stats]") {
    trainer_stats stats = trainer_stats{5, 2, 2};

    REQUIRE(stats.draw_count() == 1);
}

TEST_CASE("trainer plays a game as expected without exploration", "[trainer/play]") {
    agent *a = new agent(marker::x, new strategy{1, 0.5, -1});
    agent *d = new agent(marker::o, new strategy{1, 1, 2});
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
    agent *a = new agent(marker::x, new strategy{0.5, 0.5, 10});
    agent *d = new agent(marker::o, new strategy{1, 1, 2});

    trainer t = trainer(a, d);
    t.play();

    for (int i = 0; i < 10000; i++) {
        t.play();
    }
    trainer_stats s0 = t.get_stats();
    float won_ratio0 = float(s0.agent_won) / float(s0.game_count);

    for (int i = 0; i < 10000; i++) {
        t.play();
    }
    trainer_stats s1 = t.get_stats();
    float won_ratio1 = float(s1.agent_won) / float(s1.game_count);

    REQUIRE(won_ratio1 > won_ratio0);

    for (int i = 0; i < 10000; i++) {
        t.play();
    }
    trainer_stats s2 = t.get_stats();
    float won_ratio2 = float(s2.agent_won) / float(s2.game_count);

    REQUIRE(won_ratio2 > won_ratio1);
}