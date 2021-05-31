#pragma once
//#include "token.hpp"

template <typename TokenType>
struct parser
{
    using token_type = TokenType;
    
    
    token_type current;
    token_type previous;
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



template <typename T>
struct parse_rule
{
    using parse_fn =  void (*)();
    parse_fn prefix;
    parse_fn infix;
    parse_fn precedence;
};
