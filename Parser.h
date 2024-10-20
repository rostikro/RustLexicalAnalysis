//
// Created by rostyslav.romanets on 10/19/2024.
//

#ifndef PARSER_H
#define PARSER_H

enum TokenType
{
    KEYWORD,
    IDENTIFIER,
    FUNCTION_IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    HEX_LITERAL,
    STRING_LITERAL,
    OPERATOR,
    COMMENT,
    DOC_COMMENT,
    PUNCTUATOR,
    MACROS,
    UNKNOWN,
};


#endif //PARSER_H
