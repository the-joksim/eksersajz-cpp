#include "eksersajz/utils.hpp"

#include <random>

std::vector<int> make_random_vec(int size, int max_val) {
  assert(size >= 0);
  std::vector<int> out{size};
  std::mt19937 mt{};

  for (int i = 0; i < size; i++) {
    out.push_back(mt() % max_val);
  }

  return out;
}
