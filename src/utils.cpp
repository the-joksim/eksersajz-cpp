#include "eksersajz/utils.hpp"

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

void log_stuff(LogLevel level, std::optional<Logger> logger,
               const std::string &msg) {
  if (!logger.has_value()) {
    // default - log to stdout
    logger = spdlog::stdout_color_mt("default");
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
