#include "lexer.hpp"
#include <cctype>
#include <unordered_map>

Lexer::Lexer(const std::string &src) : source(src), pos(0), line(1), col(1) {}

char Lexer::peek() { return pos < source.size() ? source[pos] : '\0'; }

char Lexer::advance() {
  char c = peek();
  pos++;
  if (c == '\n') {
    line++;
    col = 1;
  } else
    col++;
  return c;
}

void Lexer::skipWhitespace() {
  while (std::isspace(peek()))
    advance();
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (true) {
    skipWhitespace();
    Token t = nextToken();
    tokens.push_back(t);
    if (t.type == TokenType::EndOfFile)
      break;
  }
  return tokens;
}

Token Lexer::nextToken() {
  skipWhitespace();
  int startCol = col;

  char c = peek();
  if (std::isdigit(c)) {
    std::string num;
    while (std::isdigit(peek()))
      num += advance();
    return {TokenType::Number, num, line, startCol};
  }

  if (std::isalpha(c)) {
    std::string id;
    while (std::isalnum(peek()))
      id += advance();
    if (id == "print")
      return {TokenType::Print, id, line, startCol};
    return {TokenType::Identifier, id, line, startCol};
  }

  switch (c) {
  case '+':
    advance();
    return {TokenType::Plus, "+", line, startCol};
  case '*':
    advance();
    return {TokenType::Star, "*", line, startCol};
  case '=':
    advance();
    return {TokenType::Assign, "=", line, startCol};
  case ';':
    advance();
    return {TokenType::Semicolon, ";", line, startCol};
  case '(':
    advance();
    return {TokenType::LParen, "(", line, startCol};
  case ')':
    advance();
    return {TokenType::RParen, ")", line, startCol};
  case '\0':
    return {TokenType::EndOfFile, "", line, startCol};
  default:
    advance();
    return {TokenType::Invalid, std::string(1, c), line, startCol};
  }
}
