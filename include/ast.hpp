#pragma once
#include <memory>
#include <string>
#include <vector>

enum class ASTNodeType { Number, Identifier, BinaryOp, Assign, Print };

struct ASTNode {
  ASTNodeType type;
  virtual ~ASTNode() = default;
};

struct NumberNode : ASTNode {
  int value;
  NumberNode(int val) : value(val) { type = ASTNodeType::Number; }
};

struct IdentifierNode : ASTNode {
  std::string name;
  IdentifierNode(std::string id) : name(std::move(id)) {
    type = ASTNodeType::Identifier;
  }
};

struct BinaryOpNode : ASTNode {
  char op;
  std::shared_ptr<ASTNode> left, right;
  BinaryOpNode(char op, std::shared_ptr<ASTNode> l, std::shared_ptr<ASTNode> r)
      : op(op), left(std::move(l)), right(std::move(r)) {
    type = ASTNodeType::BinaryOp;
  }
};

struct AssignNode : ASTNode {
  std::string var;
  std::shared_ptr<ASTNode> expr;
  AssignNode(std::string v, std::shared_ptr<ASTNode> e)
      : var(std::move(v)), expr(std::move(e)) {
    type = ASTNodeType::Assign;
  }
};

struct PrintNode : ASTNode {
  std::shared_ptr<ASTNode> expr;
  explicit PrintNode(std::shared_ptr<ASTNode> e) : expr(std::move(e)) {
    type = ASTNodeType::Print;
  }
};
