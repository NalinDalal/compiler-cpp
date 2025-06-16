#pragma once
#include <string>

enum class TokenType {
  Identifier,
  Number,
  Plus,
  Star,
  Assign,
  Print,
  Semicolon,
  LParen,
  RParen,
  EndOfFile,
  Invalid
};

struct Token {
  TokenType type;
  std::string value;
  int line, col;
};
