#include "Tokenizer.h"
#include "Token.h"


#include <fstream>
#include <iostream>

using namespace std;

void Tokenizer::read(string fileName) {

	ifs.open(fileName);
	if (!ifs.is_open()) { // if the file did not open, error
		std::cout << "ERROR: file not open" << std::endl;
	}
	else { // if the file opened correctly...
		while (ifs.peek() != EOF) { // go through every character until the end
			currChar = ifs.get(); // grab the characters and put them into our current Char
			TokenizeMe(); //run tokenize me which accesses current char
		}
		newToken(END, lineNum); // at the end, tokenize the end character
		//cout << "Total Tokens = " << numTokens << endl;


	}
}

void Tokenizer::TokenizeMe() {
	//take in the current character
	//make a case for every thing it could be 
		//break it into alpha/symbol/ other
	//if it matches, take it through if statements and add to the text
	//when it looks good, send it through to token

	//should I do this in Token? or call token?
	char peek = ' ';
	while (isspace(currChar)) { // if it's white space
		if (currChar == '\n') {
			lineNum = lineNum + 1; // add one to line num
		}
		currChar = ifs.get(); // do this until you aren't getting whitespace
	}
	switch (currChar) // check the characters 
	{
	case ',':
		text = ",";
		newToken(COMMA, lineNum);
		break;
	case '.':
		text = ".";
		newToken(PERIOD, lineNum);
		break;
	case '?':
		text = "?";
		newToken(Q_MARK, lineNum);
		break;
	case '(':
		text = "(";
		newToken(LEFT_PAREN, lineNum);
		break;
	case ')':
		text = ")";
		newToken(RIGHT_PAREN, lineNum);
		break;
	case ':':
		text = ":";
		peek = ifs.peek();
		if (peek == '-') {
			text = ":-";
			newToken(COLON_DASH, lineNum);
			currChar = ifs.get();
			break;
		}
		else {
			newToken(COLON, lineNum);
			break;
		}
	case '*':
		text = "*";
		newToken(MULTIPLY, lineNum);
		break;
	case '+':
		text = "+";
		newToken(ADD, lineNum);
		break;

	case '$':
		text = "$";
		newToken(UNDEFINED, lineNum);
		break;
	case '&':
		text = "&";
		newToken(UNDEFINED, lineNum);
		break;
	case '^':
		text = "^";
		newToken(UNDEFINED, lineNum);
		break;


	case '\'':
		stringToken();
		break;

	case '#':
		commentToken();
		break;

	default:
		if (isalpha(currChar)) {
			idToken();
		}
		else if (!ifs.eof()) { // anything else that's thrown at us
			text = text + currChar;
			newToken(UNDEFINED, lineNum);
		}
		break;
	}

}

void Tokenizer::newToken(tokenType type, int line) { // I think this is supposed to be in a Lexer file
	//cout << "newToken: " << text << " " << line << endl;

	Token myToken(type, text, line);
	//cout << numTokens << ":  " << myToken.print() <<endl; // probably get rid of this for lab 2
	if (type != COMMENT) {
		myTokens.push_back(myToken);
	}
	numTokens = numTokens + 1;
	text = "";

}

void Tokenizer::commentToken() {

	text = text + currChar; // add the # character to the our text
	int startLine = lineNum; // keep tracj of lines incase comments start on line 1 but end on line 2
	char peek = ifs.peek();
	if (peek != '|') { //if it's all on one line..
		currChar = ifs.get();
		while (currChar != '\n') {
			text = text + currChar; // keep adding to text until new line
			currChar = ifs.get();
		}
		if (currChar == '\n') { // the comment ends
			lineNum = lineNum + 1;
		}
		newToken(COMMENT, startLine); // take whatever text was gathered and make a new token
	}
	else { // if it's potentially multi lines..
		currChar = ifs.get();
		peek = ifs.peek();
		while ((currChar != '|' || peek != '#') && peek != EOF) { // the comment goes until |# or EOF; as long as neither of those come, we still read in the comment
			if (currChar == '\n') {
				lineNum = lineNum + 1;
			}
			text = text + currChar;
			currChar = ifs.get();
			peek = ifs.peek();
		}
		if (currChar == '|' && peek == '#') {
			text = text + currChar; // add the |
			currChar = ifs.get();
			text = text + currChar; // add the #
			newToken(COMMENT, startLine);
		}
		else if (ifs.eof()) {
			lineNum = lineNum + 1;
			newToken(UNDEFINED, startLine);
		}
	}

}
void Tokenizer::idToken() {
	//text = text + currChar;
	while (isalnum(currChar)) { // only while it's reading numbers or letters..
		text = text + currChar; // add it to the ID/string
		currChar = ifs.get();
	}
	if (text == "Schemes") {
		newToken(SCHEMES, lineNum);
	}
	else if (text == "Facts") {
		newToken(FACTS, lineNum);
	}
	else if (text == "Rules") {
		newToken(RULES, lineNum);
	}
	else if (text == "Queries") {
		newToken(QUERIES, lineNum);
	}
	else {
		newToken(ID, lineNum);
	}
	TokenizeMe(); // since our while loop moved us forward a character, we have to tokenize it


}
void Tokenizer::stringToken() {
	bool endString = false;
	text = text + currChar;
	int startLine = lineNum;
	char peek = ' ';
	while (endString == false) {
		if (ifs.peek() == EOF) {
			newToken(UNDEFINED, startLine);
			endString = true;
		}
		else {
			currChar = ifs.get();
			switch (currChar)
			{
			case '\n':
				lineNum = lineNum + 1;
				text = text + currChar;
				break;
			case '\'':
				text = text + currChar;
				peek = ifs.peek();
				if (peek != '\'') {
					newToken(STRING, startLine);
					endString = true;
				}
				else {
					currChar = ifs.get();
					text = text + currChar;
				}
				break;
			default:
				text = text + currChar;
				break;
			}
		}
	}

}


// LAB2
string Tokenizer::printMe(int index) {

	unsigned int mySize = myTokens.size();
	if ((unsigned)index >= mySize) {
		cout << "Call for: " << index << " on size of: " << mySize << endl;
		return "ERROR printMe";
	}
	return myTokens.at(index).print();
}

string Tokenizer::getTokenType(int index) {
	unsigned int mySize = myTokens.size();
	if ((unsigned)index >= mySize) {
		return "ERROR getType";
	}
	return myTokens.at(index).getType();
}
string Tokenizer::getTokenText(int index) {
	return myTokens.at(index).getText();
}