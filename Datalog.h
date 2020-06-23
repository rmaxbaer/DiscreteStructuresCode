#ifndef DATALOG_H
#define DATALOG_H 

#include "Tokenizer.h"
#include "Predicate.h"
#include "Rule.h"

#include <string>
#include<vector>
#include<set>

using namespace std;
class Datalog
{
private:
	int tIndex = 0;
	string currentID;
	vector<string> currentParams;
	bool checkingQs = false;
	//bool creatingBody = false;

	set<string> domainStrings;

	vector<Predicate> mySchemes;
	vector<Predicate> myFacts;
	vector<Rule> myRules;
	vector<Predicate> myQueries;

	Predicate ruleHead;
	vector<Predicate> ruleBody;

public:
	void startParse(Tokenizer& tokenVec);
	bool parseMe(Tokenizer& tokenVec);
	bool parseSchemes(Tokenizer& tokenVec);
	bool parseIDlist(Tokenizer& tokenVec);
	bool parseFacts(Tokenizer& tokenVec);
	bool parseStringList(Tokenizer& tokenVec);
	bool parseRuleHead(Tokenizer& tokenVec);
	bool parseRuleBody(Tokenizer& tokenVec);
	bool parseBodyList(Tokenizer& tokenVec);
	bool parseQueries(Tokenizer& tokenVec);
	bool parseQueryList(Tokenizer& tokenVec);

	void maxToString();

	//LAB 3
	vector<Predicate> getSchemes();
	vector<Predicate> getQueries();
	vector<Predicate> getFacts();

	//Lab 4
	vector<Rule> getRules();

};
#endif // DATALOG_H
