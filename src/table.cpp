//
// Created by M. Cetin on 3/17/20.
//

#include <limits>
#include "table.h"

void snapshot::update(int action_pos, float new_value) {
    std::lock_guard<std::mutex> guard(store_mutex);

    for (auto const &action : possible_actions) {
        if (action->pos == action_pos) {
            action->val = new_value;
            return;
        }
    }
    possible_actions.push_back(new action{action_pos, new_value});
}

float snapshot::get_Q(int action_pos) {
    for (auto const &action : possible_actions)
        if (action->pos == action_pos)
            return action->val;
    return 0;
}

float snapshot::get_maxQ() {
    float maxQ = std::numeric_limits<float>::lowest();
    for (auto const &action : possible_actions)
        if (action->val > maxQ)
            maxQ = action->val;
    return possible_actions.size() > 0 ? maxQ : 0;
}

int snapshot::get_maxQ_action() {
    float maxQ = std::numeric_limits<float>::lowest();
    float maxQ_action = -1;
    for (auto const &action : possible_actions)
        if (action->val > maxQ) {
            maxQ = action->val;
            maxQ_action = action->pos;
        }
    return maxQ_action;
}

int snapshot::get_action_count() {
    return possible_actions.size();
}

void table::update(const std::string state, int action, float new_value) {
    if (store.find(state) == store.end())
        store[state] = new snapshot(std::vector<int>{});
    store[state]->update(action, new_value);
}

int table::predict(const std::string state, const std::vector<int> empty_slots) {
    if (store.find(state) == store.end())
        store[state] = new snapshot(empty_slots);

    return store[state]->get_maxQ_action();
}

int table::get_table_size() {
    int size = 0;
    for (auto const i : store) {
        size += i.second->get_action_count();
    }
    return size;
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
