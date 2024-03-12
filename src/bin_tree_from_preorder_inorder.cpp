// Given two integer arrays preorder and inorder where preorder is the preorder
// traversal of a binary tree and inorder is the inorder traversal of the same
// tree, construct and return the binary tree.

// Example 1:

// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]

// Example 2:

// Input: preorder = [-1], inorder = [-1]
// Output: [-1]

// Constraints:

// 1 <= preorder.length <= 3000
// inorder.length == preorder.length
//-3000 <= preorder[i], inorder[i] <= 3000
// preorder and inorder consist of unique values.
// Each value of inorder also appears in preorder.
// preorder is guaranteed to be the preorder traversal of the tree.
// inorder is guaranteed to be the inorder traversal of the tree.

#include "eksersajz/bin_tree_from_preorder_inorder.hpp"
#include "eksersajz/utils.hpp"

#include <algorithm>
#include <ranges>

namespace {
bool is_unique(const std::vector<int> &xs) {
  auto xs_cpy = xs;
  bool uniq = true;

  std::sort(xs_cpy.begin(), xs_cpy.end());
  const int N = xs_cpy.size();

  for (int i = 0; i < (N - 1); i++) {
    // search for duplicates (that's why we sorted the array)
    if (xs_cpy[i] == xs_cpy[i + 1]) {
      uniq = false;
      break;
    }
  }

  return uniq;
}

std::tuple<std::vector<int>, std::vector<int>>
split_inorder_on_root(const std::vector<int> &xs, int root) {
  std::vector<int> l{};
  std::vector<int> r{};

  for (auto it = xs.begin(); it != xs.end(); it++) {
    if (*it == root) {
      l.insert(l.end(), xs.begin(), it);
      r.insert(r.end(), it + 1,
               xs.end()); // check if this works when it = end - 1
      break;
    }
  }

  return {l, r};
}

std::tuple<std::vector<int>, std::vector<int>>
get_left_and_right_subtree_from_preorder(const std::vector<int> &preorder,
                                         size_t l_size, size_t r_size) {
  assert(preorder.size() == (l_size + r_size + 1));

  auto l_start = preorder.begin() + 1;
  auto l_end = l_start + l_size;
  std::vector<int> l{l_start, l_end};

  auto r_start = l_end;
  auto r_end = preorder.end();
  std::vector<int> r{r_start, r_end};

  return {l, r};
}

TreeNode *do_build_tree(const std::vector<int> &preorder,
                        const std::vector<int> &inorder) {
  if (preorder.empty()) {
    return nullptr;
  }

  if (preorder.size() == 1) {
    return new TreeNode(preorder[0]);
  }

  int root = preorder[0];

  // split the inorder on the root:
  //  - elements up to root is the left subtree
  //  - elements after the root is the right subtree
  auto [in_l, in_r] = split_inorder_on_root(inorder, root);

  // get the corresponding left and right subtree from preorder:
  //  - preorder[1 : in_l.size()] is the left subtree
  //  - preorder[in_l.size() + 1 : (in_l.size() + 1) + in_r.size()] is the right
  //    subtree

  auto [pre_l, pre_r] = get_left_and_right_subtree_from_preorder(
      preorder, in_l.size(), in_r.size());

  return new TreeNode(root, do_build_tree(pre_l, in_l),
                      do_build_tree(pre_r, in_r));
}

} // namespace

TreeNode *build_tree(std::vector<int> &preorder, std::vector<int> &inorder) {
  assert(is_unique(preorder));
  assert(is_unique(inorder));
  assert(preorder.size() == inorder.size());

  auto *t = do_build_tree(preorder, inorder);
  return t;
}
