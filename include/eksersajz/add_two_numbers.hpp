// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order, and each of their nodes
// contains a single digit. Add the two numbers and return the sum as a linked
// list.

// You may assume the two numbers do not contain any leading zero, except the
// number 0 itself.

#include <functional>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *add_two_numbers(ListNode *x, ListNode *y);

void traverse(ListNode *l, std::function<void(int)> f);
ListNode *make_lnode_from(const std::vector<int> &digits);

void add_and_show(ListNode *x, ListNode *y);
