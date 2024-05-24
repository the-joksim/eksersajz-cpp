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
#include "eksersajz/utils.hpp"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <source_location>
#include <string_view>
#include <vector>

namespace {

class Scanner {
public:
  Scanner() = default;
  ~Scanner() = default;

  Scanner(const Scanner &other) = delete;
  Scanner &operator=(const Scanner &other) = delete;

  Scanner(Scanner &&other) = delete;
  Scanner &operator=(Scanner &&other) = delete;

  [[nodiscard]] constexpr bool is_done() const { return in.empty(); }

  constexpr void init(std::string_view s) { in = s; }

  [[nodiscard]] constexpr std::string_view next_token() {
    if (is_done()) {
      return {};
    }

    skip_empty();

    if (is_done()) {
      return {};
    }

    // find next empty char
    // return the view ending on the character before the found empty char

    const char *start = std::addressof(in[0]);

    // handle parens, and operators ('+', '-')
    if (is_special_char(in[0])) {
      in.remove_prefix(1);
      return {start, 1};
    }

    // handle non-special, non-empty tokens
    size_t ts = 0;
    while (!is_done() and !is_empty_char(in[0]) and !is_special_char(in[0])) {
      ts++;
      in.remove_prefix(1);
    }

    std::string_view res{start, ts};

    return res;
  }

private:
  static constexpr std::string_view EMPTY = " \n";

  std::string_view in{};

  [[nodiscard]] constexpr bool is_empty_char(const char c) const {
    return std::any_of(EMPTY.begin(), EMPTY.end(),
                       [c_ = c](const char ec) { return c_ == ec; });
  }

  [[nodiscard]] constexpr bool is_paren(const char c) const {
    return c == '(' or c == ')';
  }

  [[nodiscard]] constexpr bool is_operator(const char c) const {
    return c == '+' or c == '-';
  }

  [[nodiscard]] constexpr bool is_special_char(const char c) const {
    return is_paren(c) or is_operator(c);
  }

  constexpr void skip_empty() {
    if (is_done()) {
      return;
    }

    while (!is_done() and is_empty_char(in[0])) {
      in.remove_prefix(1);
    }
  }
};

enum class TokenType : std::uint8_t { integer, plus, minus, lparen, rparen };

struct Token {
  TokenType type;
  std::string_view content;
};

class ParseError {
  // nice to have - source location
public:
  ParseError(const std::string &desc) : desc(desc) {}
  ~ParseError() = default;

  ParseError(const ParseError &other) = default;
  ParseError &operator=(const ParseError &other) = default;

  ParseError(ParseError &&other) = default;
  ParseError &operator=(ParseError &&other) = default;

  std::string what() const { return {desc}; }

private:
  std::string desc{};
};

class ParseResult {
public:
  class Parsed {
  public:
    void add(const Token &t) { toks.push_back(t); }

  private:
    std::vector<Token> toks;
  };

  ParseResult() = default;
  ParseResult(std::string_view s) : remaining(s) {}
  ~ParseResult() = default;

  [[nodiscard]] bool has_error() const { return !errors.empty(); }

private:
  Parsed parsed{};
  std::vector<ParseError> errors{};
  std::string_view remaining;
};

class Parser {
public:
  Parser() noexcept = default;
  ~Parser() noexcept = default;

  Parser(const Parser &other) = delete;
  Parser &operator=(const Parser &other) = delete;

  Parser(Parser &&other) = delete;
  Parser &operator=(Parser &&other) = delete;

  [[nodiscard]] ParseResult parse(std::string_view in) {
    scanner.init(in);
    advance();
    // do actual parsing
    match_expr();
    return res;
  }

private:
  ParseResult res{};
  bool done{false};
  Scanner scanner;
  std::string_view current_token{};

  constexpr std::string_view next_token() { return scanner.next_token(); }

  constexpr void advance() { current_token = next_token(); }

  using Matcher = bool (Parser::*)(void);

  std::function<bool(void)> to_callable(Matcher f) {
    return [f, this]() { return (this->*f)(); };
  }

  std::function<bool(void)> p_and(std::function<bool(void)> f,
                                  std::function<bool(void)> g) {
    return [f, g, this]() {
      if (!f()) {
        return false;
      }

      advance();

      if (!g()) {
        return false;
      }

      advance();

      return true;
    };
  }

  std::function<bool(void)> p_or(std::function<bool(void)> f,
                                 std::function<bool(void)> g) {
    return [f, g, this]() {
      if (f()) {
        advance();
        return true;
      }

      if (g()) {
        advance();
        return true;
      }

      return false;
    };
  }

  bool match(const char c) {
    return current_token.size() == 1 and current_token[0] == c;
  }

  bool match(const std::string_view target) { return current_token == target; }

  bool match_lparen() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return match('(');
  }

  bool match_rparen() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return match(')');
  }

  bool match_expr() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return p_or(p_or(p_or(to_callable(&Parser::match_paren_expr),
                          to_callable(&Parser::match_binop)),
                     to_callable(&Parser::match_uniop)),
                to_callable(&Parser::match_num))();
  }

  bool match_num() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return false;
  }

  bool match_plus() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return match('+');
  }

  bool match_minus() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return match('-');
  }

  bool match_binop() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return p_and(p_and(to_callable(&Parser::match_expr),
                       p_or(to_callable(&Parser::match_plus),
                            to_callable(&Parser::match_minus))),
                 to_callable(&Parser::match_expr))();
  }

  bool match_uniop() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return p_and(to_callable(&Parser::match_minus),
                 to_callable(&Parser::match_expr))();
  }

  bool match_paren_expr() {
    my_utils::logging::log_function(
        std::source_location::current().function_name());

    return p_and(p_and(to_callable(&Parser::match_lparen),
                       to_callable(&Parser::match_expr)),
                 to_callable(&Parser::match_rparen))();
  }
};

class Calculator {
public:
  Calculator() noexcept = default;
  ~Calculator() = default;

  [[nodiscard]] int eval(ParseResult parsed) { return 0; }

  [[nodiscard]] int calculate(std::string_view in) {
    return eval(parser.parse(in));
  }

private:
  Parser parser;
};

} // namespace

int calculate(std::string s) {

  Scanner scanner{};
  scanner.init(s);

  std::string_view token{};
  while (!(token = scanner.next_token()).empty()) {
    std::cout << token << '\n';
  }

  Calculator calc{};

  return calc.calculate(s);
}
