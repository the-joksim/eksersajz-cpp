#include "eksersajz/list_node.hpp"

#include <cassert>

ListNode::ListNode() : val(0), next(nullptr) {}
ListNode::ListNode(int x) : val(x), next(nullptr) {}
ListNode::ListNode(int x, ListNode *next) : val(x), next(next) {}

bool has_more_elems(ListNode *x) { return x->next != nullptr; }

void traverse(ListNode *l, std::function<void(int)> f) {
  assert(l != nullptr);

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
