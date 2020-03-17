//
// Created by M. Cetin on 3/17/20.
//

#ifndef XOX_QLEARNING_EASY_GAME_H
#define XOX_QLEARNING_EASY_GAME_H

#include <algorithm>
#include <string>
#include <unordered_map>

enum direction {
    right = 'r',
    left = 'l'
};

class easy_game {
public:
    explicit easy_game(int pos_in) : player_pos(pos_in) {
        finished = false;
    }
    const std::string render();
    long double play(direction d);
    bool get_finished();

private:
    int player_pos;
    bool finished;
};

struct action {
    long double left;
    long double right;

    long double get_max_Q() {
        if (left > right)
            return left;
        return right;
    }
    direction get_max_action() {
        if (left > right)
            return direction::left;
        return direction::right;
    }
    long double get_Q_at(const direction d) {
        if (d == direction::left)
            return left;
        else if (d == direction::right)
            return right;
        return 0;
    }
};

class table {
public:
    table() {}
    ~table() {
        for (auto s : store)
            delete s.second;
    }
    long double get_Q_at_action(const std::string state, const direction d);
    direction get_max_Q_action(const std::string state);
    long double get_maxQ_at_state(const std::string state);
    void update(const std::string state, const direction d, long double newValue);
private:
    std::unordered_map<std::string, action*> store;
};

class agent {
public:
    agent (long double learning_rate, long double discount_factor) : lr(learning_rate),
        df(discount_factor) {
        t = new table();
    }
    ~agent() {
        delete t;
    }
    direction play(const std::string state) {
        return t->get_max_Q_action(state);
    }
    void feedback(const std::string state, const std::string next_state,
            const direction d, long double reward) {
        long double oldQ = t->get_Q_at_action(state, d);
        long double nextMaxQ = t->get_maxQ_at_state(next_state);
        long double newQValue = oldQ + lr * (reward + df * nextMaxQ - oldQ);

        t->update(state, d, newQValue);
    }

    table* t;
private:
    long double lr;
    long double df;
};

#endif //XOX_QLEARNING_EASY_GAME_H
