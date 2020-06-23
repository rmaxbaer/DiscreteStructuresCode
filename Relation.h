#ifndef RELATION_H
#define RELATION_H

#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

#include <string>
#include <vector>
#include <iostream>
#include <set>


using namespace std;
class Relation
{
public:
	void setNameHeader(string name, Header header);
	void addTuple(Tuple newTuple);
	int numTuples();
	set<Tuple> getTuples();
	//vector<Tuple> getTuples();
	void setTuples(set<Tuple> tuples);
	void PrintMe(vector<string> myAttributes);

	// LAB 4
	Header getHeader();
	string getName();
	void insertTuples(set<Tuple> addedTuples);
	void clearTuples();
	void LoadAdditonalTuples(set<Tuple> additonal_Tuples);
	set<Tuple> getDifference();


private:
	string myName = "";
	Header myHeader;
	set<Tuple> myTuples;

	// LAB 4
	set<Tuple> additionalTuples;


};

#endif // !RELATION_H
