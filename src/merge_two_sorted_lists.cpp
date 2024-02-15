#include "eksersajz/merge_two_sorted_lists.hpp"

#include <cassert>

bool is_sorted(ListNode *x) { return true; }

ListNode *merge(ListNode *x, ListNode *y) {
  // we insert the elems from y to x
  assert(x != nullptr or y != nullptr);

  if (y == nullptr) {
    return x;
  }
  if (x == nullptr) {
    return y;
  }

  ListNode *head = x;
  ListNode *x_prev = nullptr;

  ListNode *x_cur = x;
  ListNode *y_cur = y;

  bool done = false;
  while (!done) {
    if (x_cur->val >= y_cur->val) {
      // put y before x
      auto *y_next = y_cur->next; // link y to x
      y_cur->next = x_cur;

      // check if we're inserting before head and update head accordingly
      if (x_cur == head) {
        head = y_cur;
        x_cur = head;
      }

      // if there's an element before the just-inserted one, link it
      if (x_prev != nullptr) [[likely]] {
        x_prev->next = y_cur;
        x_prev = y_cur;
      }

      if (y_next != nullptr) {
        y_cur = y_next;
      } else {
        done = true;
      }
    } else if (x_cur->val < y_cur->val) {
      if (has_more_elems(x_cur)) {
        // just advance x_cur
        x_prev = x_cur;
        x_cur = x_cur->next;
      } else {
        // append y_cur to x_cur because there are no more elems in x larger
        // than y, so that the rest of the y list can be safely appended to the
        // x list
        x_cur->next = y_cur;
        done = true;
      }
    }
  }

  return head;
}
