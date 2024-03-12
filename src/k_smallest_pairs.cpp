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
#include <queue>

namespace {

void print_pairs(const std::vector<std::vector<int>> &pairs) {
  std::for_each(pairs.begin(), pairs.end(), [](const std::vector<int> p) {
    std::cout << std::format("{{{}, {}}}", p[0], p[1]) << '\n';
  });
}

struct pair {
  int x = 0;   // index in the first array
  int y = 0;   // index in the second array
  int sum = 0; // sum of elements at the above indices
};

struct pair_gt {
  bool operator()(const pair &x, const pair &y) { return x.sum > y.sum; }
};

using min_heap = std::priority_queue<pair, std::vector<pair>, pair_gt>;

} // namespace

// FIXME:
//  - still fucked
std::vector<std::vector<int>> k_smallest_pairs(std::vector<int> &x,
                                               std::vector<int> &y, int k) {
  int n_x = static_cast<int>(x.size());
  int n_y = static_cast<int>(y.size());

  if (n_x == 0 or n_y == 0) {
    return {};
  }

  min_heap h{};

  std::vector<std::vector<int>> sp{};
  sp.push_back({x[0], y[0]}); // minimum

  pair x_y{.x = 0, .y = 1};
  pair y_x{.x = 1, .y = 0};

  while (h.size() < (k + 1)) {
    // h.size < k + 1 because we need k + 1 smallest pairs to be sure that we
    // get k smalles pairs (leftover pair from a previous comparison that
    // "lost")
    int s_x = x[x_y.x] + y[x_y.y];
    int s_y = x[y_x.x] + y[y_x.y];

    h.push(pair{.x = x_y.x, .y = x_y.y, .sum = s_x});
    h.push(pair{.x = y_x.x, .y = y_x.y, .sum = s_y});

    // move on to next pair y -> x (e.g. (1, 1) -> (2, 1))
    // y is fixed, x moves until it hits the last element
    // note that we avoid duplicates (see the 'else' branch in the inner 'if')
    if (y_x.x == (n_x - 1)) {
      if (y_x.y == (n_y - 1)) {
        break; // we've reached the final pair: x[x.size - 1], y[y.size - 1]
      } else {
        y_x.y++;
        if (x_y.x < (n_x - 1)) {
          y_x.x = x_y.x + 1;
        }
      }
    } else {
      y_x.x++;
    }

    // move on to next pair x -> y (e.g. (1, 1) -> (1, 2))
    // x is fixed, y moves until it hits the last element
    if (x_y.y == (n_y - 1)) {
      if (x_y.x == (n_x - 1)) {
        break; // we've reached the final pair: x[x.size - 1], y[y.size - 1]
      } else {
        x_y.x++;
        if (y_x.y < (n_y - 1)) {
          x_y.y = y_x.y + 1;
        }
      }
    } else {
      x_y.y++;
    }
  }

  while (k > 1) {
    auto p = h.top();
    sp.push_back({x[p.x], y[p.y]});

    h.pop();
    k--;
  }

  return sp;
}
