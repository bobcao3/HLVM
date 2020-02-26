#pragma once

#include "bstrlib/bstrwrap.h"

enum TokenizerState
{
  ST_WORD,
  ST_STR,
  ST_STR_ESC,
  ST_COMMENT,
  ST_END,
  ST_ANY
};

struct ToeknizerStateTransition
{
  TokenizerState prev;
  TokenizerState next;
  bool match_null;
  CBString matching_string;
  bool emit_token_before;
  bool append_to_token;
  bool emit_token_after;
  bool error;
};

static ToeknizerStateTransition transitions[] = {
  { ST_WORD, ST_END, true, "", true, false, false, false },
  { ST_ANY, ST_END, true, "", true, false, false, true },
  { ST_WORD, ST_WORD, false, ";+-*/|&~:<>,.;\n", true, true, true, false },
  { ST_WORD, ST_WORD, false, " \t\r", true, false, false, false },
  { ST_WORD, ST_STR, false, "\"", true, false, false, false },
  { ST_STR, ST_STR_ESC, false, "\\", false, true, false, false },
  { ST_STR_ESC, ST_STR, false, "", false, true, false, false },
  { ST_STR, ST_WORD, false, "\"", true, false, false, false },
  { ST_STR, ST_STR, false, "", false, true, false, false },
  { ST_WORD, ST_COMMENT, false, "#", true, false, false, false },
  { ST_COMMENT, ST_WORD, false, "\n", false, false, false, false },
  { ST_COMMENT, ST_COMMENT, false, "", false, false, false, false },
  { ST_WORD, ST_WORD, false, "", false, true, false, false }
};