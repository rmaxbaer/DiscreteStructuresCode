#ifndef PREDICATE_H
#define PREDICATE_H

#include "Header.h"


#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Predicate
{
private:
	string predID = "";
	vector<string> predParam;
public:
	Predicate() {}
	Predicate(string name, vector<string> params);
	string toString();


	//LAB 3
	string getName();
	Header getHeader();
	vector<string> getTuple();







};

#endif // !PREDICATE_H
