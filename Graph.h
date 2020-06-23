#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Rule.h"

#include <vector>
#include <iostream>
#include <map>
#include <stack>
#include <set>


using namespace std;
class Graph
{
private:
	map<int, Node> myGraph;
	stack<int> postOrder;
	vector<int> realOrder;
	//stack<int> postOrder2;
	//vector<set<int>> v;

	int numNodes = 0;

	vector<set<int>> myForest;
	set<int> myTree;

public:
	void makeGraph(vector<Rule> myRules);
	void setPostOrder(stack<int> ReverseOrder);

	void findSCC();
	void runSCC(Node& currNode);
	
	vector<set<int>> getForest();
	void printDG();
	void printOrder();

};

#endif // !GRAPH_H
