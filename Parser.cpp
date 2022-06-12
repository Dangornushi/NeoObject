#include "Parser.hpp"

// loop to the end of file.
vector<string> Parser::parse(vector<tokens> geToken) {
    vector<string> writeVector;
    token = geToken;
    tokNumCounter = 0;
    nowIndent = 0;
    writeVector.push_back(parserSort(token[tokNumCounter].tokNum));
    return writeVector;
}

// the tokens sort.
string Parser::parserSort(int tokenByte) {
    string writeData = "";
    cout << "DEBUG: " << token[tokNumCounter].tokChar << endl;
    switch (tokenByte) {
            // define the function
        case FN: {
            string functionName = "";
            string argment = "";
            string type = "";

            tokNumCounter++;

            // entry point ?
            if (token[tokNumCounter].tokNum == ENTRY) {
				functionName = "main";
            } else {
				// get function name
                functionName = parserSort(token[tokNumCounter].tokNum);
            }

            // tokNumCounter: (
            tokNumCounter++;
            // tokNumCounter: argment or )

            if (token[++tokNumCounter].tokChar[0] != ')') {
                // get argment

                if (langMode == PYTHON)
                    argment = getArgment(PY_D_C);
                else
                    argment = getArgment(C_DEF);
            } else
                ;

			// tokNumCounter: )
            tokNumCounter+=2;
            // tokNumCounter: : type

			type = token[++tokNumCounter].tokChar;

			// tokNumCounter: {
            tokNumCounter++;
            // tokNumCounter:  something

			// add indent
			nowIndent++;

            langMode == PYTHON ? writeData = "def " + functionName + "(" + argment + "):"
                               : writeData = "void" + functionName + "(" + argment + ") {";

			// ここから
        	writeData += "\n" + parserSort(token[tokNumCounter].tokNum);

			// ここまでで何かが起こってる

			if (langMode == CPP)
				writeData += "}";

			// sub indent
			nowIndent--;

			tokNumCounter+=2;
			writeData += parserSort(token[tokNumCounter].tokNum);
        } break;
        case PUT: {

            string putArgment = "";

            // tokNumCounter: put
            tokNumCounter++;
            // tokNumCounter: put argment

            putArgment = parserSort(token[tokNumCounter].tokNum);

            tokNumCounter++;
			/* ===--- ---=== 
			 * insert expect(";")
			 * ===--- ---===*/
            tokNumCounter++;

            langMode == PYTHON ? writeData = addIndent() + "print(" + putArgment + ")"
                               : writeData = "std::cout << " + putArgment + " << std::endl";

			cout << "OK: PUT END" << endl;

            writeData += "\n" + parserSort(token[tokNumCounter].tokNum);


        } break;
        case LET: {
            string valName = ""; // valetage name
            string valType = ""; // valetage type
            string valData = ""; // valetage data
            string type = ""; // if valetage type is auto; change type name

            tokNumCounter++;
            valName = token[tokNumCounter].tokChar;
            tokNumCounter += 2;
            valType = token[tokNumCounter].tokChar;
            tokNumCounter += 2;
            valData = parserSort(token[tokNumCounter].tokNum);	

            if (langMode == CPP && valType == "auto") {
                isNumber(valData) ? writeData = "int " + valName + " = " + valData + ";"
                                   : writeData = "std::string " +  valName + " = " + valData + ";";
            } else
                ;

            langMode == PYTHON ? writeData = addIndent() + valName + " = " + valData
                               : writeData = type + " " + valName + " = " + valData + ";";
            tokNumCounter++;
			/* ===--- ---=== 
			 * insert expect(";")
			 * ===--- ---===*/
            tokNumCounter++;

			writeData += "\n" + parserSort(token[tokNumCounter].tokNum);
        } break;
        case RETURN: {

            tokNumCounter++;

            string retArg = parserSort(token[tokNumCounter].tokNum);
            tokNumCounter++;
            langMode == PYTHON ? writeData = addIndent() + "return " + retArg
                               : writeData = addIndent() + "return " + retArg + ";";

            writeData += "\n" + parserSort(token[tokNumCounter].tokNum);

        } break;
        case IF: {
            string ifForm = "";
            tokNumCounter++;
            ifForm = parserSort(token[tokNumCounter].tokNum);

            langMode == PYTHON ? writeData = addIndent() + "if " + ifForm + ":"
                               : writeData = addIndent() + "if (" + ifForm + ") {";

            tokNumCounter += 2;

            nowIndent++;

            writeData += "\n" + parserSort(token[tokNumCounter].tokNum);

            nowIndent--;

            if (langMode == CPP)
                writeData += "}";
            else
                /* ===--- ---===
                 * insert expect("}")
                 * ===--- ---===*/
                tokNumCounter++;
            writeData += "\n" + parserSort(token[tokNumCounter].tokNum);
        } break;
        case WORD: {
            char nextChar = token[tokNumCounter + 1].tokChar[0];
			string nowString = token[tokNumCounter].tokChar; 
            if (nextChar == '>' || nextChar == '<') {
                tokNumCounter+=2;
				return nowString + " " + nextChar + " " + parserSort(token[tokNumCounter].tokNum);
			}	
            if (nextChar == '(' && token[tokNumCounter - 1].tokNum != FN) {
                tokNumCounter += 2;
                string funcName = token[tokNumCounter - 2].tokChar;
                writeData = addIndent() + funcName + "(" + getArgment(PY_D_C) + ")";
                cout << "OK: WORD / function name" << endl;
            }	
			else
                writeData += token[tokNumCounter].tokChar;

        } break;
    }
    return writeData;
}

bool Parser::isNumber(const string &str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}

string Parser::getArgment(int mode) {
    vector<Argment> defuncArgment = {};
    vector<string> oneArgment = {};
    string returnArgment = "";
    int argmentCounter = tokNumCounter;
    cout << "OK: getArgment" << endl;
    while (1) {
        if (token[argmentCounter - 1].tokChar[0] == ',' ||
            token[argmentCounter].tokChar[0] == ')') {

			// add argment ( size | len, scope, type, data  )
            defuncArgment.push_back({0, 0, "void", oneArgment[0]});

            oneArgment = {};
            returnArgment += oneArgment[0];
            returnArgment += ", ";
        }
        if (token[argmentCounter].tokChar[0] == ')') {
			returnArgment.erase(returnArgment.end()-2, returnArgment.end());
            break;
		}
        else {
            oneArgment.push_back(token[argmentCounter].tokChar);
            argmentCounter++;
        }
    }
    tokNumCounter = argmentCounter;
    return returnArgment;
}

string Parser::addIndent() {
	string indent = "";
	for (int i=0;i<nowIndent;i++)
		indent += "\t"; 
	return indent;
}

