#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

enum  tokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, END };

#include <string>
using namespace std;
class Token
{
private:
	int myLine;
	string myValue;
	tokenType myTokenType;
	map<tokenType, string> tokenMap;

public:
	string print();
	string lineToString();
	Token(tokenType type, string textVal, int line);
	//LAB 2
	string getType();
	string getText();
};





#endif // !TOKEN_H
