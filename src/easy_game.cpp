//
// Created by M. Cetin on 3/17/20.
//

#include "easy_game.h"

long double easy_game::play(direction d) {
    if (d == direction::left) {
        player_pos--;
    } else {
        player_pos++;
    }
    if (player_pos < 1) {
        finished = true;
        return -1.0;
    }

    if (player_pos > 8) {
        finished = true;
        return 1.0;
    }
    return 0;
}

const std::string easy_game::render() {
    std::string r = "";
    for (int i = 0; i < 10; i++) {
        if (i == player_pos)
            r += "|";
        else
            r += "_";
    }
    return r;
}

bool easy_game::get_finished() {
    return finished;
}

direction table::get_max_Q_action(const std::string state) {
    if (store.find(state) == store.end())
        store[state] = new action{0, 0};

    return store[state]->get_max_action();
}

long double table::get_maxQ_at_state(const std::string state) {
    if (store.find(state) == store.end())
        store[state] = new action{0, 0};

    return store[state]->get_max_Q();
}

long double table::get_Q_at_action(const std::string state, const direction d) {
    if (store.find(state) == store.end())
        store[state] = new action{0, 0};

    return store[state]->get_Q_at(d);
}

void table::update(const std::string state, const direction d, long double newValue) {
    if (store.find(state) == store.end())
        store[state] = new action{0, 0};

    if (d == direction::left)
        store[state]->left = newValue;
    else if (d == direction::right)
        store[state]->right = newValue;
}


