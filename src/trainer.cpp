//
// Created by M. Cetin on 3/17/20.
//

#include <stdlib.h>

#include "trainer.h"

const marker agent::get_marker() {
    return m;
}

int agent::play(const std::string state, const std::vector<int> positions) {
    if (positions.size() == 0)
        throw std::logic_error("possible actions size is zero");

    if ((rand() % s->discovery_epsilon) == 0 && s->discovery_epsilon != -1) {
        int elem = rand() % positions.size();
        return positions[elem];
    }

    // moves to double Q
    if ((rand() % 2 == 0))
        return t0->predict(state, positions);
    else
        return t1->predict(state, positions);
}

void agent::learn(const std::string state, const std::string next_state,
                  int action, float reward) {
    table *t = rand() % 2 == 0 ? t0 : t1;

    float oldQ = t->get_Q_at_state_action(state, action);
    float nextMaxQ = t->get_maxQ_at_state(next_state);
    float newQValue = oldQ + s->learning_rate * (reward +
                                                 s->discount_factor * nextMaxQ - oldQ);
    t->update(state, action, newQValue);
}

int agent::get_table_size() {
    return t0->get_table_size() + t1->get_table_size();
}

float agent::get_max_Q_at_state(const std::string state) {
    table *t = rand() % 2 == 0 ? t0 : t1;

    return t->get_maxQ_at_state(state);
}

int dummy_agent::play(const std::vector<int> positions) {
    return positions[rand() % positions.size()];
}

struct history_entry {
    std::string state;
    std::string next_state;
    int action;
};

void trainer::play() {
    game *g = new game();

    bool finished = false;
    marker a_marker = a->get_marker();
    marker b_marker = (a_marker == marker::x) ? marker::o : marker::x;

    marker turn = rand() % 2 == 0 ? a_marker : b_marker;

    std::vector<history_entry> past_moves_a = std::vector<history_entry>{};
    std::vector<history_entry> past_moves_b = std::vector<history_entry>{};
    result turn_result;
    while (!finished) {
        const std::string state = g->render_board();
        float reward = 0;

        agent *x = turn == a_marker ? a : b;
        int action = x->play(state, g->get_available_slots());
        turn_result = g->play(turn, action);

        const std::string next_state = g->render_board();
        if (turn == a_marker)
            past_moves_a.push_back(history_entry{state, next_state, action});
        else
            past_moves_b.push_back(history_entry{state, next_state, action});

        if (turn_result.finished) {
            reward = turn_result.winner == marker::n ? 2 : 10;

            if (turn_result.winner != marker::n) {
                std::vector<history_entry> past_moves = turn == a_marker ? past_moves_a : past_moves_b;

                while (past_moves.size() > 0) {
                    history_entry le = past_moves.back();
                    x->learn(le.state, le.next_state, le.action, reward);
                    past_moves.pop_back();

                    reward = reward / 2;
                }
            } else {
                // on draw
                x->learn(state, next_state, action, reward);
            }
        }
        finished = turn_result.finished;
        turn = (turn == a_marker) ? b_marker : a_marker;
    }
    if (turn_result.winner == a_marker)
        stats.agent0_won++;
    if (turn_result.winner == b_marker)
        stats.agent1_won++;
    stats.game_count++;

    delete g;
}

const trainer_stats trainer::get_stats() {
    return stats;
}

int trainer::get_table_size() {
    return a->get_table_size();
}
