#include "insert_delete_getrandom.hpp"

#include <climits>

bool RandomizedSet::insert(int val) {
  auto [_, success] = storage.insert({val, val});
  if (success) {
    values.push_back(val);
  }
  return success;
}

bool RandomizedSet::remove(int val) {
  auto it = storage.find(val);
  if (it != storage.end()) {
    auto next_it = storage.erase(it);
    return next_it != storage.end();
  } else {
    return false;
  }
}

int RandomizedSet::get_random() {
  decltype(storage.find(0)) it{};

  do {
    auto candidate_i = mt() % values.size();
    it = storage.find(values[candidate_i]);
  } while (it == storage.end());

  return it->second;
}

RandomizedSet make_random_rs(size_t size, int max_val = 1 << 12) {
  static std::mt19937 mt{};
  RandomizedSet rs{};

  size_t count = 0;
  while (count < size) {
    count = (rs.insert(mt() % max_val)) ? count + 1 : count;
  }

  return rs;
}
