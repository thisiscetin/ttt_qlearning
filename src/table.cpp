#include <limits>

#include "table.hpp"

void snapshot::update(int action, float new_value) {
  std::lock_guard<std::mutex> guard(store_mutex);
  if (possible_actions.find(action) == possible_actions.end())
    throw std::logic_error("possible action is not found in snapshot");
  possible_actions[action] = new_value;
}

float snapshot::get_Q(int action) {
  return possible_actions[action];
}

float snapshot::get_maxQ() {
  if (possible_actions.size() == 0)
    throw std::logic_error("possible actions size is zero");

  float maxQ = std::numeric_limits<float>::lowest();
  for (auto const& i : possible_actions) {
    if (i.second > maxQ) {
      maxQ = i.second;
    }
  }
  return maxQ;
}

int snapshot::get_maxQ_action() {
  if (possible_actions.size() == 0)
    throw std::logic_error("possible actions size is zero");

  float maxQ = std::numeric_limits<float>::lowest();
  float maxQ_action = -1;
  for (auto const& i : possible_actions) {
    if (i.second > maxQ) {
      maxQ = i.second;
      maxQ_action = i.first;
    }
  }
  return maxQ_action;
}

void table::update(const std::string state, int action, float new_value) {
  // skip random movement updates for simplicity
  if (store.find(state) == store.end())
    throw std::logic_error("state not found");
  store[state]->update(action, new_value);
}

int table::predict(const std::string state, const std::vector<int> empty_slots) {
  if (store.find(state) == store.end())
    store[state] = new snapshot(empty_slots);

  return store[state]->get_maxQ_action();
}

int table::get_table_size() {
  return store.size();
}

float table::get_maxQ_at_state(const std::string state) {
  if (store.find(state) == store.end())
    return 0;

  return store[state]->get_maxQ();
}

float table::get_Q_at_state_action(const std::string state, int action) {
    if (store.find(state) == store.end())
        return 0;
  return store[state]->get_Q(action);
}
