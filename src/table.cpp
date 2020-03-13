#include "table.hpp"

void snapshot::update(int action, float new_value) {
  possible_actions[action] = new_value;

  for (auto const& i : possible_actions) {
    if (i.second > maxQ) {
      maxQ = i.second;
      maxQ_action = i.first;
    }
  }
}

float snapshot::get_maxQ() {
  return maxQ;
}

int snapshot::get_maxQ_action() {
  return maxQ_action;
}

void table::update(const std::string state, int action, float new_value) {
  store[state]->update(action, new_value);
}

int table::predict(const std::string state, const std::vector<int> empty_slots) {
  if (store.find(state) == store.end())
    store[state] = new snapshot(empty_slots);

  return store[state]->get_maxQ_action();
}
