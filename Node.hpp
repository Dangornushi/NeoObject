#pragma once

#include "neObj.hpp"

#include <cctype>

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

#define I32 4
#define I64 8

struct defArg {
	string type;
	string name;
};

struct Type {
	int len;
	int isMut;
	string type;
	string name;
};


struct Node {

	vector<tokens> token;
    int tokNumCounter;
	int indent;
	void expect(string str);
    string addIndent();
	vector<Type>valMemory;
	string parse(vector<tokens> geToken);

    string functionDefiniton();
	string funCall();
	string sent();
	string funcDefArtgment();
	string funcCallArtgment();
	string expr();
	string mulDiv();
	string addSub();
	string word();

};
