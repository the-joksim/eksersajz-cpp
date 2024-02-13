#include "eksersajz/tester_class.hpp"
#include <iostream>
#include <string>

Tester::Tester() { std::cout << "Default ctor called!" << '\n'; }
Tester::~Tester() { std::cout << "Dtor called!" << '\n'; }

Tester::Tester(const Tester &other) {
  std::cout << "Copy ctor called!" << '\n';
}

Tester &Tester::operator=(const Tester &other) {
  std::cout << "Copy assignment called!" << '\n';
  return *this;
}

Tester::Tester(Tester &&other) { std::cout << "Move ctor called!" << '\n'; }
Tester &Tester::operator=(Tester &&other) {
  std::cout << "Move assignment called!" << '\n';
  return *this;
}
