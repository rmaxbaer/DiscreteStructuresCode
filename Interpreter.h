#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Datalog.h"
#include "Database.h"
#include "Predicate.h"
#include "Tuple.h"
#include "Relation.h"

#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <unordered_set>


using namespace std;
class Interpreter
{
public:
	void loadDataBase(Datalog datalog, Database database);
	void InterpretMe();

	void selectConst(string myConst, int myIndex);
	void selectVar(int index1, int index2);

	void ProjectMe();

	//LAB 4
	void ReadRules(vector<Rule> myRules);
	Relation joinBodyPreds(vector<Predicate> bodyPreds);
	Relation joinHelper(Relation baseRelation, Relation nextRelation);

	Relation ProjectRule(Predicate headPred, Relation myRelation);


	void RuleHelper(bool single);
	int getIndex(string target, vector<string> myVector);
	void PrintTuples();
	void PrintRules();

	void PrintSingleRule(int ruleIndex);
	void PrintSingleTuple(int ruleIndex);

private:
	Datalog myDatalog;
	Database myDatabase;

	vector<Predicate> mySchemes;
	vector<Predicate> myFacts;
	vector<Rule> myRules;
	vector<Predicate> myQueries;

	Header queryHead;
	vector<string> myAttributes;
	string currAttribute;

	// LAB 4
	int schemeCount = 0;
	//vector<string> schemeAttributes;
	vector<Header> vecHeaders;


	/*

	I think these have to be vectors of tuples; at the end, we can put them in
	a set, but for removing/keeping/inserting, it will work a lot better with vectors

	set<Tuple> myTuples;
	set<Tuple> tupleHolder;
	set<Tuple> tupleHolder2;
	*/
	set<Tuple> myTuples;
	set<Tuple> tupleHolder;
	set<Tuple> tupleHolder2;

	Relation currRelation;
	Tuple currTuple;
	//Tuple currBadTuple;
	map<string, int> myVariables;
	vector<string> myVars;

	Relation temp;

	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int n = 0;

};

#endif // !INTERPRETER_H
