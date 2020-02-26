#include "lexer.hpp"

int main(int argc, char** argv)
{
  if (argc > 1) {
    return lex_file(argv[argc - 1]);
  }

  return 0;
}