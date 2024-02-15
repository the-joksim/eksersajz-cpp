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
  std::vector<int> answer(nums.size());
  auto product_all =
      std::accumulate(nums.begin(), nums.end(), 1,
                      [](const int x, const int y) { return x * y; });
  for (const auto n : nums) {
    answer.push_back(product_all / n);
  }
  return answer;
}

std::vector<int> optimal_two_pass(std::vector<int> &nums) {
  int n = nums.size();
  std::vector<int> answer(n);

  answer[0] = 1;
  for (int i = 1; i < n; i++) {
    answer[i] = answer[i - 1] * nums[i - 1];
  }
  int right = 1;
  for (int i = n - 1; i >= 0; i--) {
    answer[i] *= right;
    right *= nums[i];
  }

  return answer;
}

} // namespace

std::vector<int> product_except_self(std::vector<int> &nums) {
  return optimal_two_pass(nums);
}
