#include "codegen.hpp"
#include <fstream>

void CodeGen::generateAssembly(const std::vector<IRInstruction> &ir,
                               const std::string &outFile) {
  std::ofstream out(outFile);
  out << ".global main\n"
      << ".text\n"
      << "main:\n";

  for (const auto &instr : ir) {
    if (instr.op == "load_const") {
      out << "    mov $" << instr.arg1 << ", %" << instr.result << "\n";
    } else if (instr.op == "add") {
      out << "    mov %" << instr.arg1 << ", %rax\n";
      out << "    add %" << instr.arg2 << ", %rax\n";
      out << "    mov %rax, %" << instr.result << "\n";
    } else if (instr.op == "mul") {
      out << "    mov %" << instr.arg1 << ", %rax\n";
      out << "    imul %" << instr.arg2 << ", %rax\n";
      out << "    mov %rax, %" << instr.result << "\n";
    } else if (instr.op == "store") {
      out << "    mov %" << instr.arg1 << ", %" << instr.result << "\n";
    } else if (instr.op == "print") {
      out << "    mov %" << instr.arg1 << ", %rdi\n";
      out << "    call print_int\n";
    }
  }

  out << "    mov $0, %rax\n    ret\n";
}
