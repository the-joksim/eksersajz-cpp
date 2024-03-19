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

namespace {

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

int go_count(TreeNode *root, int root_i, int level, const int height) {
  if (root == nullptr) {
    return 0;
  }

  if (level == (height - 1)) {
    if (root->right != nullptr) {
      return (root_i * 2 + 2); // move to next viable sibling
    }

    if (root->left != nullptr) {
      return (root_i * 2 + 1);
    }
  } else {
    return std::max(go_count(root->left, root_i * 2 + 1, level + 1, height),
                    go_count(root->right, root_i * 2 + 2, level + 1, height));
  }

  return 0;
}

} // namespace

int count_nodes(TreeNode *root) {
  const int h = get_height(root);

  if (h == 0) {
    return 1;
  }

  return go_count(root, 0, 0, h);
}
