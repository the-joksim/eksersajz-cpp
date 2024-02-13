#include "eksersajz/add_two_numbers.hpp"
#include <cassert>
#include <iostream>
#include <utility>

bool has_more_digits(ListNode *x) { return x->next != nullptr; }

ListNode *add_two_numbers(ListNode *x, ListNode *y) {
  assert(x != nullptr && y != nullptr);
  ListNode *prev = nullptr;
  ListNode *head = nullptr;

  int carry = 0;
  bool x_done = false;
  bool y_done = false;

  while (!x_done or !y_done or carry != 0) {
    int dx = x_done ? 0 : x->val;
    int dy = y_done ? 0 : y->val;

    int sum = dx + dy + carry;

    int r = sum % 10;
    carry = sum / 10;

    auto *cur = new ListNode(r);
    if (prev == nullptr) {
      prev = cur;
      head = prev;
    } else [[likely]] {
      prev->next = cur;
      prev = cur;
    }

    if (has_more_digits(x)) {
      x = x->next;
    } else {
      x_done = true;
    }

    if (has_more_digits(y)) {
      y = y->next;
    } else {
      y_done = true;
    }
  }

  return head;
}

void traverse(ListNode *l, std::function<void(int)> f) {
  assert(l != nullptr);

  do {
    f(l->val);
    l = l->next;
  } while (l != nullptr);
}

// digits - number in reverse order
// fix
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

void add_and_show(ListNode *x, ListNode *y) {
  auto print = [](const int x) { std::cout << x; };

  std::cout << " ";
  traverse(x, print);
  std::cout << '\n';

  std::cout << '+' << '\n';

  std::cout << " ";
  traverse(y, print);
  std::cout << '\n';

  std::cout << '=' << '\n';

  auto *sum = add_two_numbers(x, y);

  std::cout << " ";
  traverse(sum, print);
  std::cout << '\n';
}
