// You are climbing a staircase. It takes n steps to reach the top.

// Each time you can either climb 1 or 2 steps. In how many distinct ways can
// you climb to the top?

#include "eksersajz/climbing_stairs.hpp"
#include <algorithm>
#include <cstdint>
#include <vector>

struct Steps {
  int ones = 0;
  int twos = 0;
};

int binomial_coefficient(const int n, const int k) {
  if (k == 0)
    return 1;

  // We need a bigger boat (std::int64_t) because the formula inside the for
  // loop might blow up momentarily because of the multiplication part.
  // Unfortunately, we can't reorder the formula so that we have
  // a / (i + 1) at the beginning, since it will give the wrong result (why?).
  std::int64_t a = n - k + 1;

  for (int i = 1; i < k; ++i) {
    a = a * (n - k + 1 + i) / (i + 1);
    // a = a / (i + 1) * (n - k + 1 + i);
  }

  return static_cast<int>(a);
}

int distinct_ways(const Steps &steps) {
  int k = steps.twos;
  int n = steps.ones + steps.twos;

  return binomial_coefficient(n, k);
}

int recursive_solution(int i, int n) {
  // O(2^n) complexity - we fork at each step - try one step and try two steps

  // overshoot
  if (i > n)
    return 0;
  // feasible solution
  if (i == n)
    return 1;

  return recursive_solution(i + 1, n) + recursive_solution(i + 2, n);
}

int official(int n) { return recursive_solution(0, n); }

int climb_stairs(int n) {
  int total_ways = 0;
  // start by going greedy - try to fit as many two-steps
  Steps starting = {.ones = n % 2, .twos = n / 2};

  // now, realize that we can interchange every two-step with two one-steps
  while (starting.twos >= 0) {
    total_ways += distinct_ways(starting);

    starting.twos -= 1;
    starting.ones += 2;
  }

  return total_ways;
}
