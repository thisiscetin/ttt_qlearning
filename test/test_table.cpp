//
// Created by M. Cetin on 3/17/20.
//

#include "catch.hpp"
#include "table.h"

TEST_CASE("snapshot updated action to a new value", "[snapshot]") {
    snapshot s = snapshot(std::vector<int> {1, 2, 3});

    s.update(2, 1.69);
    REQUIRE(s.get_Q(1) == 0);
    REQUIRE(s.get_Q(2) == 1.69f);
    REQUIRE(s.get_Q(3) == 0);
}

TEST_CASE("snapshot returns maxQ and maxQ_action as expected", "[snapshot]") {
    snapshot s = snapshot(std::vector<int> {1, 2, 3});

    s.update(3, 1.3);
    REQUIRE(s.get_maxQ() == 1.3f);
    REQUIRE(s.get_maxQ_action() == 3);
}

TEST_CASE("table initialized with 0 size", "[table]") {
    table t = table();

    REQUIRE(t.get_table_size() == 0);
}

TEST_CASE("table predicts unseen state as expected", "[table]") {
    table t = table();

    REQUIRE(t.predict("state0", std::vector<int> {2, 3}) == 2);
}

TEST_CASE("table updates seen state as expected", "[table]") {
    table t = table();

    REQUIRE(t.predict("state0", std::vector<int> {1, 2, 3}) == 1);

    t.update("state0", 1, 2);
    REQUIRE(t.predict("state0", std::vector<int> {1, 2, 3}) == 1);
    REQUIRE(t.get_table_size() == 3);
}

