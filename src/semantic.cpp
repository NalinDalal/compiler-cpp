#include "semantic.hpp"
#include <stdexcept>

void SemanticAnalyzer::analyze(
    const std::vector<std::shared_ptr<ASTNode>> &nodes) {
  for (auto &node : nodes)
    checkNode(node);
}

void SemanticAnalyzer::checkNode(const std::shared_ptr<ASTNode> &node) {
  switch (node->type) {
  case ASTNodeType::Assign: {
    auto n = std::dynamic_pointer_cast<AssignNode>(node);
    checkNode(n->expr);
    definedVars.insert(n->var);
    break;
  }
  case ASTNodeType::Print: {
    auto n = std::dynamic_pointer_cast<PrintNode>(node);
    checkNode(n->expr);
    break;
  }
  case ASTNodeType::BinaryOp: {
    auto n = std::dynamic_pointer_cast<BinaryOpNode>(node);
    checkNode(n->left);
    checkNode(n->right);
    break;
  }
  case ASTNodeType::Identifier: {
    auto n = std::dynamic_pointer_cast<IdentifierNode>(node);
    if (!definedVars.count(n->name))
      throw std::runtime_error("Undefined variable: " + n->name);
    break;
  }
  default:
    break;
  }
}
