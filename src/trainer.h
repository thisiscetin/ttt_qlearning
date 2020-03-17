//
// Created by M. Cetin on 3/17/20.
//

#ifndef XOX_QLEARNING_TRAINER_H
#define XOX_QLEARNING_TRAINER_H

#include <string>
#include <vector>
#include "game.h"
#include "table.h"

struct strategy {
    float learning_rate;
    float discount_factor;
    int discovery_epsilon; // any positive number accepted, -1 disables randomness
};

class agent {
public:
    agent(marker m_in, strategy *s_in) : m(m_in), s(s_in) {
        if (s->discovery_epsilon != -1) {
            srand(time(0));
        }
        t = new table();
    }

    ~agent() {
        delete t;
        delete s;
    }

    const marker get_marker();

    int play(const std::string state, const std::vector<int> positions);

    void learn(const std::string state, const std::string next_state,
               int action, float reward);

    int get_table_size();

    float get_max_Q_at_state(const std::string state);

private:
    table *t;
    strategy *s;
    marker m;
};

class dummy_agent {
public:
    dummy_agent() {
        srand(time(0));
    }

    int play(const std::vector<int> positions);
};

struct trainer_stats {
    int game_count;
    int agent_won;
    int dummy_agent_won;

    int draw_count() {
        return game_count - agent_won - dummy_agent_won;
    }
};

class trainer {
public:
    explicit trainer(agent *a_in, dummy_agent *b_in) : a(a_in), b(b_in),
                                                       stats(trainer_stats{0, 0, 0}) {}

    ~trainer() {
        delete a;
        delete b;
    }

    void play();

    const trainer_stats get_stats();

    int get_table_size();

private:
    agent *a;
    dummy_agent *b;
    trainer_stats stats;
};


#endif //XOX_QLEARNING_TRAINER_H
