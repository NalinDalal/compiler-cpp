#include "codegen.hpp"
#include "ir.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "semantic.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: nova <source.nova>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string source = buffer.str();

  Lexer lexer(source);
  auto tokens = lexer.tokenize();

  Parser parser(tokens);
  auto ast = parser.parse();

  SemanticAnalyzer sema;
  sema.analyze(ast);

  IRGenerator irgen;
  auto ir = irgen.generate(ast);

  CodeGen codegen;
  codegen.generateAssembly(ir, "out.s");

  system("gcc out.s runtime/print.c -o out");
  std::cout << "Compiled to `out`\n";
  return 0;
}
