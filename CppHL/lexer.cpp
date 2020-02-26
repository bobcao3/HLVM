#include "lexer.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include "bstrlib/buniutil.h"
#include "bstrlib/utf8util.h"
#include "consts.hpp"
#include "lexer_fsm.hpp"

bool match_cp(cpUcs4 c, bool match_null, CBString& str)
{
  if (match_null) {
    return c == 0;
  }

  if (str.length() == 0)
    return true;

  utf8Iterator iter_match;
  utf8IteratorInit(&iter_match, str.data, str.length());

  while (cpUcs4 m = utf8IteratorGetNextCodePoint(&iter_match, 0)) {
    if (c == 0 || m == 0)
      return false;
    if (m == c)
      return true;
  }

  return false;
}

int lex_string(CBString* source, CBString* filename)
{
  utf8Iterator iter_src;
  utf8IteratorInit(&iter_src, source->data, source->length());

  std::vector<cpUcs4> seperators;

  std::vector<LexerToken> tokens;

  size_t lines = 0;
  size_t columns = 0;

  bool error = false;

  LexerToken curr_tok("", *filename, 0, 0);

  TokenizerState state = ST_WORD;

  while (state != ST_END) {
    cpUcs4 c = utf8IteratorGetNextCodePoint(&iter_src, 0);

    int i = 0;
    for (auto& t : transitions) {
      if (t.prev == state || t.prev == ST_ANY) {
        if (match_cp(c, t.match_null, t.matching_string)) {
          if (t.emit_token_before && curr_tok.token.length() > 0) {
            tokens.push_back(curr_tok);
            curr_tok.token = "";
            curr_tok.line = lines;
            curr_tok.column = columns;
          }

          if (t.append_to_token) {
            buAppendBlkUcs4(&curr_tok.token, &c, 1, 0);
          }

          if (t.emit_token_after && curr_tok.token.length() > 0) {
            tokens.push_back(curr_tok);
            curr_tok.token = "";
            curr_tok.line = lines;
            curr_tok.column = columns;
          }

          if (t.error) {
            error = true;
          }

          state = t.next;
          break;
        }
      }
      i++;
    }

    if (error) {
      std::cerr << "Error on " << lines << ":" << columns << std::endl;
      break;
    }

    columns++;
    if (c == '\n') {
      lines++;
      columns = 0;
    }
  }

  for (auto& t : tokens) {
    std::cout << "{" << t.token << "},";
  }
  std::cout << std::endl;

  return 0;
}

int lex_file(const char* filename)
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size)) {
    return -1;
  }

  CBString source(buffer.data());

  std::cout << "=====================\n INPUT FILE\n=====================\n"
            << source << "\n=====================" << std::endl;

  return lex_string(&source, new CBString(filename));
}