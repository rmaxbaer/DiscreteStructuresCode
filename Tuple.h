#ifndef TUPLE_H
#define TUPLE_H

#include "Predicate.h"

#include <vector>
#include <string>
#include <iostream>
#include<sstream>  


using namespace std;
class Tuple
{
private:
	vector<string> myStrings;

public:
	void setTuple(vector<string> factTuple);
	string toString();
	string getString(int myIndex);
	vector<string> getAllStrings();

	//LAB 4
	int numStrings();




	bool operator<(const Tuple& other) const {
		if (this->myStrings < other.myStrings) {
			return true;
		}
		else {
			return false;
		}

	}
};

#endif // !TUPLE_H
