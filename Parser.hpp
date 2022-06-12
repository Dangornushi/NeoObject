#pragma once

#include "neObj.hpp"

#define INFUNC 0
#define INCLASS 1
#define INSUBANDMAINCLASS 2
#define INFILE 256

#define INT 0
#define STR 1
#define AUTO 2

#define PY_D_C 0
#define C_DEF 1
#define C_CALL 2


struct Argment {
	int Size;
	int ScopeLevel;
	string Type;
	string Data;
};

class Parser {
    int tokNumCounter;
    int nowIndent; // Pyton : now indent counter
    string parserSort(int tokenByte);
    string addIndent();
    string getArgment(int mode);
    vector<tokens> token;
    bool isNumber(const string &str);

  public:
    vector<string> parse(vector<tokens> geToken);
};
