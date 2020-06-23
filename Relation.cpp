#include "Relation.h"



void Relation::setNameHeader(string name, Header header) {
	myName = name;
	myHeader = header;
	//cout << endl << "SETNAME HEADER" << endl;
}

void Relation::addTuple(Tuple newTuple) {
	myTuples.insert(newTuple);
}

int Relation::numTuples() {
	return myTuples.size();
}

set<Tuple> Relation::getTuples() {
	return myTuples;
}

/*
vector<Tuple> Relation::getTuples() {
	vector<Tuple> tupleVec;
	for (auto it = myTuples.begin(); it != myTuples.end(); ++it) {
		tupleVec.push_back(*it);
	}
	return tupleVec;
}
*/


void Relation::setTuples(set<Tuple> tuples) {
	myTuples = tuples;
}

void Relation::PrintMe(vector<string> myAttributes) {
	cout << myName << "(";
	//myHeader.printMe();
	for (unsigned int i = 0; i < myAttributes.size(); ++i) {
		cout << myAttributes.at(i);
		if (i != myAttributes.size() - 1) {
			cout << ",";
		}
	}
	cout << ")? ";
	if (myTuples.size() != 0) {
		cout << "Yes(" << myTuples.size() << ")" << endl;
	}
	else {
		cout << "No" << endl;
	}
	/*
	Tuple currTuple;
	for (auto it = myTuples.begin(); it != myTuples.end(); ++it) {
		currTuple = *it;
		cout << currTuple.toString() << endl;
	}
	*/
}

// LAB 4

Header Relation::getHeader() {
	return myHeader;
}

string Relation::getName() {
	return myName;
}

void Relation::insertTuples(set<Tuple> addedTuples) {
	for (auto itr = addedTuples.begin(); itr != addedTuples.end(); ++itr) {
		Tuple addedTuple = *itr;
		myTuples.insert(addedTuple);
	}
}

void Relation::clearTuples() {
	myTuples.clear();
}

void Relation::LoadAdditonalTuples(set<Tuple> additonal_Tuples) {
	additionalTuples = additonal_Tuples;
}

set<Tuple> Relation::getDifference() {
	set<Tuple> difference;
	for (auto myItr = additionalTuples.begin(); myItr != additionalTuples.end(); ++myItr) {
		Tuple newAddition = *myItr;
		int startNum = myTuples.size();
		myTuples.insert(newAddition);
		int endNum = myTuples.size();
		if (startNum != endNum) {
			difference.insert(newAddition);
		}
	}
	additionalTuples.clear();
	return difference;
}