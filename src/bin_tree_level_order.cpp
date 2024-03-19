// Given the root of a binary tree, return the level order traversal of its
// nodes' values. (i.e., from left to right, level by level).

// Example 1:

// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]

// Example 2:

// Input: root = [1]
// Output: [[1]]

// Example 3:

// Input: root = []
// Output: []

// Constraints:

// The number of nodes in the tree is in the range [0, 2000].
//-1000 <= Node.val <= 1000

#include "eksersajz/bin_tree_level_order.hpp"
#include <deque>

void push_to_correct_level(int val, const int level,
                           std::vector<std::vector<int>> &ls) {
  if (level < ls.size()) {
    ls[level].push_back(val);
  } else {
    ls.push_back({val});
  }
}

// FIXME:
//  - too slow and too much memory
std::vector<std::vector<int>> level_order(TreeNode *root) {
  if (root == nullptr) {
    return {};
  }

  int level = 0;

  std::deque<std::tuple<TreeNode *, int>> q{{root, level}};
  std::vector<std::vector<int>> vs{};

  while (!q.empty()) {
    auto [node, lvl] = q.front();
    if (node != nullptr) {
      push_to_correct_level(node->val, lvl, vs);

      if (node->left != nullptr) {
        q.push_back({node->left, lvl + 1});
      }

      if (node->right != nullptr) {
        q.push_back({node->right, lvl + 1});
      }
    }

    q.pop_front();
  }

  return vs;
}
