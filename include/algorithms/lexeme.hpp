#pragma once



struct lexeme
{
    char* begin;
    char* end;
    int line;
    
    lexeme (auto& scanner) : begin {scanner.start}, end {scanner.current}, line {scanner.line}
    {
        
    }
};


inline std::ostream& operator<< (std::ostream& os, lexeme const& l)
{
    return os << std::string (l.begin, l.end);
}
