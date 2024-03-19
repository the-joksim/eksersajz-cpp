// Given the root of a complete binary tree, return the number of the nodes in
// the tree.

// According to Wikipedia, every level, except possibly the last, is completely
// filled in a complete binary tree, and all nodes in the last level are as far
// left as possible. It can have between 1 and 2h nodes inclusive at the last
// level h.

// Design an algorithm that runs in less than O(n) time complexity.

// Example 1:

// Input: root = [1,2,3,4,5,6]
// Output: 6

// Example 2:

// Input: root = []
// Output: 0

// Example 3:

// Input: root = [1]
// Output: 1

// Constraints:

// The number of nodes in the tree is in the range [0, 5 * 104].
// 0 <= Node.val <= 5 * 104
// The tree is guaranteed to be complete.

#include "eksersajz/count_complete_tree_nodes.hpp"
#include "eksersajz/utils.hpp"
#include <cmath>

namespace {

using namespace my_utils;

int get_height(TreeNode *root) {
  // a complete tree has at least one node at the last level,
  // so we try to go left at every iteration
  // every time we can go left (next != nullptr), we increase the height by one
  int h = 0;

  for (TreeNode *next = root; next != nullptr; next = next->left) {
    h++;
  }

  return h - 1;
}

void process(const TreeNode *const node, const int level) {
  logging::log_stuff(
      std::format("node with val {} at level {}", node->val, level));
}

struct NodeInfo {
  int level;
  int index;

  void show(const int val) const {
    logging::log_stuff(std::format("node with value {}, index {} at level {}",
                                   val, index, level));
  }
};

// The main trick is:
//  - do a dfs, preferring to visit the right node first (we're looking for the
//  rightmost node at the bottom level)
//  - this search will hit the rightmost node at the bottom level (before any
//  other node at the bottom level)
//  - when this happens, we save the result (index computed from the parent
//  index)
//  - however, as we're doing dfs recursively, we have to have a way of stopping
//  the recursion (we're supposed to do less than O(n) work)
//  - we use a trick where upon entering the recursive function 'go' we check
//  whether we've got the result (i.e. *res > 0)
//
void go(const TreeNode *const root, const NodeInfo root_info,
        const int last_level, int *res) {
  if (*res > 0) {
    return;
  }

  if (root == nullptr) {
    return;
  }

  if (root_info.level == last_level) {
    *res = root_info.index + 1;
  }

  go(root->right,
     {.level = root_info.level + 1, .index = 2 * root_info.index + 2},
     last_level, res);
  go(root->left,
     {.level = root_info.level + 1, .index = 2 * root_info.index + 1},
     last_level, res);

  return;
}

} // namespace

int count_nodes(TreeNode *root) {
  const int h = get_height(root);

  if (h == 0) {
    return 1;
  }

  int res = 0;

  go(root, {.level = 0, .index = 0}, h, &res);

  return res;
}
