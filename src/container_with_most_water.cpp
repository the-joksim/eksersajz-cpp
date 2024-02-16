#include "eksersajz/container_with_most_water.hpp"
#include <iostream>

// Constraints:
// n == height.length
// 2 <= n <= 10^5
// 0 <= height[i] <= 10^4

namespace {
int brute_force(std::vector<int> &height) {
  // try all combinations of i and j, except i == j and don't test i and j if at
  // some previous iteration i was j and j was i
  int size = height.size();
  int max = 0;
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      int area = std::min(height[i], height[j]) * std::abs(i - j);
      if (area > max)
        max = area;
    }
  }

  return max;
}

void process_current(int area, int l, int r) {
  std::cout << '{' << l << ", " << r << '}' << " : ";
  std::cout << area << '\n';
}

int better(std::vector<int> &height) {
  int n = height.size();

  int l = 0;
  int r = n - 1;

  int max = 0;

  while (l < r) {
    int area = std::min(height[l], height[r]) * (r - l);
    area = std::max(max, area);

    process_current(area, l, r);

    if (height[l] >= height[r]) {
      r--;
    }
    if (height[r] >= height[l]) {
      l++;
    }
  }

  return max;
}

} // namespace

int max_area(std::vector<int> &height) { return better(height); }
