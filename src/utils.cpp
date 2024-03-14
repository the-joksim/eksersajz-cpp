#include "eksersajz/utils.hpp"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <cassert>
#include <format>
#include <random>

std::vector<int> make_random_vec(int size, int max_val) {
  assert(size >= 0);
  std::vector<int> out{size};
  std::mt19937 mt{};

  for (int i = 0; i < size; i++) {
    out.push_back(mt() % max_val);
  }

  return out;
}

TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int x, TreeNode *l, TreeNode *r)
    : val(x), left(l), right(r) {}

// FIXME:
//  - make an iterative version
bool TreeNode::equal(const TreeNode *x, const TreeNode *y) {
  if (x == nullptr && y == nullptr) {
    return true;
  }

  return x->val == y->val && equal(x->left, y->left) &&
         equal(x->right, y->right);
}

void TreeNode::traverse_with(TreeNode *root, TreeNode::Traversal traversal,
                             std::function<void(TreeNode *)> f) {
  if (root == nullptr) {
    return;
  }

  switch (traversal) {
  case TreeNode::Traversal::Preorder: {
    f(root);
    traverse_with(root->left, traversal, f);
    traverse_with(root->right, traversal, f);
  } break;
  case TreeNode::Traversal::Inorder: {
    traverse_with(root->left, traversal, f);
    f(root);
    traverse_with(root->right, traversal, f);
  } break;
  case TreeNode::Traversal::Postorder: {
    traverse_with(root->left, traversal, f);
    traverse_with(root->right, traversal, f);
    f(root);
  } break;
  }

  return;
}

namespace my_utils {

namespace logging {

std::optional<Logger> mk_basic_logger(const std::string &name,
                                      const std::string &log_file) {
  try {
    auto logger = spdlog::basic_logger_mt(name, log_file);
    return logger;
  } catch (std::exception &e) {
    return std::nullopt;
  }
}

std::optional<Logger> mk_stderr_logger(const std::string &name) {
  Logger logger;
  try {
    logger = spdlog::stderr_color_mt(name);
    return logger;
  } catch (std::exception &e) {
    return std::nullopt;
  }
}

void log_stuff(const std::string &msg, std::optional<Logger> logger,
               LogLevel level) {
  if (!logger.has_value()) {
    // default - log to stdout
    logger = spdlog::get("default");
    if (logger == nullptr) {
      logger = spdlog::stdout_color_mt("default");
    }
  }

  switch (level) {
  case LogLevel::debug:
    (*logger)->debug(msg);
    break;

  case LogLevel::trace:
    (*logger)->trace(msg);
    break;

  case LogLevel::info:
    (*logger)->info(msg);
    break;

  case LogLevel::warn:
    (*logger)->warn(msg);
    break;

  case LogLevel::err:
    (*logger)->error(msg);
    break;

  default:
    (*logger)->error(
        std::format("unknown logging level: {}", static_cast<uint8_t>(level)));
    break;
  }
}

} // namespace logging

} // namespace my_utils
