#include "Node.h"


void Node::setID(int thisID) {
	myID = thisID;
}

void Node::setAdjList(set<int> thisList) {
	myAdjList = thisList;
}

bool Node::isMarked() {
	return beenMarked;
}

void Node::markTrue() {
	beenMarked = true;
}

void Node::markFalse() {
	beenMarked = false;
}

set<int> Node::getList() {
	return myAdjList;
}

int Node::getID() {
	return myID;
}