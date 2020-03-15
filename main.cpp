#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

#include "game.hpp"
#include "table.hpp"

int predict_pos(table* t, std::string state, const std::vector<int> positions) {
  return t->predict(state, positions);
}

float learning_rate = 0.2;
float discount_factor = 0.3;

int main() {
  srand(time(0));

  table* t_x = new table();
  table* t_o = new table();

  int draw_count = 0;
  int x_won = 0;
  int o_won = 0;

  int x_rand = 10;
  int o_rand = 5;

  marker turn = marker::x;
  for (int i = 0; i < 1000000000; i++) {
    table* t = (turn == marker::x) ? t_x : t_o;
    game g = game();

    bool finished = false;
    while (!finished) {
      std::string state = g.render_board();

      const std::vector<int> available_slots = g.get_available_slots();
      int action = predict_pos(t, state, available_slots);

      if (rand() % (turn == marker::x ? x_rand : o_rand) == 0) {
        action = available_slots[rand() % available_slots.size()];
      }
      result r = g.play(turn, action);

      float reward = 0;
      if (r.finished) {
        if (r.winner == marker::x) {
          reward = (r.winner == turn) ? 1 : -1;
          x_won++;
        } else if (r.winner == marker::o) {
          reward = (r.winner == turn) ? 1 : -1;
          o_won++;
        } else {
          draw_count++;
        }
        if (i % 1000000 == 0) {
          std::cout << g.render_board();
          std::cout << "x won: " << x_won << std::endl;
          std::cout << "table x size: " << t_x->get_table_size() << std::endl;
          std::cout << "o won: " << o_won << std::endl;
          std::cout << "table o size: " << t_o->get_table_size() << std::endl;
          std::cout << "draw: " << draw_count << std::endl;

          draw_count = 0;
          x_won = 0;
          o_won = 0;
        }
      }
      std::string next_state = g.render_board();

      float nextMaxQ = t->get_maxQ_at_state(next_state);
      float oldQ = t->get_Q_at_state_action(state, action);

      float newQValue = oldQ + learning_rate * (reward + discount_factor *
          nextMaxQ - oldQ);

      t->update(state, action, newQValue);

      finished = r.finished;
      if (turn == marker::x)
        turn = marker::o;
      else
        turn = marker::x;
    }
  }

  return 0;
}

