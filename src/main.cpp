#include <cctype>
#include <iostream>
#include <regex>
#include <string>

#include "eksersajz/buy_sell_stock.hpp"
#include "eksersajz/fill_bounds.hpp"
#include "eksersajz/longest_common_prefix.hpp"
#include "eksersajz/tester_class.hpp"
#include "eksersajz/weird_date.hpp"

int main(int argc, char **argv) {
  // std::vector<std::vector<int>> in = std::vector(6, std::vector<int>(7));
  // do_fill_boundaries(in);
  //  do_weird(argv);
  // std::vector<int> prices{7, 6, 5, 2, 9, 11, 18};
  // const size_t I = 1;
  // for (size_t i = 0; i < I; i++) {
  // std::vector<int> prices = make_prices(100'000);
  // std::cout << "Max profit: " << max_profit(prices) << '\n';
  //}
  auto words = std::vector<std::string>{"flower", "flow", "flobber", "float",
                                        "floopitynoop"};
  std::cout << longest_common_prefix(words) << '\n';

  Tester t{};       // default ctor
  Tester u = t;     // copy ctor called!
  Tester v{};       // default ctor
  v = std::move(u); // move assignment called!
}
