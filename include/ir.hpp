#pragma once
#include "ast.hpp"
#include <memory>
#include <string>
#include <vector>

struct IRInstruction {
  std::string op;
  std::string arg1, arg2, result;
};

class IRGenerator {
public:
  std::vector<IRInstruction>
  generate(const std::vector<std::shared_ptr<ASTNode>> &ast);

private:
  int tempCount = 0;
  std::string newTemp();
  void emit(const IRInstruction &instr);
  std::vector<IRInstruction> instructions;
  std::string genExpr(const std::shared_ptr<ASTNode> &node);
};
