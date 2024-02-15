// * bool insert(int val) Inserts an item val into the set if not present.
// Returns true if the item was not present, false otherwise.
// * bool remove(int val)
// Removes an item val from the set if present. Returns true if the item was
// present, false otherwise.
// * int getRandom()
// Returns a random element from the
// current set of elements (it's guaranteed that at least one element exists
// when this method is called). Each element must have the same probability of
// being returned.
// You must implement the functions of the class such
// that each function works in average
// O(1) time complexity.

#pragma once

#include <random>
#include <unordered_map>

class RandomizedSet {
public:
  RandomizedSet() = default;
  ~RandomizedSet() = default;

  bool insert(int val);
  bool remove(int val);
  int get_random();

private:
  std::unordered_map<int, int> storage{};
  std::vector<int> values{};
  mutable std::mt19937 mt{};
};

// Fastest solution uses an unordered_map<int, int> that keeps a mapping between
// values and its index in a vector (elements are actually stored in a vector)
// unordered_map<int, int> map;
// std::vector<int> elems;
// So, getting an element goes something like this:
//  elems[map.find(v)->second] (provided the element exists in the vector)

RandomizedSet make_random_rs(size_t size, int max_val);
