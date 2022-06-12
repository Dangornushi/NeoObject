#pragma once
#include "neObj.hpp"

#include "Lexer.hpp"
#include "Parser.hpp"

class Main {
  public:
    string fileData;
    string fileName;
	void open();
};

Lexer lexer;
Parser parser;
