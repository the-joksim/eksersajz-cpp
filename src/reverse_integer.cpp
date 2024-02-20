#include "eksersajz/reverse_integer.hpp"
#include <climits>
#include <cmath>
#include <vector>

int reverse_integer(int x) {
  if (x == INT_MIN)
    return 0;

  int sign = (x >= 0) ? 1 : -1;
  x = std::abs(x);

  std::vector<int> digits{};
  do {
    digits.push_back(x % 10);
    x = x / 10;
  } while (x);

  int r = 0;
  const int max_pow = 9;
  int pow = digits.size() - 1;

  if (pow > max_pow) {
    return 0;
  }

  if (pow == max_pow and digits[0] > 4) {
    return 0;
  }

  for (const auto d : digits) {
    int z = d * std::pow(10, pow);

    if (sign == 1) {
      if ((INT_MAX - r) < z) {
        return 0;
      }
    } else {
      if ((INT_MIN + r) > -z) {
        return 0;
      }
    }

    r += z;
    pow--;
  }

  return sign * r;
}
