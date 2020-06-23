#ifndef REVERSEGRAPH_H
#define REVERSEGRAPH_H

#include "Node.h"
#include "Rule.h"

#include <vector>
#include <iostream>
#include <map>
#include <stack>
#include <set>


using namespace std;
class ReverseGraph
{
private:
	map<int, Node> myReverseGraph;
	stack<int> reversePostOrder;
	//stack<int> postOrder2;
	//vector<set<int>> v;

	int numNodes = 0;


public:
	void makeReverseGraph(vector<Rule> myRules);
	
	void dfsForest();
	void runDFS(Node& currNode);

	stack<int> getReverseOrder();


	void printRDG();
	void printRPO();

};

#endif // !REVERSEGRAPH_H