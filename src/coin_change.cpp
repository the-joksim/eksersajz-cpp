// You are given an integer array coins representing coins of different
// denominations and an integer amount representing a total amount of money.

// Return the fewest number of coins that you need to make up that amount. If
// that amount of money cannot be made up by any combination of the coins,
// return -1.

// You may assume that you have an infinite number of each kind of coin.

// Example 1:

// Input: coins = [1,2,5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1

// Example 2:

// Input: coins = [2], amount = 3
// Output: -1

// Example 3:

// Input: coins = [1], amount = 0
// Output: 0

// Constraints:

// 1 <= coins.length <= 12
// 1 <= coins[i] <= 231 - 1
// 0 <= amount <= 104

#include "eksersajz/coin_change.hpp"
#include <climits>

#include <map>

namespace {

int get_next_coin(const std::vector<int> &coins, int remainder) {
  int next = 0;
  int min_remainder = INT_MAX;
  for (const auto c : coins) {
    if (c > remainder)
      continue;

    int d = remainder - c;

    if (d < min_remainder) {
      min_remainder = d;
      next = c;
    }
  }

  return next;
}

int go(const std::vector<int> &coins, int remainder, std::vector<int> count) {
  if (remainder < 0) {
    return -1;
  }
  if (remainder == 0) {
    return 0;
  }

  if (count[remainder] != 0) {
    return count[remainder];
  }

  int min = INT_MAX;

  for (const auto c : coins) {
    int res = go(coins, remainder - c, count);
    if (res >= 0 and res < min) {
      min = 1 + res;
    }
  }

  count[remainder] = (min == INT_MAX) ? -1 : min;

  return count[remainder];
}

int official(std::vector<int> &coins, int amount) {
  std::vector<int> count(amount + 1); // indexes start from 1 and end up at N
  return go(coins, amount, count);
}

} // namespace

int coin_change(std::vector<int> &coins, int amount) {
  return official(coins, amount);
}
