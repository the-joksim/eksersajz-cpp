#pragma once

#include <optional>
#include <vector>

#include "spdlog/logger.h"

std::vector<int> make_random_vec(int size, int max_val);

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x);
  TreeNode(int x, TreeNode *l, TreeNode *r);

  static bool equal(const TreeNode *x, const TreeNode *y);

  enum class Traversal { Preorder, Inorder, Postorder };

  static void traverse_with(TreeNode *root, Traversal traversal,
                            std::function<void(TreeNode *)> f);
};

namespace my_utils {

namespace logging {

using Logger = std::shared_ptr<spdlog::logger>;

enum class LogLevel : std::uint8_t { debug, trace, info, warn, err };

std::optional<Logger> mk_basic_logger(const std::string &name,
                                      const std::string &log_file);

std::optional<Logger> mk_stderr_logger(const std::string &name);

void log_stuff(const std::string &msg,
               std::optional<Logger> logger = std::nullopt,
               LogLevel level = LogLevel::info);

void log_function(const char *fun_name);
} // namespace logging

} // namespace my_utils
