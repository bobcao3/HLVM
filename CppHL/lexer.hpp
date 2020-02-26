#pragma once

#include "bstrlib/bstrwrap.h"

enum TokenType
{
  UNKNOWN,
  WORD,
  DELIMS,
  OPERATORS
};

struct LexerToken
{
  CBString token;
  CBString file;
  size_t line;
  size_t column;

  LexerToken(CBString t, CBString f, size_t l, size_t c)
    : token(t)
    , file(f)
    , line(l)
    , column(c)
  {}
};

int lex_file(const char* filename);