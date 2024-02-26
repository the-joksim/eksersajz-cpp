// Given an integer array nums and an integer k, return the kth largest element
// in the array.

// Note that it is the kth largest element in the sorted order, not the kth
// distinct element.

// Can you solve it without sorting?

#include "eksersajz/kth_largest_element_array.hpp"
#include <algorithm>

int find_kth_largest(std::vector<int> &nums, int k) {
  if (k == 0 or k > nums.size())
    return -1;

  // heapify
  std::make_heap(nums.begin(), nums.end());

  int t = 1;

  while (t < k) {
    std::pop_heap(nums.begin(), nums.end());
    nums.pop_back();

    // Rebalancing is easy:
    //  * after the max is removed (nums[0]), we are left with an array whose
    //  first two elements are the children of the removed max
    //  * we could end up in the situation where the new first element is
    //  smaller than the second one, and if this is the case, we swap them,
    // and are left with a proper max heap (check this - sounds whack)
    // CHECKED - make_heap builds a different heap than I'd expect - it sorts
    // the input array in reverse HENCE, no swapping is necessary

    // if (nums.size() > 1) {
    // if (nums[0] < nums[1]) {
    // std::swap(nums[0], nums[1]);
    //}
    //}

    t++;
  }

  return nums.front();
}
