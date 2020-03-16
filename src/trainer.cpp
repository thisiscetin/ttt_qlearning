#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "trainer.hpp"

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
  return t->predict(state, positions);
}

void agent::learn(const std::string state, const std::string next_state,
      int action, float reward) {
  float oldQ = t->get_Q_at_state_action(state, action);
  float nextMaxQ = t->get_maxQ_at_state(next_state);
  float newQValue = oldQ + s->learning_rate * (reward +
      s->discount_factor * nextMaxQ - oldQ);

  t->update(state, action, newQValue);
}

int dummy_agent::play(const std::vector<int> positions) {
  return positions[rand() % positions.size()];
}

void trainer::play() {
  game g = game();

  bool finished = false;
  marker a_marker = a->get_marker();
  marker d_marker = (a_marker == marker::x) ? marker::o : marker::x;

  marker turn = a_marker;
  result r;
  while (!finished) {
    const std::string state = g.render_board();

    if (turn == a_marker) {
      int action = a->play(state, g.get_available_slots());
      r = g.play(a_marker, action);

      if (r.finished && r.winner == a_marker) {
        a->learn(state, g.render_board(), action, 1.0);
      }
    } else {
      r = g.play(d_marker, b->play(g.get_available_slots()));
    }

    finished = r.finished;
    turn = (turn == a_marker) ? d_marker : a_marker;
  }

  if (r.winner == a_marker)
    stats.agent_won++;
  if (r.winner == d_marker)
    stats.dummy_agent_won++;
  stats.game_count++;
}

const trainer_stats trainer::get_stats() {
  return stats;
}
