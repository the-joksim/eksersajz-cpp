#include <iostream>
#include <string>
#include <vector>

#include "fill_bounds.hpp"

namespace {

void fill_boundaries(std::vector<std::vector<int>> &in) {
  // fill first row with ones
  for (size_t n = 0; n < in[0].size(); n++) {
    in[0][n] = 1;
  }

  // fill intermediate rows - one at first and last position
  for (size_t m = 1; m < (in.size() - 1); m++) {
    in[m][0] = 1;
    in[m][in[m].size() - 1] = 1;
  }

  // fill last row with ones
  for (size_t n = 0; n < in[in.size() - 1].size(); n++) {
    in[in.size() - 1][n] = 1;
  }
}

void print_row(const std::vector<int> &row) {
  const std::string elem_spacer = "  ";
  for (const auto &e : row) {
    std::cout << e << elem_spacer;
  }
  std::cout << '\n';
}

} // namespace

void print_table(const std::vector<std::vector<int>> &in) {
  for (const auto &row : in) {
    print_row(row);
  }
}

void do_fill_boundaries(std::vector<std::vector<int>> &in) {
  fill_boundaries(in);
  print_table(in);
}
