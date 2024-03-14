// Given the root of a binary tree, flatten the tree into a "linked list":

// The "linked list" should use the same TreeNode class where the right child
// pointer points to the next node in the list and the left child pointer is
// always null. The "linked list" should be in the same order as a pre-order
// traversal of the binary tree.

// Example 1:

// Input: root = [1,2,5,3,4,null,6]
// Output: [1,null,2,null,3,null,4,null,5,null,6]

// Example 2:

// Input: root = []
// Output: []

// Example 3:

// Input: root = [0]
// Output: [0]

// Constraints:

// The number of nodes in the tree is in the range [0, 2000].
//-100 <= Node.val <= 100

// Follow up: Can you flatten the tree in-place (with O(1) extra space)?

#include "eksersajz/flatten_bin_tree.hpp"
#include "eksersajz/utils.hpp"

namespace {

TreeNode *find_last_in_flattened_tree(TreeNode **root_p) {
  if (*root_p == nullptr) {
    return nullptr;
  }

  while ((*root_p)->right != nullptr) {
    root_p = &(*root_p)->right;
  }
  return *root_p;
}

void do_flatten(TreeNode *node) {
  // do a preorder and flatten subtrees
  if (node == nullptr) {
    return;
  }

  // save the right subtree, because we'll be swapping the left and right
  // subtree
  auto *right_tmp = node->right;

  // because the "linked list" leans to the right
  node->right = node->left;
  node->left = nullptr;

  // flatten the left subtree (now the right subtree)
  do_flatten(node->right);

  // flatten the right subtree
  do_flatten(right_tmp);

  // seek forward to the last element in the flattened left subtree,
  // so we can append the flattened right subtree (currently in right_tmp) to it
  auto *last_in_left_subtree = find_last_in_flattened_tree(&node->right);

  if (last_in_left_subtree == nullptr) {
    // left subtree is null -> link the right subtree to the root
    node->right = right_tmp;
  } else {
    last_in_left_subtree->right = right_tmp;
  }

  return;
}

void show_tree(TreeNode *root) {
  TreeNode::traverse_with(
      root, TreeNode::Traversal::Preorder, [](const TreeNode *n) {
        my_utils::logging::log_stuff(std::format("val: {}", n->val));
      });

  return;
}

} // namespace

void flatten(TreeNode *root) {
  show_tree(root);

  do_flatten(root);

  show_tree(root);

  return;
}
