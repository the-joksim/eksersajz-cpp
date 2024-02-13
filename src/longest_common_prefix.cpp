#include "eksersajz/longest_common_prefix.hpp"

#include <algorithm>
#include <iterator>

namespace {

std::string get_shortest(std::vector<std::string> &words) {
  // dumb search for minimum (O(n))
  std::string *shortest = nullptr;
  size_t minsize = 200;
  for (auto &w : words) {
    if (w.size() < minsize) {
      shortest = &w;
      minsize = w.size();
    }
  }

  return (shortest == nullptr) ? std::string{} : *shortest;
}

} // namespace

std::string longest_common_prefix(std::vector<std::string> &words) {
  std::sort(words.begin(), words.end(),
            [](const std::string &a, const std::string &b) {
              return a.size() < b.size();
            });
  auto shortest = words[0];

  // an efficiency hack - I don't have to sort, just find the shortest string
  // (O(n) instead of O(nlogn))
  // auto shortest = get_shortest(words);

  std::string lcp{};

  for (size_t i = 0; i < shortest.size(); i++) {
    if (std::all_of(words.begin(), words.end(),
                    [char_i = i, c = shortest[i]](const std::string &w) {
                      return w[char_i] == c;
                    })) {
      lcp.push_back(shortest[i]);
    } else {
      break;
    }
  }

  return lcp;
}
