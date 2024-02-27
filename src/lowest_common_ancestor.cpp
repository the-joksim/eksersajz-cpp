
#include "eksersajz/lowest_common_ancestor.hpp"
#include "eksersajz/utils.hpp"
#include <algorithm>

namespace {

bool find(TreeNode *root, TreeNode *t, std::vector<TreeNode *> &path) {
  if (root == t) {
    path.push_back(root); // because we allow a node to be its own ancestor
    return true;
  }

  if (root == nullptr) {
    return false;
  }

  bool l_found = find(root->left, t, path);
  bool r_found = find(root->right, t, path);

  bool found = l_found or r_found;

  if (found) {
    path.push_back(root);
  }

  return found;
}

} // namespace

TreeNode *lowest_common_ancestor(TreeNode *root, TreeNode *p, TreeNode *q) {
  std::vector<TreeNode *> path_p{};
  std::vector<TreeNode *> path_q{};

  assert(find(root, p, path_p));
  assert(find(root, q, path_q));

  TreeNode *lcp = nullptr;

  std::reverse(path_p.begin(), path_p.end());
  std::reverse(path_q.begin(), path_q.end());

  auto p_it = path_p.begin();
  auto q_it = path_q.begin();

  while (p_it != path_p.end() and q_it != path_q.end() and *p_it == *q_it) {
    lcp = *p_it;

    p_it++;
    q_it++;
  }

  return lcp;
}
