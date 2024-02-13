// Given an integer array nums, return an array answer such that answer[i] is
// equal to the product of all the elements of nums except nums[i].

// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit
// integer.

// You must write an algorithm that runs in O(n) time and without using the
// division operation.

#include "eksersajz/product_of_array_except_self.hpp"
#include <numeric>

namespace {

std::vector<int> brute_force(std::vector<int> &nums) {
  std::vector<int> answer;
  answer.reserve(nums.size());
  auto product_all =
      std::accumulate(nums.begin(), nums.end(), 1,
                      [](const int x, const int y) { return x * y; });
  for (const auto n : nums) {
    answer.push_back(product_all / n);
  }
  return answer;
}

} // namespace

std::vector<int> product_except_self(std::vector<int> &nums) {
  return brute_force(nums);
}
