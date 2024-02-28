// You are given two integer arrays nums1 and nums2 sorted in non-decreasing
// order and an integer k.

// Define a pair (u, v) which consists of one element from the first array and
// one element from the second array.

// Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.

// Example 1:

// Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
// Output: [[1,2],[1,4],[1,6]]
// Explanation: The first 3 pairs are returned from the sequence:
// [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

// Example 2:

// Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
// Output: [[1,1],[1,1]]
// Explanation: The first 2 pairs are returned from the sequence:
// [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

// Constraints:

// 1 <= nums1.length, nums2.length <= 10^5
//-10^9 <= nums1[i], nums2[i] <= 10^9
// nums1 and nums2 both are sorted in non-decreasing order.
// 1 <= k <= 10^4
// k <= nums1.length * nums2.length

#include "eksersajz/k_smallest_pairs.hpp"
#include "eksersajz/utils.hpp"

#include <climits>
#include <format>
#include <iostream>
#include <optional>

namespace {

void print_pairs(const std::vector<std::vector<int>> &pairs) {
  std::for_each(pairs.begin(), pairs.end(), [](const std::vector<int> p) {
    std::cout << std::format("{{{}, {}}}", p[0], p[1]) << '\n';
  });
}

struct pair_ptr {
  int from = 0;
  int to = 0;
};

} // namespace

// FIXME:
//  - still fucked - the case s_x == s_y is probably not handled correctly
std::vector<std::vector<int>> k_smallest_pairs(std::vector<int> &x,
                                               std::vector<int> &y, int k) {
  int n_x = static_cast<int>(x.size());
  int n_y = static_cast<int>(y.size());

  if (n_x == 0 or n_y == 0) {
    return {};
  }

  std::vector<std::vector<int>> sp{};
  sp.push_back({x[0], y[0]}); // minimum
  int n = 1;

  pair_ptr x_to_y{.from = 0, .to = 1};
  pair_ptr y_to_x{.from = 0, .to = 1};

  while (n < k) {
    int s_x = x[x_to_y.from] + y[x_to_y.to];
    int s_y = y[y_to_x.from] + x[y_to_x.to];

    if (s_x < s_y) {
      sp.push_back({x[x_to_y.from], y[x_to_y.to]});
      n++;
      if (x_to_y.to == (n_y - 1)) {
        if (x_to_y.from == (n_x - 1)) {
          break; // we've reached the final pair: x[x.size - 1], y[y.size - 1]
        } else {
          x_to_y.from++;
          if (y_to_x.from < (n_y - 1)) {
            x_to_y.to = y_to_x.from + 1;
          }
        }
      } else {
        x_to_y.to++;
      }
    }

    if (s_y <= s_x) {
      sp.push_back({x[y_to_x.to], y[y_to_x.from]});
      n++;
      if (y_to_x.to == (n_x - 1)) {
        if (y_to_x.from == (n_y - 1)) {
          break;
        } else {
          y_to_x.from++;
          if (x_to_y.from < (n_x - 1)) {
            y_to_x.to = x_to_y.from + 1;
          }
        }
      } else {
        y_to_x.to++;
      }
    }
  }

  return sp;
}
