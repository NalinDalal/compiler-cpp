#include "ir.hpp"

std::string IRGenerator::newTemp() { return "t" + std::to_string(tempCount++); }

void IRGenerator::emit(const IRInstruction &instr) {
  instructions.push_back(instr);
}

std::string IRGenerator::genExpr(const std::shared_ptr<ASTNode> &node) {
  switch (node->type) {
  case ASTNodeType::Number: {
    auto n = std::dynamic_pointer_cast<NumberNode>(node);
    std::string t = newTemp();
    emit({"load_const", std::to_string(n->value), "", t});
    return t;
  }
  case ASTNodeType::Identifier: {
    auto n = std::dynamic_pointer_cast<IdentifierNode>(node);
    return n->name;
  }
  case ASTNodeType::BinaryOp: {
    auto n = std::dynamic_pointer_cast<BinaryOpNode>(node);
    std::string lhs = genExpr(n->left);
    std::string rhs = genExpr(n->right);
    std::string res = newTemp();
    std::string op = (n->op == '+') ? "add" : "mul";
    emit({op, lhs, rhs, res});
    return res;
  }
  default:
    return "";
  }
}

std::vector<IRInstruction>
IRGenerator::generate(const std::vector<std::shared_ptr<ASTNode>> &ast) {
  instructions.clear();
  for (auto &node : ast) {
    if (node->type == ASTNodeType::Assign) {
      auto n = std::dynamic_pointer_cast<AssignNode>(node);
      std::string rhs = genExpr(n->expr);
      emit({"store", rhs, "", n->var});
    } else if (node->type == ASTNodeType::Print) {
      auto n = std::dynamic_pointer_cast<PrintNode>(node);
      std::string val = genExpr(n->expr);
      emit({"print", val, "", ""});
    }
  }
  return instructions;
}
