#ifndef NODE_H
#define NODE_H

#include <set>
#include <iostream>

using namespace std;
class Node
{
private:
	int myID;
	set<int> myAdjList;
	bool beenMarked = false;
public:
	void setID(int thisID);
	void setAdjList(set<int> thisList);
	
	bool isMarked();
	void markTrue();
	void markFalse();

	set<int> getList();
	int getID();

};

#endif // !NODE_H
