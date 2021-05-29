#pragma once
#include "array.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "opcode.hpp"


/*
 The compiler will take the user’s program and fill up the chunk with bytecode.
 At least, that’s what it will do if the program doesn’t have any compile errors.
 
 A compiler has roughly two jobs. It parses the user’s source code to understand what it means. Then it takes that knowledge and outputs low-level instructions that produce the same semantics.
 */
struct compiler
{
    array <int> code;
    array <int> consts;
    scanner sc;
    parser prs;
    
    compiler (char const* source) : sc {source}
    {
        advance ();
        expression ();
        consume (token::type::TOKEN_EOF, "Expect end of expression.");
        emit_return ();
    }
    
    // returns whether or not compilation succeeded
    operator bool () const
    {
        return not prs.had_error;
    }
    
private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// parsing utility functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    /*
     It asks the scanner for the next token and stores it for later use.
     Before doing that, it takes the old current token and stashes that in a previous field.
     */
    auto advance () -> void
    {
        prs.previous = prs.current;
        
        prs.current = sc.scan_token ();
        
        if (prs.current.t == token::type::TOKEN_ERROR)
        {
            throw;
        }
    }
    
    /*
     It’s similar to advance() in that it reads the next token.
     But it also validates that the token has an expected type.
     If not, it reports an error. This function is the foundation
     of most syntax errors in the compiler.
     */
    auto consume (token::type t, const char* msg) -> void
    {
      if (prs.current.t == t)
      {
        advance ();
        return;
      }

      error_at_current (msg);
    }
    
    auto expression () -> void
    {
        
    }
    
    auto unary() -> void
    {
      token::type operatorType = prs.previous.t;

      // Compile the operand.
      expression ();

      // Emit the operator instruction.
      switch (operatorType)
      {
          case token::type::TOKEN_MINUS: emit_bytes (opcode::OP_NEGATE); break;
          default: return; // Unreachable.
      }
    }
    
    auto grouping() -> void
    {
      expression ();
      consume (token::type::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    }
    
    auto number() -> void
    {
      int value = strtod (prs.previous.start, NULL);
      emit_constants (value);
    }
    
    auto error_at_current(const char* msg) -> void
    {
        error_at (&prs.current, msg);
    }
    
    auto error(const char* msg) -> void
    {
        error_at (&prs.previous, msg);
    }
    
    auto error_at (token* tok, const char* msg) -> void
    {
        if (prs.panic_mode)
        {
            return;
        }
        
        prs.panic_mode = true;
        
        fprintf (stderr, "[line %d] Error", tok->line);
        
        if (tok->t == token::type::TOKEN_EOF)
        {
            fprintf(stderr, " at end");
            
        } else if (tok->t == token::type::TOKEN_ERROR)
        {
            // Nothing.
        } else
        {
            fprintf(stderr, " at '%.*s'", tok->length, tok->start);
        }
        
        fprintf (stderr, ": %s\n", msg);
        prs.had_error = true;
    }
    
    
    
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// code generation utility functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto emit_constants(int value) -> void
    {
      emit_bytes (opcode::OP_CONSTANT, make_constant (value));
    }
    
    auto make_constant (int value) -> int
    {
        consts += value;
        int index = consts.active ();
        
//      if (constant > UINT8_MAX) {
//        error("Too many constants in one chunk.");
//        return 0;
//      }

      return index;
    }
    
    auto emit_return () -> void
    {
        emit_bytes (opcode::OP_RETURN);
    }
    
    auto emit_bytes (auto... b) -> void
    {
        ((code += b), ...);
    }
    
    
    
    
};
