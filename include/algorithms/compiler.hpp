#pragma once


#include "common.hpp"
#include <ph_concepts/concepts.hpp>


template <typename...>
struct language_type;

template <typename A>
struct language_type <A>
{
    std::string source = "https://github.com/c++";
};

/**
 When the source language is also the implementation language and the source text to be compiled is actually a new version of the compiler itself, the process is called bootstrapping
 */
template <typename source_language, typename implementation_language, typename source_text>
struct bootstrapping
{
    using value_type = bool;
    cexp value_type value = false;
};

template <typename source_language>
struct bootstrapping <source_language, source_language, source_language>
{
    using value_type = bool;
    cexp value_type value = true;
};




template <typename language>
concept Language = requires () {
    typename language::reference_manual_type;
    language::reference_manual;
};



template <typename front_end>
concept is_compiler_front_end = requires () {
    requires (true);
};

template <typename front_end>
concept is_compiler_back_end = requires () {
    requires (true);
};

namespace {
template <int>
struct language_true;

template <int>
struct language_false;

template <>
struct language_true <0>
{
    using reference_manual_type = char const*;
    cexp reference_manual_type reference_manual = "https://github.com/phiwen96/kuk";
};

template <>
struct language_false <0>
{
    
};

static_assert (Language <language_true <0>>, "");
static_assert (not Language <language_false <0>>, "");
}

/**
* The part of a compiler that performs the analysis of the source language text is called the front-end, and the part that does the target language synthesis is the back-end.
 
* If the cimpiler has a very clean design, the froned-end is totally unaware of the tharget language and the back-end is totally unaware of the source language.
 */

template <typename...>
concept Lexer = requires () {
    /**
     Lexer: break the program up in words.
     */1;
};

template <typename...>
concept Parser = requires () {
    /**
     Parser: Check that the syntax of the sentences are correct.
*/
    1;
};

template <typename...>
concept Semantic_analysis = requires () {
    /**
     Semantic analysis: Check that the sentences make sense.
     */
    1;
};

template <typename...>
concept Optimizer = requires () {
    /**
     Optimi<er: Edit the sentences for brevity

     */
    1;
};

template <typename...>
concept Code_generator = requires () {
    /**
     Semantic analysis: Check that the sentences make sense.
     */
    1;
};

template <typename...>
concept Front_end = requires () {
    1;
};


template <typename...>
concept Back_end = requires () {
    1;
};


template <typename...>
concept Impl_language = requires () {
    1;
};

template <typename...>
concept Semantic_representation = requires () {
    1;
};

template <typename T>
concept String = requires (T& str) {
    requires requires ()
    {
        {str [declval (int)]} -> same_as <char>;
        {str.size ()} -> convertible_to <char>;
        
    } or requires () {
        true;
    };
};

struct Bajs
{
    int i;
    auto begin () {return &i;}
    auto end () {return &i;}
};



cexp bool __ = requires (Bajs& b) {
    true;
};

template <typename T>
#define string_type decltype (T::value)
concept Scanner = requires (string_type& v)
{
    
//    requires requires (string_type& v, size_t i)
//    {
//        requires requires ()
//        {
//            {v[i]} -> same_as <char>;
//        };
//        requires requires ()
//        {
//            {v[i]} -> same_as <char>;
//        };
//    };
    true;
};




template <typename compiler>
concept Compiler =
    Lexer <typename compiler::lexer> and
    Parser <typename compiler::parser> and
    Semantic_analysis <typename compiler::semantic_analysis> and
    Optimizer <typename compiler::optimizer> and
    Code_generator <typename compiler::code_generator> and
    Front_end <typename compiler::front_end> and
    Back_end <typename compiler::back_end> and
    Impl_language <typename compiler::impl_language> and
    Semantic_representation <typename compiler::semantic_representation>;






