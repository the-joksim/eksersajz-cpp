#include "eksersajz/insert_delete_getrandom.hpp"

#include <climits>

bool RandomizedSet::insert(int val) {
  if (storage.find(val) != storage.end())
    return false;

  values.push_back(val);
  auto [_, success] = storage.insert({val, values.size() - 1});

  return success;
}

bool RandomizedSet::remove(int val) {
  auto it = storage.find(val);
  if (it == storage.end())
    return false;

  values[it->second] = values.back(); // replace the element to be erased with
  values.pop_back();
  storage[values[it->second]] = it->second; // update the swapped element index

  storage.erase(it);
  return true;
}

int RandomizedSet::get_random() { return values[mt() % values.size()]; }

RandomizedSet make_random_rs(size_t size, int max_val = 1 << 12) {
  static std::mt19937 mt{};
  RandomizedSet rs{};

  size_t count = 0;
  while (count < size) {
    count = (rs.insert(mt() % max_val)) ? count + 1 : count;
  }

  return rs;
}
