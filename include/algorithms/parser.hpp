#pragma once
#include "token.hpp"

struct parser
{
    token current;
    token previous;
    bool had_error {false};
    bool panic_mode {false};
};

enum precedence
{
  PREC_NONE,
  PREC_ASSIGNMENT,  // =
  PREC_OR,          // or
  PREC_AND,         // and
  PREC_EQUALITY,    // == !=
  PREC_COMPARISON,  // < > <= >=
  PREC_TERM,        // + -
  PREC_FACTOR,      // * /
  PREC_UNARY,       // ! -
  PREC_CALL,        // . ()
  PREC_PRIMARY
};


using parse_fn =  void (*)();

struct parse_rule
{
    parse_fn prefix;
    parse_fn infix;
    parse_fn precedence;
};
