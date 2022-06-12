#include "Main.hpp"
#include "neObj.hpp"

#include <fstream>

int langMode;

void Main::open() {

	string filedata;
	std::ifstream reading_file;
	reading_file.open(fileName, std::ios::in);

        while (std::getline(reading_file, filedata))
			fileData += filedata;
        return;
}

int main(void) {
    Main mainclass;
    vector<tokens> token;
    vector<string> runCode;
	/*
    mainclass.fileData = "fn restart (x: auto) : int {"                 "\n"
                         "    let x:auto = 13;"                       "\n"
						 "    if x < 35 {"                            "\n"
                         "        put x;"                             "\n"
						 "    }"                                      "\n"
                         "    return x;"                              "\n"
                         "}"                                          "\n"
                         "fn main () : int {"                         "\n"
                         "         restart(x);"                         "\n"
                         "}"                                          "\n";
						 */
	mainclass.fileName = "main.my";

	mainclass.open();

    langMode = PYTHON;
    token = lexer.lex(mainclass.fileData);
    runCode = parser.parse(token);
	langMode == PYTHON ? runCode.push_back("main()") : runCode.push_back("_start():");
    for (auto tmp : runCode)
        cout << tmp << endl;
    return 0;
}
