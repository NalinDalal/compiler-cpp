#pragma once
#include "token.hpp"
#include <string>
#include <vector>

class Lexer {
public:
  explicit Lexer(const std::string &src);
  std::vector<Token> tokenize();

private:
  char peek();
  char advance();
  void skipWhitespace();
  Token nextToken();

  std::string source;
  size_t pos;
  int line, col;
};
