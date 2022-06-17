#include "Main.hpp"
#include "neObj.hpp"

#include <fstream>

int langMode;
int debugMode;

string splitStr(string s1) {
    string ret;
    for (auto tmp:s1) {
        if (tmp == '.') 
            return ret;
        ret += tmp;
    }
    return "";
}

void Main::open() {

	string filedata;
	std::ifstream reading_file;
	reading_file.open(fileName, std::ios::in);

    while (std::getline(reading_file, filedata))
		fileData += filedata;
    return;
}

void Main::write() {    
    string fileBuf;
    std::ofstream writing_file;
    writing_file.open(splitStr(fileName)+".c", std::ios::out);
    writing_file << runCode;
    writing_file.close();
}

int isDigit(string s1) {
    for (int i=0;i<s1.length();i++) {
        if (!isdigit(s1[i]))
            return True;
    }
    return False;
}

int main(void) {
	debugMode = 1;
    Main mainclass;
    vector<tokens> token;
	mainclass.fileName = "main.my";

	mainclass.open();

    langMode = CPP;
    token = lexer.lex(mainclass.fileData);
    mainclass.runCode = node.parse(token);
	(langMode == PYTHON) ? mainclass.runCode+="\nmain()" : mainclass.runCode+="\nint start(void) {\n\treturn main();\n}";

	mainclass.write();
    return 0;
}
