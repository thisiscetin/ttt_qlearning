//
// Created by M. Cetin on 3/17/20.
//

#ifndef XOX_QLEARNING_TABLE_H
#define XOX_QLEARNING_TABLE_H
#include <vector>
#include <string>
#include <unordered_map>
#include <mutex> // NOLINT

struct action {
    int pos;
    float val;
};

class snapshot {
public:
    explicit snapshot(const std::vector<int> empty_slots) {
        for (auto const& slot : empty_slots)
            possible_actions.push_back(new action {slot, 0});
    }
    ~snapshot() {
        for (auto const& action : possible_actions)
            delete action;
    }
    void update(int action_pos, float new_value);
    float get_Q(int action_pos);
    float get_maxQ();
    int get_maxQ_action();
    int get_action_count();

private:
    std::vector<action*> possible_actions;
    std::mutex store_mutex;
};

class table {
public:
    void update(const std::string state, int action, float new_value);
    int predict(const std::string state, const std::vector<int> empty_slots);
    int get_table_size();
    float get_maxQ_at_state(const std::string state);
    float get_Q_at_state_action(const std::string state, int action);

private:
    std::unordered_map<std::string, snapshot*> store;
    std::mutex store_mutex;
};


#endif //XOX_QLEARNING_TABLE_H
