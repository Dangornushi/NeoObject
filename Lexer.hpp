#pragma once

#include "neObj.hpp"

#define LEN_CALL 2
#define LEN_FN 3
#define LEN_IF 3
#define LEN_LET 4
#define LEN_MUT 5
#define LEN_PUT 4
#define LEN_ELSE 5
#define LEN_ELIF 5
#define LEN_ENTRY 4
#define LEN_WHILE 6
#define LEN_RETURN 7

class Lexer {
	/* Mapping OPs */
    map<char, RESERV> OP = {
        {'(', LBRACKET},
        {')', RBRACKET},
        {'{', LRIPPLE},
        {'}', RRIPPLE},
        {':', CORON},
        {';', SEMICORON},
        {'\'', SQ},
        {'"', DQ},
        {',', CANMA},
        {'.', PERIOD},
        {'<', BIG},
        {'>', MINI},
		{'+', PLUS},
		{'-', MIN},
		{'*', MUL},
		{'/', DIV},
    };

  public:
    vector<tokens> lex(string fileData);
};
