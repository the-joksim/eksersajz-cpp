#include "eksersajz/list_node.hpp"

#include <cassert>
#include <random>

ListNode::ListNode() : val(0), next(nullptr) {}
ListNode::ListNode(int x) : val(x), next(nullptr) {}
ListNode::ListNode(int x, ListNode *next) : val(x), next(next) {}

bool has_more_elems(ListNode *x) { return x->next != nullptr; }

void traverse(ListNode *l, std::function<void(int)> f) {
  if (l != nullptr) {
    return;
  }

  do {
    f(l->val);
    l = l->next;
  } while (l != nullptr);
}

ListNode *make_lnode_from(const std::vector<int> &digits) {
  ListNode *prev = nullptr;
  ListNode *head = nullptr;

  for (const auto d : digits) {
    auto *cur = new ListNode(d);
    if (prev == nullptr) {
      prev = cur;
      head = prev;
    } else [[likely]] {
      prev->next = cur;
      prev = cur;
    }
  }

  return head;
}

ListNode *make_random_list(size_t n, int max_val,
                           std::function<bool(int, int)> relation) {
  static std::mt19937 mt{};
  ListNode *prev = nullptr;
  ListNode *head = nullptr;

  int u = 0;
  int max_step = 50;
  int v = mt() % max_step;

  for (size_t i = 0; i < n; i++) {
    while (not relation(u, u + v)) {
      v = mt() % max_step;
    }
    auto *cur = new ListNode(u + v);
    if (prev == nullptr) {
      prev = cur;
      head = prev;
    } else [[likely]] {
      prev->next = cur;
      prev = cur;
    }
    u = u + v;
    // if we don't update, we get stuck at the same step at every iteration
    v = mt() % max_step;
  }

  return head;
}
