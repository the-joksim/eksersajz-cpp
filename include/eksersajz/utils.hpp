#pragma once

#include <cassert>
#include <vector>

#include <format>
#include <optional>

#include "spdlog/logger.h"

std::vector<int> make_random_vec(int size, int max_val);

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x);
  TreeNode(int x, TreeNode *l, TreeNode *r);
};

bool equal(const TreeNode *x, const TreeNode *y);

namespace my_utils {

namespace logging {

using Logger = std::shared_ptr<spdlog::logger>;

enum class LogLevel : std::uint8_t { debug, trace, info, warn, err };

std::optional<Logger> mk_basic_logger(const std::string &name,
                                      const std::string &log_file);

std::optional<Logger> mk_stderr_logger(const std::string &name);

void log_stuff(std::optional<Logger> logger, const std::string &msg,
               LogLevel level = LogLevel::info);

} // namespace logging

} // namespace my_utils
