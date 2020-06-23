#include "Header.h"



int Header::getSize() {
	return myAttributes.size();
}


void Header::loadAttributes(vector<string> attributes) {
	myAttributes = attributes;
}



void Header::printMe() {
	//cout << "Atributes: ";
	cout << "(";
	for (unsigned int i = 0; i < myAttributes.size(); ++i) {
		cout << myAttributes.at(i);
		if (i != myAttributes.size() - 1) {
			cout << ',';
		}
	}
	cout << ")";
}


vector<string> Header::getAttributes() {
	return myAttributes;
}