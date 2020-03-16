#ifndef SRC_TABLE_HPP_
#define SRC_TABLE_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <mutex> // NOLINT

class snapshot {
 public:
  explicit snapshot(const std::vector<int> empty_slots) {
    for (auto const& slot : empty_slots)
      possible_actions[slot] = 0;
  }
  void update(int action, float new_value);
  float get_Q(int action);
  float get_maxQ();
  int get_maxQ_action();

 private:
  std::unordered_map<int, float> possible_actions;
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
};

#endif // SRC_TABLE_HPP_
