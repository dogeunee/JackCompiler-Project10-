#pragma once
#include <set>
#include <string>
namespace TokenType
{
    enum TokenType
    {
        KEYWORD,
        SYMBOL,
        IDENTIFIER,
        INT_CONST,
        STRING_CONST,
        EMPTY
    };
};
namespace KeyWord
{
    enum KeyWord
    {
        CLASS,
        METHOD,
        FUNCTION,
        CONSTRUCTOR,
        INT,
        BOOLEAN,
        CHAR,
        VOID,
        VAR,
        STATIC,
        FIELD,
        LET,
        DO,
        IF,
        ELSE,
        WHILE,
        RETURN,
        TRUE,
        FALSE,
        _NULL,
        THIS
    };
};
namespace kind
{
    enum kind
    {
        STATIC,
        FIELD,
        ARG,
        VAR,
        NONE
    };
};
namespace segment
{
    enum segment
    {
        CONST,
        ARG,
        LOCAL,
        STATIC,
        THIS,
        THAT,
        POINTER,
        TEMP
    };
};
namespace command
{
    enum command
    {
        ADD,
        SUB,
        NEG,
        EQ,
        GT,
        LT,
        AND,
        OR,
        NOT,
        MULT,
        DIV
    };
};