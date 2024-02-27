#pragma once

#include <cassert>
#include <vector>

#include <format>
#include <optional>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

std::vector<int> make_random_vec(int size, int max_val);

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x);
  TreeNode(int x, TreeNode *l, TreeNode *r);
};

namespace my_utils {

namespace logging {

using Logger = std::shared_ptr<spdlog::logger>;

enum class LogLevel : std::uint8_t { debug, trace, info, warn, err };

std::optional<Logger> mk_basic_logger(const std::string &name,
                                      const std::string &log_file);
void log_stuff(LogLevel level, std::optional<Logger> logger,
               const std::string &msg);

} // namespace logging

} // namespace my_utils
