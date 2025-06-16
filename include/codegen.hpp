#pragma once
#include "ir.hpp"
#include <string>
#include <vector>

class CodeGen {
public:
  void generateAssembly(const std::vector<IRInstruction> &ir,
                        const std::string &outFile);
};
