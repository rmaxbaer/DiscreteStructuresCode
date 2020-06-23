#include "Predicate.h"

#include<sstream>

Predicate::Predicate(string name, vector<string> params) {
	predID = name;
	predParam = params;

	//cout << "Predicate added: " << name << endl;
	//cout << name << "(";
	for (unsigned int i = 0; i < params.size(); ++i) {
		//cout << params.at(i);
		if (i != params.size() - 1) {
			//cout << ",";
		}
	}
	//cout << ")" << endl << endl;


}

string Predicate::toString() {


	stringstream convert;
	convert << predID << "(";
	for (unsigned int i = 0; i < predParam.size(); ++i) {
		convert << predParam.at(i);
		if (i != predParam.size() - 1) {
			convert << ",";
		}
	}
	convert << ")";
	string output = convert.str();
	return output;



}



//LAB 2
string Predicate::getName() {
	return predID;
}

Header Predicate::getHeader() {
	Header myHeader;
	myHeader.loadAttributes(predParam);
	return myHeader;
}

vector<string> Predicate::getTuple() {
	return predParam;
}