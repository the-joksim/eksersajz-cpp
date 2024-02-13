#include <iostream>
#include <regex>

#include "eksersajz/weird_date.hpp"

void StandardDate::print() const {
  std::cout << day << "-" << month << "-" << year << '\n';
}

namespace {

StandardDate from_weird_to_standard(const std::string &weird) {
  const std::regex weird_regex(R"(\d x \d{3}u \d{3} \d)");

  if (!std::regex_match(weird, weird_regex)) {
    return {};
  }

  StandardDate standard{};
  int read = 0;
  for (auto c : weird) {
    if (!isdigit(c))
      continue;
    if (read < 4) {
      standard.year.push_back(c);
      read++;
    } else if (read < 6) {
      standard.month.push_back(c);
      read++;
    } else if (read < 8) {
      standard.day.push_back(c);
      read++;
    }
  }
  return standard;
}

} // namespace

void do_weird(char **argv) {
  if (argv[1]) {
    from_weird_to_standard(std::string{argv[1]}).print();
  } else {
    std::cerr << "No input given!" << '\n';
  }
}
