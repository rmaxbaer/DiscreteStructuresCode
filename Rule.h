#ifndef RULE_H
#define RULE_H

#include "Predicate.h"

#include<iostream>
#include<string>
#include<vector>

using namespace std;
class Rule
{
private:
	Predicate headPred;
	vector<Predicate> bodyPreds;
public:
	Rule(Predicate head, vector<Predicate> body);
	string toString();

	//Lab 4
	int bodySize();
	Predicate getSingleBody();
	vector<Predicate> getBody();
	Predicate getHeadPred();
};


#endif // !RULE_H