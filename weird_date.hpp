#include <string>

struct StandardDate {
  std::string day;
  std::string month;
  std::string year;

  void print() const;
};

void do_weird(char **argv);
