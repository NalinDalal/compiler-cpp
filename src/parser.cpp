#include "parser.hpp"
#include <stdexcept>

Parser::Parser(const std::vector<Token> &t) : tokens(t), pos(0) {}

const Token &Parser::peek() { return tokens[pos]; }
const Token &Parser::advance() { return tokens[pos++]; }

bool Parser::match(TokenType type) {
  if (peek().type == type) {
    advance();
    return true;
  }
  return false;
}

std::vector<std::shared_ptr<ASTNode>> Parser::parse() {
  std::vector<std::shared_ptr<ASTNode>> stmts;
  while (peek().type != TokenType::EndOfFile) {
    stmts.push_back(parseStatement());
  }
  return stmts;
}

std::shared_ptr<ASTNode> Parser::parseStatement() {
  if (peek().type == TokenType::Print) {
    advance();
    auto expr = parseExpression();
    if (!match(TokenType::Semicolon))
      throw std::runtime_error("Expected ';'");
    return std::make_shared<PrintNode>(expr);
  } else if (peek().type == TokenType::Identifier) {
    std::string var = advance().value;
    if (!match(TokenType::Assign))
      throw std::runtime_error("Expected '='");
    auto expr = parseExpression();
    if (!match(TokenType::Semicolon))
      throw std::runtime_error("Expected ';'");
    return std::make_shared<AssignNode>(var, expr);
  }
  throw std::runtime_error("Unknown statement");
}

std::shared_ptr<ASTNode> Parser::parseExpression() {
  auto node = parseTerm();
  while (peek().type == TokenType::Plus) {
    advance();
    auto right = parseTerm();
    node = std::make_shared<BinaryOpNode>('+', node, right);
  }
  return node;
}

std::shared_ptr<ASTNode> Parser::parseTerm() {
  auto node = parseFactor();
  while (peek().type == TokenType::Star) {
    advance();
    auto right = parseFactor();
    node = std::make_shared<BinaryOpNode>('*', node, right);
  }
  return node;
}

std::shared_ptr<ASTNode> Parser::parseFactor() {
  if (peek().type == TokenType::Number) {
    int val = std::stoi(advance().value);
    return std::make_shared<NumberNode>(val);
  } else if (peek().type == TokenType::Identifier) {
    return std::make_shared<IdentifierNode>(advance().value);
  } else if (match(TokenType::LParen)) {
    auto node = parseExpression();
    if (!match(TokenType::RParen))
      throw std::runtime_error("Expected ')'");
    return node;
  }
  throw std::runtime_error("Invalid expression");
}
