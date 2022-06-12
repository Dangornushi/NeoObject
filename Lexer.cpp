#include "Lexer.hpp"

/*
 * ===---Lexer::lex(Target file's all data)---===
 */

vector<tokens> Lexer::lex(string fileData) {
    int i = 0;
    // inpout tokens
    vector<tokens> token;

    for (int i = 0; i < fileData.size(); i++) {
        // Now lokking word
        char nowChar = fileData[i];
        string addStr;
        int str_c = 0;

        // RESERV | OP | word

        if (nowChar == '\n' || nowChar == ' ' || nowChar == '\t') {
            continue;
        }
        /*===--- fn ---=== */
        if (fileData.substr(i, LEN_FN) == "fn ") {
            token.push_back({FN, "fn"});
            if (fileData.substr(i + LEN_FN, LEN_ENTRY) == "main") {
                token.push_back({ENTRY, "main"});
                i += LEN_ENTRY;
            }
            i += LEN_FN - 1;
            continue;
        }
        /*===--- return ---=== */
        if (fileData.substr(i, LEN_RETURN) == "return ") {
            token.push_back({RETURN, "return"});
            i += LEN_RETURN - 1;
            continue;
        }
        /*===--- let ---=== */
        if (fileData.substr(i, LEN_LET) == "let ") {
            token.push_back({LET, "let"});
            i += LEN_LET - 1;
            continue;
        }
        /*===--- put ---=== */
        if (fileData.substr(i, LEN_PUT) == "put ") {
            token.push_back({PUT, "put"});
            i += LEN_PUT - 1;
            continue;
        }
        /*===--- if ---=== */
        if (fileData.substr(i, LEN_IF) == "if ") {
            token.push_back({IF, "if"});
            i += LEN_IF - 1;
            continue;
        }
		if (fileData.substr(i, LEN_CALL) == "<-") {
            token.push_back({CALL, "<-"});
            i += LEN_CALL;
            continue;
		}
        /*===--- op(MAP : OP) ---=== */
        if (OP.find(nowChar) != OP.end()) {
            token.push_back({OP.find(nowChar)->second, addStr.append(1, nowChar)});
            continue;
        }
        /*===--- else(STR | NUMBER | WORD) ---=== */
        addStr = "";
        char wordChar;
        while (1) {
            wordChar = fileData[i++];
            if (wordChar != '\n' && wordChar != ' ' && OP.find(wordChar) == OP.end()) {
                addStr.append(1, wordChar);
                continue;
            }
            break;
        }
        token.push_back({WORD, addStr});
        addStr = "";
        if (OP.find(wordChar) != OP.end())
            token.push_back({OP.find(wordChar)->second, addStr.append(1, wordChar)});
        i--;
    }
    return token;
}
