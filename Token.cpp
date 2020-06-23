#include "Token.h"

#include <sstream>


Token::Token(tokenType type, string textVal, int line) {
	myLine = line;
	myValue = textVal;
	myTokenType = type;

	tokenMap[COMMA] = "COMMA";
	tokenMap[PERIOD] = "PERIOD";
	tokenMap[Q_MARK] = "Q_MARK";
	tokenMap[LEFT_PAREN] = "LEFT_PAREN";
	tokenMap[RIGHT_PAREN] = "RIGHT_PAREN";
	tokenMap[COLON] = "COLON";
	tokenMap[COLON_DASH] = "COLON_DASH";
	tokenMap[MULTIPLY] = "MULTIPLY";
	tokenMap[ADD] = "ADD";
	tokenMap[SCHEMES] = "SCHEMES";
	tokenMap[FACTS] = "FACTS";
	tokenMap[RULES] = "RULES";
	tokenMap[QUERIES] = "QUERIES";
	tokenMap[ID] = "ID";
	tokenMap[STRING] = "STRING";
	tokenMap[COMMENT] = "COMMENT";
	tokenMap[UNDEFINED] = "UNDEFINED";
	tokenMap[END] = "EOF";

}

string Token::lineToString() {
	stringstream convert;
	convert << myLine;
	string lineNum = convert.str();
	return lineNum;
}

string Token::print() {
	string output;
	output = "(" + tokenMap[myTokenType] + ",\"" + myValue + "\"," + lineToString() + ")";
	return output;
}


string Token::getType() {
	return tokenMap[myTokenType];
}
string Token::getText() {
	return myValue;
}
