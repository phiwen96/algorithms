#pragma once
#include "common.hpp"
#include "lexeme.hpp"

/// lkml
#define TOKEN \
    X (TOKEN_COLON) \
    X (TOKEN_WHITESPACE) \
    X (TOKEN_LEFT_PAREN, '(') \
    X (TOKEN_RIGHT_PAREN, ')') \
    X (TOKEN_LEFT_BRACE, '{') \
    X (TOKEN_RIGHT_BRACE, '}') \
    X (TOKEN_LEFT_BRACKET, '[') \
    X (TOKEN_RIGHT_BRACKET, ']') \
    X (TOKEN_COMMA, ',') \
    X (TOKEN_DOT, ',') \
    X (TOKEN_MINUS, '-') \
    X (TOKEN_PLUS, '+') \
    X (TOKEN_SEMICOLON, ';') \
    X (TOKEN_SLASH, '/') \
    X (TOKEN_STAR, '*') \
    X (TOKEN_BANG, '!') \
    X (TOKEN_BANG_EQUAL, '!', '=') \
    X (TOKEN_EQUAL, '=') \
    X (TOKEN_EQUAL_EQUAL, '=', '=') \
    X (TOKEN_GREATER) \
    X (TOKEN_GREATER_EQUAL) \
    X (TOKEN_LESS) \
    X (TOKEN_LESS_EQUAL) \
    X (TOKEN_IDENTIFIER) \
    X (TOKEN_STRING) \
    X (TOKEN_NUMBER, double value = strtod (parser.previous.start, NULL); emitConstant(value);) \
    X (TOKEN_AND) \
    X (TOKEN_CLASS) \
    X (TOKEN_ELSE) \
    X (TOKEN_FALSE) \
    X (TOKEN_FOR) \
    X (TOKEN_FUN) \
    X (TOKEN_IF) \
    X (TOKEN_NIL) \
    X (TOKEN_OR) \
    X (TOKEN_PRINT) \
    X (TOKEN_RETURN) \
    X (TOKEN_SUPER) \
    X (TOKEN_THIS) \
    X (TOKEN_TRUE) \
    X (TOKEN_VAR) \
    X (TOKEN_WHILE) \
    X (TOKEN_ERROR) \
    X (TOKEN_EOF)
//BOOST_PP_VARIADIC_SIZE (__VA_ARGS__)


template <char>
struct token_imp;

template <>
struct token_imp <'('>
{
    lexeme lex;
};

template <typename parser>
struct token_number
{
    cexp bool number = true;
    cexp bool identifier = false;
    cexp char const* lexeme = "";
};

struct token
{

    enum type
    {
        
#define X(tok, ...) \
tok,
        TOKEN
#undef X
        
        
        //single-character tokens
//        TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
//        TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
//        TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
//        TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
//
//        //one or two character tokens
//        TOKEN_BANG, TOKEN_BANG_EQUAL,
//        TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
//        TOKEN_GREATER, TOKEN_GREATER_EQUAL,
//        TOKEN_LESS, TOKEN_LESS_EQUAL,
//
//        //literals
//        TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
//
//        //keywords
//        TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
//        TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
//        TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
//        TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,
//
//        TOKEN_ERROR, TOKEN_EOF
    };
    
    type t;
    lexeme lex;
    int line {0};
};


enum
{
#define X(x, ...) \
x,
    TOKEN
#undef X
};

template <typename Lexeme>
struct toki
{
    using lexeme_type = Lexeme;
    
    
    int type;
    lexeme_type lexeme;
    int line {0};
};

