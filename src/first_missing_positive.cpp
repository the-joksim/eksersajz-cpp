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

int my_failed_attempt(std::vector<int> &nums) {
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
    // gap candidate g. We backtrack from the position of the last found gap
    // element + 1.
    if (s == g) {
      s++;

      // i = g_i; // we don't set it to g_i + 1 because the for loop will do
      // that for us (i++ before entering into another iteration)

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

int official(std::vector<int> &nums) {
  // The solution is based on two tricks/observations:
  // 1.) For an array of n numbers, the first missing positive integer is <=
  //     n+1.
  //     The equality will hold only if the array has the first n positive
  //     integers as elements, e.g. nums = [1, 2, 3, 4, 5, 6] (they could be in
  //     any order).
  // 2.) As we're constrained by O(1) in space, we have to use the original
  //     integer array.
  //     We use it as follows:
  //      We first do a sweep to check if 1 is found in the array. If not, then
  //      1 is the smallest missing positive integer.
  //      Otherwise, we preprocess the array so that for nums[i] < 0 or nums[i]
  //      > n (?), we replace nums[i] with 1, so when we encounter them
  //      (remember that at this point we know 1 was found in the array), we
  //      don't care about them.
  //      For a given nums[i], , we set nums[nums[i]] to -1 indicating that
  //      nums[i] is present.
  //      Finally, we scan the array once more, searching for the first position
  //      i where we find a positive number. i is then the smallest missing
  //      positive integer.

  int n = nums.size();

  // Base case.
  int contains = 0;
  for (int i = 0; i < n; i++)
    if (nums[i] == 1) {
      contains++;
      break;
    }

  if (contains == 0)
    return 1;

  // Replace negative numbers, zeros,
  // and numbers larger than n by 1s.
  // After this convertion nums will contain
  // only positive numbers.
  for (int i = 0; i < n; i++)
    if ((nums[i] <= 0) or (nums[i] > n))
      nums[i] = 1;

  // Use index as a hash key and number sign as a presence detector.
  // For example, if nums[1] is negative that means that number `1`
  // is present in the array.
  // If nums[2] is positive - number 2 is missing.
  for (int i = 0; i < n; i++) {
    int a = std::abs(nums[i]);
    // If you meet number a in the array - change the sign of a-th element.
    // Be careful with duplicates : do it only once.
    if (a == n)
      nums[0] = -std::abs(nums[0]);
    else
      nums[a] = -std::abs(nums[a]);
  }

  // Now the index of the first positive number
  // is equal to first missing positive.
  for (int i = 1; i < n; i++) {
    if (nums[i] > 0)
      return i;
  }

  if (nums[0] > 0)
    return n;

  return n + 1;
}

int first_missing_positive(std::vector<int> &nums) { return official(nums); }
