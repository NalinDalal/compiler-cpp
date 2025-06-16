#pragma once
#include "ast.hpp"
#include <string>
#include <unordered_set>
#include <vector>

class SemanticAnalyzer {
public:
  void analyze(const std::vector<std::shared_ptr<ASTNode>> &nodes);

private:
  std::unordered_set<std::string> definedVars;
  void checkNode(const std::shared_ptr<ASTNode> &node);
};
