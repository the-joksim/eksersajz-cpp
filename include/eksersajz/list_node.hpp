#pragma once

#include <functional>
#include <vector>

// list<int>
struct ListNode {
  int val;
  ListNode *next;

  ListNode();
  ListNode(int x);
  ListNode(int x, ListNode *next);
};

bool has_more_elems(ListNode *x);
void traverse(ListNode *l, std::function<void(int)> f);
ListNode *make_lnode_from(const std::vector<int> &digits);
