#include "Graph.h"

#include "Predicate.h"

#include <string>

void Graph::makeGraph(vector<Rule> myRules) {
	numNodes = myRules.size();
	vector<Predicate> myBodyPreds;
	set<int> myDependencies;
	Node myNode;
	for (unsigned int i = 0; i < myRules.size(); ++i) {
		myDependencies.clear();
		myBodyPreds = myRules.at(i).getBody();
		for (unsigned int k = 0; k < myBodyPreds.size(); ++k) {
			string myPredName = myBodyPreds.at(k).getName();
			for (unsigned int j = 0; j < myRules.size(); ++j) {
				Predicate myHeadPred = myRules.at(j).getHeadPred();
				string myRuleName = myHeadPred.getName();
				if (myPredName == myRuleName) {
					myDependencies.insert(j);
				}
			}
		}
		myNode.setID(i);
		myNode.setAdjList(myDependencies);
		myGraph.insert(pair<int, Node>(i, myNode));
	}

}

void Graph::setPostOrder(stack<int> ReverseOrder) {
	stack<int> reverse = ReverseOrder;
	int holder;
		
	/*
	*/
	while (reverse.size() != 0) {
		holder = reverse.top();
		postOrder.push(holder); // this loads a stack that will pop off the postorder in the correct order
		realOrder.push_back(holder); // this vector stores postOrder from left to right
		reverse.pop();
	}
}

void Graph::findSCC() {
	for (unsigned int o = 0; o < myGraph.size(); ++o) {
		myGraph.at(o).markFalse();
	}
	myForest.clear();
	Node currNode;
	for (unsigned int o = 0; o < realOrder.size(); ++o) {
		myTree.clear();
		currNode = myGraph.at(realOrder.at(o));
		if (currNode.isMarked() == false) {
			runSCC(myGraph.at(realOrder.at(o)));
		}
		if (myTree.size() != 0) {
			myForest.push_back(myTree); // for three, it pushes back an empty tree; shouldn't it push back 3?
		}
	}
}

void Graph::runSCC(Node& currNode) {
	currNode.markTrue();
	int thisID;
	set<int> currList = currNode.getList(); // this is the adjacency list; ie {R0, R2, R5}
	for (auto itr = currList.begin(); itr != currList.end(); ++itr) {
		thisID = *itr; // this will be an item from our adjacenyList; from our example above, it will go through {0, 2, 5}
		if (myGraph.at(thisID).isMarked() == false) {
			runSCC(myGraph.at(thisID));
		}
		//myTree.insert(thisID);

	}
	myTree.insert(currNode.getID());
}

vector<set<int>> Graph::getForest() {
	return myForest;
}

void Graph::printOrder() {
	cout << "Printing real order... " << endl;
	for (unsigned int tom = 0; tom < realOrder.size(); ++tom) {
		cout << "R" << realOrder.at(tom) << " ";
	}
	cout << endl;
}









void Graph::printDG() {
	Node tempNode;
	set<int> tempList;
	cout << "Dependency Graph" << endl;
	for (unsigned int n = 0; n < myGraph.size(); ++n) {
		tempNode = myGraph.at(n);
		cout << "R" << tempNode.getID() << ":";
		tempList = tempNode.getList();
		vector<int> tempInts;
		tempInts.clear();
		for (auto myIR = tempList.begin(); myIR != tempList.end(); ++myIR) {
			int currInt = *myIR;
			//cout << "R" << currInt;
			tempInts.push_back(currInt);
		}
		for (unsigned int p = 0; p < tempInts.size(); ++p) {
			cout << "R" << tempInts.at(p);
			if (p != (tempInts.size() - 1)) {
				cout << ",";
			}
		}
		cout << endl;

	}
	cout << endl;
}
