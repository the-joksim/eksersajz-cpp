// Given a sorted array of distinct integers and a target value, return the
// index if the target is found. If not, return the index where it would be if
// it were inserted in order.

// You must write an algorithm with O(log n) runtime complexity.

// Example 1:

// Input: nums = [1,3,5,6], target = 5
// Output: 2

// Example 2:

// Input: nums = [1,3,5,6], target = 2
// Output: 1

// Example 3:

// Input: nums = [1,3,5,6], target = 7
// Output: 4

// Constraints:

// 1 <= nums.length <= 10^4
//-10^4 <= nums[i] <= 10^4
// nums contains distinct values sorted in ascending order.
//-10^4 <= target <= 10^4

#include "eksersajz/insert_search_position.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>

namespace {
int brute_force(std::vector<int> &nums, int target) {
  int n = nums.size();
  int r = -1;

  if (target < nums[0])
    return 0;
  if (target > nums[n - 1])
    return n;

  for (int i = 0; i < n - 1; i += 2) {
    if (target == nums[i]) {
      r = i;
    }
    if (nums[i] < target and target <= nums[i + 1]) {
      r = i + 1;
    }
  }

  return r;
}

void process_current(int l, int r) {
  std::cout << '{' << l << ", " << r << '}' << '\n';
}

int better(std::vector<int> &nums, int t) {
  int n = nums.size();
  int i = -1;

  if (t < nums[0])
    return 0;
  if (t > nums[n - 1])
    return n;

  int l = 0;
  int r = n - 1;

  while (r - l > 1) {
    int m = (r + l) / 2;

    if (t >= nums[m]) {
      l = m;
    }
    if (t <= nums[m]) {
      r = m;
    }
    // process_current(l, r);
  }

  if (nums[l] == t) {
    i = l;
  } else {
    i = r;
  }

  return i;
}

} // namespace

int search_insert(std::vector<int> &nums, int target) {
  return better(nums, target);
}
