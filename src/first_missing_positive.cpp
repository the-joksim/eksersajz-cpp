// Given an unsorted integer array nums, return the smallest missing positive
// integer.

// You must implement an algorithm that runs in O(n) time and uses O(1)
// auxiliary space.

// Example 1:

// Input: nums = [1,2,0]
// Output: 3
// Explanation: The numbers in the range [1,2] are all in the array.

// Example 2:

// Input: nums = [3,4,-1,1]
// Output: 2
// Explanation: 1 is in the array but 2 is missing.

// Example 3:

// Input: nums = [7,8,9,11,12]
// Output: 1
// Explanation: The smallest positive integer 1 is missing.

// Constraints:

// 1 <= nums.length <= 10^5
//-2^31 <= nums[i] <= 2^31 - 1

#include "eksersajz/first_missing_positive.hpp"
#include <climits>
#include <iostream>

int first_missing_positive(std::vector<int> &nums) {
  int s = 1; // smallest missing positive candidate
  int g = INT_MAX;
  int g_i = -1; // index of the number closest to our candidate u (used for
                // backtracking)

  // profiling
  int iterations = 0;

  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] < 0)
      continue;

    if (nums[i] == s) {
      s++;
    }

    // gap detection
    // save the closest gap element and its index
    if (nums[i] > s and nums[i] < g) {
      g = nums[i];
      g_i = i;
    }

    // A gap is closed if the smallest missing candidate becomes equal to the
    // gap candidate g if we find a number closer to s than the closest known so
    // far. We backtrack from the position of the last found gap element + 1
    if (s == g) {
      s++;

      // i = g_i; // we don't set it to g_i because the for loop will do that
      // for us (i++ before entering into another iteration)

      // This makes the algorithm O(n^2) - we jump back to the beginning.
      // Can we choose a better index to backtrack to?
      i = -1;

      // reset gap vars
      g = INT_MAX;
      g_i = -1;
    }

    // profiling
    iterations++;
  }

  std::cout << "input size: " << nums.size() << "; "
            << "iterations: " << iterations << '\n';
  return s;
}
