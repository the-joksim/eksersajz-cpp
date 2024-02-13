#include "eksersajz/buy_sell_stock.hpp"
#include <iostream>
#include <random>
#include <vector>

namespace {
void max_profit_brute_force(const std::vector<int> &prices, int &max_profit) {
  for (size_t i = 0; i < prices.size() - 1; i++) {
    for (size_t j = i + 1; j < prices.size(); j++) {
      int profit = prices[j] - prices[i];
      max_profit = (profit > max_profit) ? profit : max_profit;
    }
  }
}

// Fixme!
//  * works for smaller arrays, but fails for some big ones (100k elements)
//  * weird indices bug (and who knows what else)
//  * check the official solution and prove that it works, and why
void max_profit_smarter(const std::vector<int> &prices, size_t buy_i,
                        int &max_profit) {
  static uint call_counter = 0;
  call_counter++;
  std::cout << "Call counter: " << call_counter << '\n';

  if (buy_i > (prices.size() - 2))
    return;

  size_t sell_i = 0;

  // find first max_profit > 0
  for (size_t i = buy_i; i < prices.size() - 1; i++) {
    if (max_profit)
      break;
    for (size_t j = i + 1; j < prices.size(); j++) {
      int profit = prices[j] - prices[i];
      if (profit >= max_profit) {
        max_profit = profit;
        buy_i = i;
        sell_i = j;
      }
    }
  }

  // try finding better buying day
  for (size_t i = buy_i; i < sell_i; i++) {
    int profit = prices[sell_i] - prices[i];
    if (profit >= max_profit) {
      buy_i = i;
      max_profit = profit;
    }
  }

  // repeat on the rest of the array (from sell_i + 1 until the end of prices)
  int max_profit_on_rest = 0;
  max_profit_smarter(prices, sell_i + 1, max_profit_on_rest);
  max_profit =
      (max_profit_on_rest > max_profit) ? max_profit_on_rest : max_profit;
}

} // namespace

int max_profit(const std::vector<int> &prices) {
  int max_profit = 0;

  // max_profit_brute_force(prices, max_profit);
  max_profit_smarter(prices, 0, max_profit);

  return max_profit;
}

std::vector<int> make_prices(size_t N) {
  static std::mt19937 mt{};
  std::vector<int> prices;
  prices.reserve(N);
  for (size_t n = 0; n < N; n++) {
    prices.push_back(mt() % (1 << 12));
  }
  return prices;
}
