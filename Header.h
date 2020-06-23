#ifndef HEADER_H
#define HEADER_H


#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Header
{
public:
	int getSize();
	void loadAttributes(vector<string> attributes);
	void printMe();
	vector<string> getAttributes();
private:
	vector<string> myAttributes;
};

#endif // !HEADER_H
