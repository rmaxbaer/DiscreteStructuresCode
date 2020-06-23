#include "Tuple.h"




void Tuple::setTuple(vector<string> factTuple) {
	myStrings = factTuple;
}

string Tuple::toString() {
	string outString = "";
	for (unsigned int i = 0; i < myStrings.size(); ++i) {
		outString = outString + myStrings.at(i);
	}
	return outString;
}


string Tuple::getString(int myIndex) {
	/*
	if (myIndex >= myStrings.size()) {
		cout << "Can't get that string at index " << myIndex << "; only have " << myStrings.size() << " elements" << endl;
		for (unsigned int brooke = 0; brooke < myStrings.size(); ++brooke) {
			cout << myStrings.at(brooke) << endl;
		}
		return " ";
	}
	*/

	return myStrings.at(myIndex);
}


// LAB 4

vector<string> Tuple::getAllStrings() {
	return myStrings;
}

int Tuple::numStrings() {
	return myStrings.size();
}