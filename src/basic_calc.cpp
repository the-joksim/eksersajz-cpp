// Given a string s representing a valid expression, implement a basic
// calculator to evaluate it, and return the result of the evaluation.

// Note: You are not allowed to use any built-in function which evaluates
// strings as mathematical expressions, such as eval().

// Example 1:

// Input: s = "1 + 1"
// Output: 2

// Example 2:

// Input: s = " 2-1 + 2 "
// Output: 3

// Example 3:

// Input: s = "(1+(4+5+2)-3)+(6+8)"
// Output: 23

// Constraints:

// 1 <= s.length <= 3 * 105
// s consists of digits, '+', '-', '(', ')', and ' '.
// s represents a valid expression.
//'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
//'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
// There will be no two consecutive operators in the input.
// Every number and running calculation will fit in a signed 32-bit integer.

#include "eksersajz/basic_calc.hpp"
#include <algorithm>
#include <iostream>
#include <string_view>

namespace {

class Scanner {
public:
  Scanner(std::string_view s) : in(s) {}
  ~Scanner() = default;

  std::string_view lookahead() { return next_token(); }

private:
  const std::string EMPTY = " \n";

  std::string_view in{};

  bool is_done() const { return in.empty(); }

  bool is_empty_char(const char c) const {
    return std::any_of(EMPTY.begin(), EMPTY.end(),
                       [c_ = c](const char ec) { return c_ == ec; });
  }

  bool is_paren(const char c) const { return c == '(' or c == ')'; }

  void ignore_empty() {
    if (is_done()) {
      return;
    }

    while (!is_done() and is_empty_char(in[0])) {
      in.remove_prefix(1);
    }
  }

  std::string_view next_token() {
    if (is_done()) {
      return {};
    }

    ignore_empty();

    if (is_done()) {
      return {};
    }

    // find next empty char
    // return the view ending on the character before the found empty char

    const char *start = std::addressof(in[0]);

    // parens treated as single-character tokens
    if (is_paren(in[0])) {
      in.remove_prefix(1);
      return {start, 1};
    }

    // handle non-paren tokens
    size_t ts = 0;
    while (!is_done() and !is_empty_char(in[0]) and !is_paren(in[0])) {
      ts++;
      in.remove_prefix(1);
    }

    std::string_view res{start, ts};

    return res;
  }
};

class ParseResult {
public:
  struct Parsed {};

  ParseResult() = default;
  ParseResult(std::string_view s) : remaining(s) {}
  ~ParseResult() = default;

private:
  Parsed parsed{};
  std::string_view remaining;
};

class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  ParseResult parse(std::string_view s) {
    res = ParseResult{s};
    // do actual parsing
    return res;
  }

private:
  ParseResult res{};
  bool done{false};

  void match_expr() {
    match_paren();
    match_binop();
    match_uniop();
    match_num();
  }

  void match_num() {}

  void match_binop() { match_expr(); }

  void match_uniop() { match_expr(); }

  void match_paren() {}

  void match_paren_expr() {
    match_paren();
    match_expr();
    match_paren();
  }
};

class Calculator {
public:
  Calculator() noexcept = default;
  ~Calculator() = default;

  int eval(ParseResult parsed) { return 0; }

  int calculate(std::string s) { return eval(parser.parse(s)); }

private:
  Parser parser{};
};

} // namespace

int calculate(std::string s) {
  Scanner scanner{s};

  std::string_view token{};
  while (!(token = scanner.lookahead()).empty()) {
    std::cout << token << '\n';
  }

  Calculator calc{};

  return calc.calculate(s);
}
