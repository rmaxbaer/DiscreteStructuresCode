#include "ReverseGraph.h"

#include <string>


void ReverseGraph::makeReverseGraph(vector<Rule> myRules) {
	numNodes = myRules.size();
	Node myNode;
	set<int> myDependencies;
	vector<Predicate> myBodyPreds;
	for (unsigned int i = 0; i < myRules.size(); ++i) {
		myDependencies.clear();
		Predicate thisHeadPred = myRules.at(i).getHeadPred();
		string myName = thisHeadPred.getName();
		for (unsigned int k = 0; k < myRules.size(); ++k) {
			myBodyPreds = myRules.at(k).getBody();
			for (unsigned int j = 0; j < myBodyPreds.size(); ++j) {
				string thisPredName = myBodyPreds.at(j).getName();
				if (thisPredName == myName) {
					myDependencies.insert(k);
				}
			}
		}
		myNode.setID(i);
		myNode.setAdjList(myDependencies);
		myReverseGraph.insert(pair<int, Node>(i, myNode));

	}



}



void ReverseGraph::dfsForest() {
	//cout << "Testing numNodes: " << numNodes << endl;
	for (unsigned int m = 0; m < myReverseGraph.size(); ++m) {
		Node currNode = myReverseGraph.at(m);
		if (currNode.isMarked() == false) {
			runDFS(myReverseGraph.at(m));
		}
	}
	//printRPO();

}

void ReverseGraph::runDFS(Node& currNode) {
	currNode.markTrue();
	set<int> currList = currNode.getList();
 	for (auto it = currList.begin(); it != currList.end(); ++it) {
		//Node thisNode = myReverseGraph.at(*it);
		int thisIndex = *it;
		if (myReverseGraph.at(thisIndex).isMarked() == false) {
			runDFS(myReverseGraph.at(thisIndex));
		}
	}
	reversePostOrder.push(currNode.getID());
}

stack<int> ReverseGraph::getReverseOrder() {
	return reversePostOrder;
}







void ReverseGraph::printRDG() {
	Node tempNode;
	set<int> tempList;
	cout << "Reverse Dependency Graph" << endl;
	for (unsigned int n = 0; n < myReverseGraph.size(); ++n) {
		tempNode = myReverseGraph.at(n);
		cout << "R" << tempNode.getID() << ": ";
		tempList = tempNode.getList();
		for (auto myIR = tempList.begin(); myIR != tempList.end(); ++myIR) {
			int currInt = *myIR;
			cout << "R" << currInt << " ";
		}
		cout << endl;

	}
	cout << endl;
}

void ReverseGraph::printRPO() {
	stack<int> myCopy = reversePostOrder;
	cout << "Printing reversePostOder but in reverse.. regular post order" << endl;
	cout << "SIZE: " << myCopy.size() << " vs numNodes: " << numNodes << endl;
	while (myCopy.size() != 0) {
		cout << "R" << myCopy.top() << " ";
		myCopy.pop();
	}
	cout << endl;
}