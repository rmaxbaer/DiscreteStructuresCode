#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"

#include <string>
#include <fstream>
#include <vector>

using namespace std;
class Tokenizer
{
private:
	string text;
	int lineNum = 1;
	ifstream ifs;
	char currChar = ' ';
	int numTokens = 0;
	// LAB 2
	vector<Token> myTokens;

public:
	Tokenizer() {};
	void read(string fileName);
	void TokenizeMe();
	void newToken(tokenType type, int line);
	void stringToken();
	void idToken();
	void commentToken();
	//LAB 2
	string printMe(int index);
	string getTokenType(int index);
	string getTokenText(int index);


};

#endif // !TOKENIZER_H
