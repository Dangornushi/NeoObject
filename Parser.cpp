#include "Parser.hpp"
#include "Node.hpp"

// loop to the end of file.
string Node::parse(vector<tokens> geToken) {
    tokNumCounter = 0;
    string write;
    token = geToken;
	write = functionDefiniton();

    return write;
}

void Node::expect(string str) {
	if (token[tokNumCounter].tokChar != str) {
		cout << "Err: " << token[tokNumCounter].tokChar << "But: " << str << endl;
		exit(1);
	}
}

string Node::functionDefiniton() {
    if (token[tokNumCounter].tokNum == FN) {
        string argment = "";
        string functionName;
        string functionType;
		string functionData;
		string ret;

		indent++;

        tokNumCounter++; // fn

        functionName = word();

        tokNumCounter++;

        if (token[tokNumCounter].tokNum == LBRACKET) {
            tokNumCounter++; // (
			if (token[tokNumCounter].tokNum != RBRACKET)
            	argment = funcDefArtgment();
            tokNumCounter++; // )
	
        }

        expect(":");

        tokNumCounter++;

        functionType = word();

		string Fsent = "fn " + functionName + "(" + argment + ") : ";  


        if (functionType == "auto") {
			cout << Fsent + functionType << endl;;
            for (int i= 0; i < Fsent.length();i++)
                cout << " " << std::flush;
            cout << "^ Can't use 'auto' for function return value." << endl;
        }

        tokNumCounter++;

        expect("{");

        tokNumCounter++;

		functionData = sent();

        expect("}");

        tokNumCounter++;

		indent--;

		valMemory.push_back({0, False, functionType, functionName});

		ret = functionType + " " + functionName + " (" + argment + ") {\n" + functionData + "\n}" + functionDefiniton();
		

        return ret;
    }
    return "";
}


string Node::sent() {
    switch (token[tokNumCounter].tokNum) {
        case LET: {
            int isMut;
            string valueName;
            string valueType;
            string data;
            string ret;

            expect("let");
            tokNumCounter++;
            if (token[tokNumCounter].tokNum == MUT) {
                isMut = True;
                tokNumCounter++;
            } else
                isMut = False;

            valueName = token[tokNumCounter++].tokChar;

            expect(":");

            tokNumCounter++;

            //if (valMemory.)
            valueType = token[tokNumCounter++].tokChar;

            expect("<-");

            tokNumCounter++;

            data = addSub();

            expect(";");

            tokNumCounter++;

            int hasType = True;

            for (vector<Type>::const_iterator i = valMemory.begin(); i != valMemory.end(); i++) {
                if (i->name == valueName)
                    // もうすでに変数が存在する
                    break;
                else
                    // 初めて宣言される
                    hasType = False;
            }

			valMemory.push_back({0, isMut, valueType, valueName});
            if (hasType == True)
                ret = addIndent() + valueName + " = " + data + ";\n" + sent() ;
            else
                ret = addIndent() + valueType + " " +  valueName + " = " + data + ";\n" + sent() ; 

            return ret;

    } break;
		case RETURN: {
			expect("return");
            tokNumCounter++;

			string ret =  addIndent() + "return " + expr() + ";";

            tokNumCounter++;
			expect(";");
            tokNumCounter++;

			return ret + sent();

		} break;
    }
    return " ";
}

string Node::addSub() {
	if (token[tokNumCounter+1].tokNum == PLUS) {
		string s1 = mulDiv();
		tokNumCounter += 2;
		string s2 = mulDiv();
		tokNumCounter++;
        if (!isDigit(s1) && !isDigit(s2)) {
            return std::to_string(std::stoi(s1) + std::stoi(s2));
        }
		return s1 + "+" + s2;
	}
	if (token[tokNumCounter+1].tokNum == MIN) {
		string s1 = mulDiv();
		tokNumCounter += 2;
		string s2 = mulDiv();
		tokNumCounter++;
		return s1 + "-" + s2;
	}
	return mulDiv();
}

string Node::mulDiv() {
	if (token[tokNumCounter+1].tokNum == MUL) {
		string s1 = funCall();
		tokNumCounter += 2;
		string s2 = funCall();
		tokNumCounter++;
		return s1 + "*" + s2;
	}
	if (token[tokNumCounter+1].tokNum == DIV) {
		string s1 = funCall();
		tokNumCounter += 2;
		string s2 = funCall();
		tokNumCounter++;
		return s1 + "/" + s2;
	}
	return funCall();
}

string Node::funCall() {
	if (token[tokNumCounter+1].tokNum == LBRACKET) {
		string funcName = token[tokNumCounter++].tokChar;
		tokNumCounter++;
		string argment = funcCallArtgment();
		expect(")");
        string ret = funcName + "(" + argment + ")";
		tokNumCounter++;
		return ret;
	}
	return expr();
}

string Node::expr() {
	if (token[tokNumCounter].tokNum == LBRACKET) {
		tokNumCounter++;
		string ret = addSub();
		expect(")");
//		tokNumCounter++;
        return ret;
	}
	return word();
}


string Node::word() {
    return token[tokNumCounter].tokChar;
}

string Node::funcCallArtgment() {
	string returnFunctionArgment = "";
	string oneArgment;

	while (1) {
        if (token[tokNumCounter].tokNum== RBRACKET) {
            break;
		}
        if (token[tokNumCounter - 1].tokNum == CANMA) {
            oneArgment.push_back(',');
        }
        else {
            string arg = addSub();
            for (int i = 0; i < arg.length(); i++)
                oneArgment.push_back(arg[i]);
            if (token[tokNumCounter].tokNum == RBRACKET) {
                break;
            }
            tokNumCounter++;
        }
    }

	return oneArgment;
}

string Node::funcDefArtgment() {
	string returnFunctionArgment = "";
	vector<string> oneArgment;

	while (1) {
        if (token[tokNumCounter - 1].tokChar[0] == ',' || token[tokNumCounter].tokChar[0] == ')') {
            returnFunctionArgment += oneArgment[2] + " " + oneArgment[0];
            returnFunctionArgment += ", ";
			oneArgment = {};
        }
        if (token[tokNumCounter].tokChar[0] == ')') {
			returnFunctionArgment.erase(returnFunctionArgment.end()-2, returnFunctionArgment.end());
            break;
		}
        else {
            oneArgment.push_back(token[tokNumCounter].tokChar);
            tokNumCounter++;
        }
    }

	return returnFunctionArgment;
}

string Node::addIndent() {
	string ret = "";
	for (int i=0;i<indent;i++)
		ret += "\t"; 
	return ret;
}

