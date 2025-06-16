#pragma once
#include "ast.hpp"
#include "token.hpp"
#include <memory>
#include <vector>

class Parser {
public:
  explicit Parser(const std::vector<Token> &tokens);
  std::vector<std::shared_ptr<ASTNode>> parse();

private:
  std::shared_ptr<ASTNode> parseStatement();
  std::shared_ptr<ASTNode> parseExpression();
  std::shared_ptr<ASTNode> parsePrimary();
  std::shared_ptr<ASTNode> parseFactor();
  std::shared_ptr<ASTNode> parseTerm();

  const Token &peek();
  const Token &advance();
  bool match(TokenType type);

  const std::vector<Token> &tokens;
  size_t pos;
};
