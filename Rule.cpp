#include "Rule.h"

#include<sstream>

Rule::Rule(Predicate head, vector<Predicate> body) {
	headPred = head;
	bodyPreds = body;

}

string Rule::toString() {
	stringstream convert;
	convert << headPred.toString() << " :- ";
	for (unsigned int i = 0; i < bodyPreds.size(); ++i) {
		convert << bodyPreds.at(i).toString();
		if (i != bodyPreds.size() - 1) {
			convert << ",";
		}
	}
	convert << ".";
	string output = convert.str();
	return output;
}

// LAB 4

int Rule::bodySize() {
	return bodyPreds.size();
}

Predicate Rule::getSingleBody() {
	return bodyPreds.at(0);
}

vector<Predicate> Rule::getBody() {
	return bodyPreds;
}


Predicate Rule::getHeadPred() {
	return headPred;
}