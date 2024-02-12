#include <algorithm>
#include <gtest/gtest.h>
#include <map>

#include "insert_delete_getrandom.hpp"
#include "longest_common_prefix.hpp"

TEST(Eksersajz, lcpNoCommonPrefix) {
  std::vector<std::string> words{"ark", "ball", "cluster", "dork"};
  ASSERT_EQ(longest_common_prefix(words), std::string{});
}

TEST(Eksersajz, lcpCommonPrefix) {
  std::vector<std::string> words{"ark", "architecture", "arkansas", "arid"};
  ASSERT_EQ(longest_common_prefix(words), std::string{"ar"});
}

TEST(Eksersajz, getRandomSimplestAPI) {
  RandomizedSet rs{};
  std::vector<int> vals{1, 7, 16, 33, 21, 74, 48};

  ASSERT_FALSE(rs.remove(vals[0]));
  ASSERT_TRUE(rs.insert(vals[0]));

  ASSERT_FALSE(rs.remove(vals[1]));
  ASSERT_TRUE(rs.insert(vals[1]));
  ASSERT_TRUE(rs.remove(vals[1]));
}

namespace {

void update_bins(std::map<int, int> &bins, int v) {
  auto it = bins.find(v);
  if (it != bins.end()) [[likely]] {
    it->second += 1;
  } else {
    bins.emplace(std::pair<int, int>{v, 1});
  }
}

void show_bins(const std::map<int, int> &bins) {
  for (const auto &[k, v] : bins) {
    std::cout << k << " : " << v << '\n';
  }
}

void show_bins_statistics(const std::map<int, int> &bins) {
  using BinItem = decltype(*bins.begin());

  double sum =
      std::accumulate(bins.begin(), bins.end(), 0.0f,
                      [](double acc, BinItem i) { return acc + i.second; });

  double avg = sum / static_cast<double>(bins.size());

  double max_dev_from_avg = 0.0;
  double dev_acc = 0.0;
  for (const auto &[val, hit] : bins) {
    double dev = (static_cast<double>(hit) - avg) / avg;
    if (std::abs(dev) > max_dev_from_avg) {
      max_dev_from_avg = dev;
    }
    dev_acc += std::abs(dev);
  }

  double avg_dev = dev_acc / static_cast<double>(bins.size());

  std::cout << "Avg hits per bin: " << avg << "; "
            << "Max element hit deviation: " << max_dev_from_avg * 100 << '%'
            << "; "
            << "Avg element hit deviation: " << avg_dev * 100 << '%' << '\n';
}

} // namespace

TEST(Eksersajz, getRandomAllValuesUniformlyDrawn) {
  const size_t S = 100'000;
  std::map<int, int> bins;
  const size_t N = 1000;
  RandomizedSet rs = make_random_rs(N, N);

  for (size_t i = 0; i < S; i++) {
    int v = rs.get_random();
    update_bins(bins, v);
  }

  // show_bins(bins);
  show_bins_statistics(bins);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
