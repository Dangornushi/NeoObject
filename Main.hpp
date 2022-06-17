#pragma once

#include "neObj.hpp"

#include "Lexer.hpp"
#include "Node.hpp"

class Main {
  public:
    string runCode;
    string fileData;
    string fileName;
	void open();
	void write();
};

Lexer lexer;
Node node;
