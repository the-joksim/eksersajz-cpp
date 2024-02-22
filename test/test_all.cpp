#include <algorithm>
#include <gtest/gtest.h>
#include <map>

#include "eksersajz/add_two_numbers.hpp"
#include "eksersajz/climbing_stairs.hpp"
#include "eksersajz/container_with_most_water.hpp"
#include "eksersajz/first_missing_positive.hpp"
#include "eksersajz/house_robber.hpp"
#include "eksersajz/insert_delete_getrandom.hpp"
#include "eksersajz/insert_search_position.hpp"
#include "eksersajz/longest_common_prefix.hpp"
#include "eksersajz/merge_two_sorted_lists.hpp"
#include "eksersajz/product_of_array_except_self.hpp"
#include "eksersajz/reverse_integer.hpp"
#include "eksersajz/utils.hpp"

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
    update_bins(bins, rs.get_random());
  }

  // show_bins(bins);
  show_bins_statistics(bins);
}

TEST(Eksersajz, productExceptSelf) {
  {
    std::vector<int> nums{5, 7, 2, 4};
    std::vector<int> expected{56, 40, 140, 70};
    auto answer = product_except_self(nums);
    ASSERT_EQ(answer, expected);
  }

  {
    std::vector<int> nums{1, 2, 3, 4, 5, 6};
    std::vector<int> expected{720, 360, 240, 180, 144, 120};
    auto answer = product_except_self(nums);
    ASSERT_EQ(answer, expected);
  }
}

TEST(Eksersajz, addTwoNumbers) {
  {
    auto *x = make_lnode_from({9, 9, 9});
    auto *y = make_lnode_from({1});

    add_and_show(x, y);
  }

  {
    auto *u = make_lnode_from({5, 6, 6});
    auto *v = make_lnode_from({5, 3});

    add_and_show(u, v);
  }
}

TEST(Eksersajz, mergeTwoSortedLists) {
  {
    auto *x = make_lnode_from({3, 4, 4, 4});
    auto *y = make_lnode_from({1, 2, 2, 3, 5, 6, 7});
    auto *merged = merge(x, y);
    traverse(merged, [](const int x) { std::cout << x << " : "; });
    std::cout << '\n';
  }

  {
    auto *x = make_lnode_from({1, 4, 5, 8});
    auto *y = make_lnode_from({2, 3, 6, 7, 9});
    auto *merged = merge(x, y);
    traverse(merged, [](const int x) { std::cout << x << " : "; });
    std::cout << '\n';
  }

  {
    auto *x = make_random_list(10, 1000, [](int u, int v) { return u < v; });
    std::cout << "x = ";
    traverse(x, [](const int x) { std::cout << x << " : "; });
    std::cout << '\n';

    auto *y = make_random_list(15, 1000, [](int u, int v) { return u < v; });
    std::cout << "y = ";
    traverse(y, [](const int x) { std::cout << x << " : "; });
    std::cout << '\n';

    auto *merged = merge(x, y);
    std::cout << "merged = ";
    traverse(merged, [](const int x) { std::cout << x << " : "; });
    std::cout << '\n';
  }
}

TEST(Eksersajz, containerWithMostWater) {
  {
    std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    int expected = 49;
    ASSERT_EQ(max_area(height), expected);
  }

  {
    std::vector<int> height{1, 4, 4, 1};
    int expected = 4;
    ASSERT_EQ(max_area(height), expected);
  }
  {
    std::vector<int> height{1, 8, 100, 2, 100, 4, 8, 3, 7};
    int expected = 200;
    ASSERT_EQ(max_area(height), expected);
  }
}

TEST(Eksersajz, insertSearchPosition) {
  {
    std::cout << "Run: 1" << '\n';
    std::vector<int> nums{1, 3, 5, 6};
    int t = 5;
    int expected = 2;
    ASSERT_EQ(search_insert(nums, t), expected);
  }

  {
    std::cout << "Run: 2" << '\n';
    std::vector<int> nums{1, 3, 5, 6};
    int t = 0;
    int expected = 0;
    ASSERT_EQ(search_insert(nums, t), expected);
  }

  {
    std::cout << "Run: 3" << '\n';
    std::vector<int> nums{1, 3, 5, 6};
    int t = 7;
    int expected = 4;
    ASSERT_EQ(search_insert(nums, t), expected);
  }

  {
    std::cout << "Run: 4" << '\n';
    std::vector<int> nums{0, 25, 37, 39, 63, 74, 77, 81, 95, 105};
    int t = 57;
    int expected = 4;
    ASSERT_EQ(search_insert(nums, t), expected);
  }
}

TEST(Eksersajz, firstMissingPositive) {
  {
    std::vector<int> nums{7, 8, 9, 10, 11, 12};
    int expected = 1;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }

  {
    std::vector<int> nums{1, 2, 0};
    int expected = 3;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }

  {
    std::vector<int> nums{3, 4, -1, 1};
    int expected = 2;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }

  {
    std::vector<int> nums{3, 5, -1, 1, 2};
    int expected = 4;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }

  {
    std::vector<int> nums{3, 5, -1, 1, 2, -1, 7, 6, -1, 4, 9};
    int expected = 8;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }

  {
    std::vector<int> nums{1, 2, 6, 3, 5, 4};
    int expected = 7;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }

  {
    std::vector<int> nums{20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
                          10, 9,  8,  7,  6,  5,  4,  3,  2,  1};
    int expected = 21;
    ASSERT_EQ(first_missing_positive(nums), expected);
  }
}

TEST(Eksersajz, reverseInteger) {
  {
    int n = 123;
    int expected = 321;
    ASSERT_EQ(reverse_integer(n), expected);
  }

  {
    int n = 120;
    int expected = 21;
    ASSERT_EQ(reverse_integer(n), expected);
  }

  {
    int n = -4567;
    int expected = -7654;
    ASSERT_EQ(reverse_integer(n), expected);
  }

  {
    int n = INT_MAX;
    int expected = 0;
    ASSERT_EQ(reverse_integer(n), expected);
  }

  {
    int n = INT_MIN;
    int expected = 0;
    ASSERT_EQ(reverse_integer(n), expected);
  }
}

TEST(Eksersajz, climbingStairs) {
  {
    int n = 2;
    int expected = 2;
    ASSERT_EQ(climb_stairs(n), expected);
  }

  {
    int n = 3;
    int expected = 3;
    ASSERT_EQ(climb_stairs(n), expected);
  }

  {
    int n = 4;
    int expected = 5;
    ASSERT_EQ(climb_stairs(n), expected);
  }

  {
    int n = 5;
    int expected = 8;
    ASSERT_EQ(climb_stairs(n), expected);
  }
}

TEST(Eksersajz, houseRobber) {
  {
    std::vector<int> nums{1, 2, 3, 1};
    int expected = 4;
    ASSERT_EQ(rob(nums), expected);
  }

  {
    std::vector<int> nums{2, 7, 3, 1};
    int expected = 8;
    ASSERT_EQ(rob(nums), expected);
  }

  {
    std::vector<int> nums{2, 7, 9, 3, 1};
    int expected = 12;
    ASSERT_EQ(rob(nums), expected);
  }

  {
    std::vector<int> nums{1, 2, 3, 2, 1, 5};
    int expected = 9;
    ASSERT_EQ(rob(nums), expected);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
