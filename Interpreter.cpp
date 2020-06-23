#include "Interpreter.h"
#include "Graph.h"
#include "ReverseGraph.h"


void Interpreter::loadDataBase(Datalog datalog, Database database) {
	myDatabase = database;
	myDatalog = datalog;

	mySchemes = myDatalog.getSchemes();
	myFacts = myDatalog.getFacts();
	myQueries = myDatalog.getQueries();
	myRules = myDatalog.getRules();
	//cout << "numRules: " << myRules.size() << endl;

	//cout << " loaded Database" << endl;
	//cout << mySchemes.size() << ": schemes" << endl;
	//cout << myFacts.size() << ": facts" << endl;
	//cout << myQueries.size() << ": queries" << endl;

	for (i = 0; i < mySchemes.size(); ++i) {
		//cout << mySchemes.at(i).toString() << endl;
		//Header newHeader = mySchemes.at(i).getHeader();
		//cout << "loading " << mySchemes.at(i).getName() << endl;
		//newHeader.printMe();
		currRelation.setNameHeader(mySchemes.at(i).getName(), mySchemes.at(i).getHeader());
		myDatabase.insert(pair<string, Relation>(mySchemes.at(i).getName(), currRelation));
	}
	//cout << myDatabase.size() << " elements in myDatabase" << endl;

	for (i = 0; i < myFacts.size(); ++i) {
		currTuple.setTuple(myFacts.at(i).getTuple());
		myDatabase.at(myFacts.at(i).getName()).addTuple(currTuple);
	}
	//cout << myDatabase.size() << endl;
	//cout << myDatabase.at(mySchemes.at(0).getName()).numTuples() << endl;

	/// LAB 5
	Graph myGraph;
	ReverseGraph myReverseGraph;
	myGraph.makeGraph(myRules);
	myReverseGraph.makeReverseGraph(myRules);
	myReverseGraph.dfsForest();
	myGraph.setPostOrder(myReverseGraph.getReverseOrder());
	myGraph.findSCC();

	// This prints the forest structure
	vector<set<int>> thisForest = myGraph.getForest();
	/*
	cout << "START:" << endl << endl;
	for (unsigned int r = 0; r < thisForest.size(); ++r) {
		cout << "Printing Tree: " << r << endl;
		set<int> mySet = thisForest.at(r);
		for (auto itr12 = mySet.begin(); itr12 != mySet.end(); ++itr12) {
			int currInt = *itr12;
			cout << currInt << " ";
		}
		cout << endl << endl;
	}
	*/
		
		
	myGraph.printDG();
	//myReverseGraph.printRDG();
	//myReverseGraph.printRPO();
	//myGraph.printOrder();









	//cout << "fin" << endl;
	//Lab 4
	cout << "Rule Evaluation" << endl;
	//Lab 5
	vector<Rule> oldRules;
	oldRules = myRules;
	for (unsigned int q = 0; q < thisForest.size(); ++q) { // for every tree...
		schemeCount = 0;
		set<int> mySet;
		mySet = thisForest.at(q);
		vector<Rule> currentRules;
		vector<int> myTree;
		myTree.clear();
		currentRules.clear();
		for (auto ruleITR = mySet.begin(); ruleITR != mySet.end(); ++ruleITR) { // go through every rule
			int ruleIndex = *ruleITR;
			currentRules.push_back(oldRules.at(ruleIndex));
			myTree.push_back(ruleIndex);
		}
		cout << "SCC: ";
		for (unsigned int r = 0; r < myTree.size(); ++r) {
			cout << "R" << myTree.at(r);
			if (r != (myTree.size() - 1)) {
				cout << ",";
			}
		}
		cout << endl;
		myRules = currentRules;
		
		
		
		bool singleSCC = false;
		if(myRules.size() == 1){
			singleSCC = true;
			vector<Predicate> myBodyPreds = myRules.at(0).getBody();
			Predicate myHead = myRules.at(0).getHeadPred();
			string ruleName = myHead.getName();
			for (unsigned int s = 0; s < myBodyPreds.size(); ++s) {
				string bodyName = myBodyPreds.at(s).getName();
				if (bodyName == ruleName) {
					singleSCC = false;
				}
			}
		}
		
		
		
		RuleHelper(singleSCC);


		for (unsigned int r = 0; r < myTree.size(); ++r) {
			cout << "R" << myTree.at(r);
			if (r != (myTree.size() - 1)) {
				cout << ",";
			}
		}
		cout << endl;

		// If an SCC contains only one rule and that rule does not depend on itself, the rule is evaluated only once.
	}
	cout << endl << "Query Evaluation" << endl;
	InterpretMe();







	//RuleHelper();
	//ReadRules(myRules);


}

void Interpreter::InterpretMe() {
	for (i = 0; i < myQueries.size(); ++i) {
		//cout << myQueries.at(i).toString() << endl;
		temp = myDatabase.at(myQueries.at(i).getName());
		queryHead = myQueries.at(i).getHeader();
		myAttributes = queryHead.getAttributes();
		//tupleHolder.clear();
		myTuples.clear();
		myTuples = temp.getTuples();
		//badTuples = myTuples;
		myVariables.clear();

		string currParam = "";
		for (j = 0; j < myAttributes.size(); ++j) {
			currParam = myAttributes.at(j);
			if (currParam.at(0) == '\'') {
				//cout << currParam << " is a string" << endl;
				selectConst(currParam, j);

			}
			else {
				//cout << "Ham!" << endl;
				//selectConst(currParam, j);
				//cout << currParam << " is a constant" << endl;
				//myDatabase.insert(pair<string, Relation>(mySchemes.at(i).getName(), currRelation));
				myVariables.insert(pair<string, int>(currParam, j));
				for (k = (j + 1); k < myAttributes.size(); ++k) {
					if (myAttributes.at(j) == myAttributes.at(k)) {
						selectVar(j, k);
					}
				}


			}
		}
		temp.setTuples(myTuples);
		temp.PrintMe(myAttributes);

		ProjectMe();


	}


}

void Interpreter::selectConst(string myConst, int myIndex) {
	// note the lack of ++it iterator at the end of this statement
	for (auto it = myTuples.begin(); it != myTuples.end(); ) {
		currTuple = *it;
		if (currTuple.getString(myIndex) != myConst) {
			//cout << "erasing: " << currTuple.toString() << endl;
			it = myTuples.erase(it);
		}
		else {
			++it;
		}
	}
	/*
	cout << "Remaining tuples: " << endl;
	for (auto it = myTuples.begin(); it != myTuples.end(); ++it) {
		currTuple = *it;
		cout << currTuple.toString() << endl;
		}
	*/




}

void Interpreter::selectVar(int index1, int index2) {
	// note the lack of ++it iterator at the end of this statement
	for (auto it = myTuples.begin(); it != myTuples.end(); ) {
		currTuple = *it;
		if (currTuple.getString(index1) != currTuple.getString(index2)) {
			//cout << "erasing via var: " << currTuple.toString() << endl;
			it = myTuples.erase(it);
		}
		else {
			++it;
		}
	}
}


void Interpreter::ProjectMe() {

	myVars.clear();
	for (unsigned int m = 0; m < myAttributes.size(); ++m) {
		currAttribute = myAttributes.at(m);
		if (currAttribute.at(0) != '\'') {
			if (find(myVars.begin(), myVars.end(), currAttribute) != myVars.end()) {
			}
			else {
				myVars.push_back(currAttribute);
			}
		}
	}



	for (auto it = myTuples.begin(); it != myTuples.end(); ++it) {
		Tuple thisTuple = *it;
		if (myVars.size() != 0) {
			cout << "  ";
		}
		for (unsigned int n = 0; n < myVars.size(); ++n) {
			cout << myAttributes.at(myVariables.at(myVars.at(n))) << "=" << thisTuple.getString(myVariables.at(myVars.at(n)));
			if (n != (myVars.size() - 1)) {
				cout << ", ";
			}
		}
		if (myVars.size() != 0) {
			cout << endl;
		}
	}

}

// Lab 4

void Interpreter::ReadRules(vector<Rule> myRules) {
	Relation bodyRelation;
	//bool finishedUp = true;
	for (i = 0; i < myRules.size(); ++i) {
		/*
		if (i > 0) {
			for (unsigned int back = (i - 1); back < i; ++back) {
				Predicate pastPredicate = myRules.at(back).getHeadPred();
				Predicate currentHead = myRules.at(i).getHeadPred();
				if (pastPredicate.getName() == currentHead.getName()) {
					myDatabase.at(pastPredicate.getName()).clearTuples();
				}
			}

		}
		int targ = 4;
		*/

		Rule tempRule = myRules.at(i);
		if (tempRule.bodySize() == 1) {
			Predicate lonePred = tempRule.getSingleBody();
			bodyRelation = myDatabase.at(lonePred.getName());
			bodyRelation.setNameHeader(lonePred.getName(), lonePred.getHeader());
		}
		else { // if there are multiple body predicates
			bodyRelation = joinBodyPreds(tempRule.getBody());
		}




		// after you've joined the body predicate relations...
		// these steps gives us the header of the rule's head predicate, the name of our relation
		// we keep track of these headers (the original scheme ones) because that's what we use to print
		Predicate headPredicate = tempRule.getHeadPred();
		Relation originalRelation = myDatabase.at(headPredicate.getName());


		Relation schemeRelation = myDatabase.at(headPredicate.getName());
		Header schemeHeader = schemeRelation.getHeader();
		vecHeaders.push_back(schemeHeader);
		//schemeAttributes = schemeHeader.getAttributes();
		/*
		cout << "Scheme pred: ";
		for (unsigned int Max = 0; Max < schemeAtts.size(); ++Max) {
			cout << " " << schemeAtts.at(Max) << endl;
		}
		*/


		//cout << "Head Pred: " << headPredicate.getName() << endl;
		Relation newRelation = ProjectRule(headPredicate, bodyRelation);
		//cout << "Pause";



		//myDatabase.at(headPredicate.getName()) = newRelation;
		/*
		cout << "TESTING SIZE:" << endl;
		cout << "Original: " << myDatabase.at(headPredicate.getName()).numTuples() << endl;
		cout << "Being added: " << newRelation.numTuples() << endl;
		*/



		//myDatabase.at(headPredicate.getName()).insertTuples(newRelation.getTuples()); // this is the union part
		myDatabase.at(headPredicate.getName()).LoadAdditonalTuples(newRelation.getTuples());
		PrintSingleTuple(i);



		/*
		Relation testRelation = myDatabase.at(headPredicate.getName());
		set<Tuple> testTuples = newRelation.getTuples();
		for (auto itr1 = testTuples.begin(); itr1 != testTuples.end(); ++itr1) {
			Tuple testTuple = *itr1;
			//cout << "Final Tuple Size: " << testTuple.numStrings() << endl;
		}
		*/

		//Relation existingRelation = myDatabase.at(headPredicate.getName());
		//int newSize = existingRelation.numTuples();
	}
}

Relation Interpreter::joinBodyPreds(vector<Predicate> bodyPreds) {
	Relation endRelation;
	Relation newRelation;
	vector<Relation> bodyRelations;
	bodyRelations.clear();
	for (j = 0; j < bodyPreds.size(); ++j) { // for all of the predicates, pull in the matching relation
		//cout << bodyPreds.at(j).getName() << endl;
		newRelation = myDatabase.at(bodyPreds.at(j).getName());
		newRelation.setNameHeader(bodyPreds.at(j).getName(), bodyPreds.at(j).getHeader());
		bodyRelations.push_back(newRelation);
	}
	//cout << "body Relations: " << bodyRelations.size() << endl;
	endRelation = bodyRelations.at(0);
	for (j = 1; j < bodyRelations.size(); ++j) {
		endRelation = joinHelper(endRelation, bodyRelations.at(j));
	}

	return endRelation;
}

Relation Interpreter::joinHelper(Relation baseRelation, Relation nextRelation) {
	Relation myRelation;
	Header myHeader;
	Header baseHeader = baseRelation.getHeader();
	Header nextHeader = nextRelation.getHeader();
	vector<string> baseAttributes = baseHeader.getAttributes();
	for (unsigned int q = 0; q < baseAttributes.size(); ++q) {
		//cout << "Base Attributes: " << baseAttributes.at(q) << endl;
	}
	vector<string> nextAttributes = nextHeader.getAttributes();
	set<Tuple> baseTuples = baseRelation.getTuples();
	set<Tuple> nextTuples = nextRelation.getTuples();
	set<Tuple> newTuples;
	vector<string> newTupleVec;
	Tuple tempTuple;
	Tuple joinedTuple;
	vector<string> commonVars;
	bool equalHeader;
	bool common;
	bool validTuple;
	unsigned int z = baseHeader.getSize();

	commonVars.clear();
	newTuples.clear();
	// we probably don't need these since they are local to this function

	if (baseHeader.getSize() == nextHeader.getSize()) {
		equalHeader = true;
		for (k = 0; k < z; ++k) {
			if (baseAttributes.at(k) != nextAttributes.at(k)) {
				equalHeader = false;
			}
		}
		if (equalHeader == true) { // if they have the same header...
			for (auto it1 = baseTuples.begin(); it1 != baseTuples.end(); ++it1) {
				Tuple baseTuple = *it1;
				vector<string> baseStrings = baseTuple.getAllStrings();
				common = false;
				for (auto it2 = nextTuples.begin(); it2 != nextTuples.end(); ++it2) {
					Tuple nextTuple = *it2;
					vector<string> nextStrings = nextTuple.getAllStrings();
					if (baseStrings == nextStrings) {
						common = true;
					}
				}
				if (common == true) {
					newTuples.insert(baseTuple);
				}
			}
			myRelation.setTuples(newTuples);
			myRelation.setNameHeader(baseRelation.getName(), baseHeader);
			return myRelation;
		}
	}
	for (k = 0; k < baseAttributes.size(); ++k) {
		for (n = 0; n < nextAttributes.size(); ++n) {
			if (baseAttributes.at(k) == nextAttributes.at(n)) {
				commonVars.push_back(baseAttributes.at(k));
			}
		}
	}
	myAttributes = baseAttributes;
	for (k = 0; k < nextAttributes.size(); ++k) {
		myAttributes.push_back(nextAttributes.at(k));
	}
	for (unsigned int fart = 0; fart < myAttributes.size(); ++fart) {
		//cout << "Testing 1 " << myAttributes.at(fart) << endl;
	}
	if ((commonVars.size() == 1) | (commonVars.size() == baseAttributes.size())) { // AND it equals nextAttributes.size() ??
		for (k = 0; k < commonVars.size(); ++k) {
			int myIndex = getIndex(commonVars.at(k), nextAttributes) + baseAttributes.size();
			//int myIndex = getIndex(commonVars.at(k), myAttributes);
			//cout << commonVars.at(k) << " will be erased from myAttributes: " << myAttributes.at(myIndex + 1) << endl;
			myAttributes.erase(myAttributes.begin() + myIndex);
		}
	}
	else {
		for (k = 0; k < commonVars.size(); ++k) {
			//int myIndex = getIndex(commonVars.at(k), nextAttributes) + baseAttributes.size();


			int myIndex = getIndex(commonVars.at(k), myAttributes);
			//int myIndex = getIndex(commonVars.at(k), nextAttributes) + baseAttributes.size();

			//cout << commonVars.at(k) << " will be erased from myAttributes: " << myAttributes.at(myIndex + 1) << endl;
			myAttributes.erase(myAttributes.begin() + myIndex);
		}
	}

	/*
	cout << "CommonVar 0: " << commonVars.at(0) << " of " << commonVars.size() << endl;
	for (unsigned int y = 0; y < myAttributes.size(); ++y) {
		cout << "TEST IT " << myAttributes.at(y) << endl;
	}
	*/
	myHeader.loadAttributes(myAttributes);
	for (unsigned int fart = 0; fart < myAttributes.size(); ++fart) {
		//cout << "Testing 2" << myAttributes.at(fart) << endl;
	}
	if (commonVars.size() == 0) {
		vector<string> joinedVec;
		for (auto it3 = baseTuples.begin(); it3 != baseTuples.end(); ++it3) {
			Tuple baseTuple = *it3;
			for (auto it4 = nextTuples.begin(); it4 != nextTuples.end(); ++it4) {
				Tuple nextTuple = *it4;
				joinedVec.clear();
				joinedVec = baseTuple.getAllStrings();
				vector<string> nextVec = nextTuple.getAllStrings();
				for (k = 0; k < nextVec.size(); ++k) {
					joinedVec.push_back(nextVec.at(k));
				}
				tempTuple.setTuple(joinedVec);
				newTuples.insert(tempTuple);
			}
		}
		myRelation.setTuples(newTuples);
		//myRelation.setNameHeader(baseRelation.getName(), baseHeader); // this baseheader only has one thing it should have the other guy
		myRelation.setNameHeader(baseRelation.getName(), myHeader);
		return myRelation;
	}
	else {
		for (auto it5 = baseTuples.begin(); it5 != baseTuples.end(); ++it5) {
			Tuple baseTuple = *it5;
			for (auto it6 = nextTuples.begin(); it6 != nextTuples.end(); ++it6) {
				Tuple nextTuple = *it6;
				validTuple = true;

				for (k = 0; k < commonVars.size(); ++k) {
					int baseIndex = getIndex(commonVars.at(k), baseAttributes);
					int nextIndex = getIndex(commonVars.at(k), nextAttributes);
					if (baseTuple.getString(baseIndex) != nextTuple.getString(nextIndex)) {
						validTuple = false;
					}
				}

				if (validTuple == true) {
					vector<string> otherAttributes = nextAttributes;
					for (k = 0; k < commonVars.size(); ++k) {
						int nextIndex = getIndex(commonVars.at(k), otherAttributes);
						/*
						for (unsigned int r = 0; r < otherAttributes.size(); ++r) {
							//cout << "Others 1: " << otherAttributes.at(r) << endl;
						}
						*/
						otherAttributes.erase(otherAttributes.begin() + nextIndex);
						/*
						for (unsigned int r = 0; r < otherAttributes.size(); ++r) {
							//cout << "Others 2: " << otherAttributes.at(r) << endl;
						}
						*/
						vector<string> vecStrings = nextTuple.getAllStrings();
						/*
						for (unsigned int r = 0; r < vecStrings.size(); ++r) {
							//cout << "tuple at " << r << ": " << vecStrings.at(r) << endl;
						}
						*/
						vecStrings.erase(vecStrings.begin() + nextIndex);
						/*
						for (unsigned int r = 0; r < vecStrings.size(); ++r) {
							//cout << "tuple at " << r << ": " << vecStrings.at(r) << endl;
						}
						*/
						nextTuple.setTuple(vecStrings);
					}
					vector<string> joinedVec = baseTuple.getAllStrings();
					vector<string> nextVec = nextTuple.getAllStrings();
					for (k = 0; k < nextVec.size(); ++k) {
						//cout << "Inserting: " << nextVec.at(k) << endl;
						joinedVec.push_back(nextVec.at(k));
					}
					tempTuple.setTuple(joinedVec);
					newTuples.insert(tempTuple);
					/*
					cout << "Tuple added: ";
					for (k = 0; k < joinedVec.size(); ++k) {
						cout << joinedVec.at(k) << " ";
					}
					cout << endl;
					*/


				}

			}
		}
		myRelation.setTuples(newTuples);
		myRelation.setNameHeader(baseRelation.getName(), myHeader);
	}
	return myRelation;
}

Relation Interpreter::ProjectRule(Predicate headPred, Relation myRelation) {
	Header headHeader = headPred.getHeader();
	vector<string> headAttributes = headHeader.getAttributes();
	set<Tuple> bodyTuples = myRelation.getTuples();
	Header bodyHeader = myRelation.getHeader();
	Relation headRelation = myDatabase.at(headPred.getName());
	vector<string> bodyAttributes = bodyHeader.getAttributes();
	set<Tuple> newTuples;
	vector<string> projectedVec;

	Tuple projectedTuple;

	for (unsigned int p = 0; p < headAttributes.size(); ++p) {
		//cout << " HEAD Attributes: " << headAttributes.at(p) << endl;
	}
	for (unsigned int p = 0; p < bodyAttributes.size(); ++p) {
		//cout << " BODY Attributes: " << bodyAttributes.at(p) << endl;
	}


	for (unsigned int mom = 0; mom < bodyAttributes.size(); ++mom) {
		string currString = bodyAttributes.at(mom);
		if (currString.at(0) == '\'') {
			for (auto bat = bodyTuples.begin(); bat != bodyTuples.end(); ) {
				Tuple batTuple = *bat;
				if (batTuple.getString(mom) != currString) {
					//cout << "erasing: " << currTuple.toString() << endl;
					bat = bodyTuples.erase(bat);
				}
				else {
					++bat;
				}
			}
		}
	}
	//cout << "TESTING: " << endl;






	for (auto it7 = bodyTuples.begin(); it7 != bodyTuples.end(); ++it7) {
		Tuple myTuple = *it7;
		projectedVec.clear();
		for (unsigned int p = 0; p < headAttributes.size(); ++p) {
			/*
			cout << "projecting column: " << headAttributes.at(p) << endl;
			for (unsigned int s = 0; s < bodyAttributes.size(); ++s) {
				//cout << "body: " << bodyAttributes.at(s) << endl;
			}
			*/
			int myColumn = getIndex(headAttributes.at(p), bodyAttributes);
			//vector<string> printThis = myTuple.getAllStrings();
			//for (unsigned int s = 0; s < printThis.size(); ++s) {
				//cout << "tuple at: " << s << " is: " << printThis.at(s) << endl;
			//}
			//cout << "Inserting: " << myTuple.getString(myColumn) << endl;
			projectedVec.push_back(myTuple.getString(myColumn));
		}
		projectedTuple.setTuple(projectedVec);
		//cout << newTuples.size();
		newTuples.insert(projectedTuple);
	}
	//int startingSize = headRelation.numTuples();
	for (auto it8 = newTuples.begin(); it8 != newTuples.end(); ++it8) {
		Tuple myTuple = *it8;
		headRelation.addTuple(myTuple);
		//cout << " adding Tuple of size: " << myTuple.numStrings() << endl;
	}





	return headRelation;

	/*
	int endSize = headRelation.numTuples();
	if (endSize == startingSize) {
		//we're done
	}
	else {
		// do it again
	}
	*/




}





// Helper
int Interpreter::getIndex(string target, vector<string> myVector) {
	unsigned int o = 0;
	for (o = 0; o < myVector.size(); ++o) {
		if (myVector.at(o) == target) {
			return o;
		}
	}
	cout << "getIndex Error: string not found" << endl;
	cout << "could not find: " << target << " in vector: " << endl;
	for (o = 0; o < myVector.size(); ++o) {
		//cout << myVector.at(o) << endl;
	}
	return 0;
}

void Interpreter::RuleHelper(bool single) {
	vector<int> mySizes;
	mySizes.clear();
	vector<int> myNewSizes;
	myNewSizes.clear();
	Relation thisRelation;
	Predicate thisPredicate;
	schemeCount++;
	for (unsigned int t = 0; t < myRules.size(); ++t) { // this loads a vector with the sizes of each Rule relation in the database
		thisPredicate = myRules.at(t).getHeadPred();
		thisRelation = myDatabase.at(thisPredicate.getName());
		mySizes.push_back(thisRelation.numTuples());
	}

	ReadRules(myRules);
	if (single == true) {
		PrintRules();
		return;
	}
	for (unsigned int t = 0; t < myRules.size(); ++t) { // this loads a vector with the NEW sizes of each Rule relation in the database
		thisPredicate = myRules.at(t).getHeadPred();
		thisRelation = myDatabase.at(thisPredicate.getName());
		myNewSizes.push_back(thisRelation.numTuples());
	}
	/*
	for (unsigned t = 0; t < myRules.size(); ++t) {
		if (mySizes.at(t) == myNewSizes.at(t)) {
			PrintRules(); // but only for the ones that are done
		}
		else {
			PrintTuples();
			RuleHelper();
		}
	}

	*/
	if (mySizes == myNewSizes) {

		//we're done; output the rules
		//Lab 5; do i need this thing below?
		PrintRules();
	
	}
	else {
		/*
		for (unsigned t = 0; t < myRules.size(); ++t) {
			if (mySizes.at(t) == myNewSizes.at(t)) {
				PrintSingleRule(t); // but only for the ones that are done
			}
			else {
				PrintSingleTuple(t);
			}
		}
		*/
		RuleHelper(false);







		/*

		//output all the Rule tuples; iterate counter
		//RuleHelper
		schemeCount++;
		PrintTuples();
		//mySizes.clear();
		//myNewSizes.clear();
		RuleHelper();
		*/
	}

}

void Interpreter::PrintTuples() {
	for (unsigned int u = 0; u < myRules.size(); ++u) {
		Rule printRule = myRules.at(u);
		Predicate printPred = printRule.getHeadPred();
		Relation printRelation = myDatabase.at(printPred.getName());
		Header printHeader = printPred.getHeader();
		vector<string> printAttributes = printHeader.getAttributes();
		//vector<string> printAttributes = schemeAttributes;
		set<Tuple> printTuples = printRelation.getTuples();
		vector<string> schemeAttributes = vecHeaders.at(u).getAttributes();

		//Relation schemeRelation = myDatabase.at()

		/*
		for (unsigned int v = 0; v < printAttributes.size(); ++v) {
			for_each(printAttributes.at(v).begin(), printAttributes.at(v).end(), [](char& c) {
				c = toupper(c);
				});
		}
		*/

		cout << printRule.toString() << endl;
		for (auto it9 = printTuples.begin(); it9 != printTuples.end(); ++it9) {
			Tuple printTuple = *it9;
			//cout << "This Tuple Size: " << printTuple.numStrings() << endl;
			cout << "  ";
			for (unsigned int v = 0; v < printAttributes.size(); ++v) {
				cout << schemeAttributes.at(v) << "=" << printTuple.getString(v);
				if (v != (printAttributes.size() - 1)) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		//clear relation if it occurs again; actually, we want to make a new relation
		/*
		if (u < (myRules.size() - 1)) { // as long as it's not the last one...
			Predicate currentHead = myRules.at(u).getHeadPred();
			for (unsigned int back = (u + 1); back < myRules.size(); ++back) {
				Predicate futurePred = myRules.at(back).getHeadPred();
				if (futurePred.getName() == currentHead.getName()) {
					myDatabase.at(currentHead.getName()).clearTuples();
				}
			}

		}
		*/




	}
}

void Interpreter::PrintRules() {
	/*
	for (unsigned int x = 0; x < myRules.size(); ++x) {
		cout << myRules.at(x).toString() << endl;
	}
	*/
	//cout << endl << "Schemes populated after " << schemeCount << " passes through the Rules." << endl << endl;
	//cout << "Query Evaluation" << endl;
	
	// Lab 5
	cout << schemeCount << " passes: ";
}


void Interpreter::PrintSingleRule(int ruleIndex) {
	cout << myRules.at(ruleIndex).toString() << endl;
}

void Interpreter::PrintSingleTuple(int ruleIndex) {
	Rule printRule = myRules.at(ruleIndex);
	Predicate printPred = printRule.getHeadPred();
	Relation printRelation = myDatabase.at(printPred.getName());
	Header printHeader = printPred.getHeader();
	vector<string> printAttributes = printHeader.getAttributes();
	//vector<string> printAttributes = schemeAttributes;
	vector<string> schemeAttributes = vecHeaders.at(ruleIndex).getAttributes();

	string ruleName = printRelation.getName();
	for (unsigned int count = 0; count < mySchemes.size(); ++count) {
		if (mySchemes.at(count).getName() == ruleName) {
			schemeAttributes = mySchemes.at(count).getTuple();
		}
	}
	cout << "";
	//set<Tuple> printTuples = printRelation.getTuples();
	set<Tuple> printTuples = printRelation.getDifference();
	//cout << "Tuple size: " << printTuples.size() << endl;




	//Relation schemeRelation = myDatabase.at()

	/*
	for (unsigned int v = 0; v < printAttributes.size(); ++v) {
		for_each(printAttributes.at(v).begin(), printAttributes.at(v).end(), [](char& c) {
			c = toupper(c);
			});
	}
	*/

	cout << printRule.toString() << endl;
	for (auto it9 = printTuples.begin(); it9 != printTuples.end(); ++it9) {
		Tuple printTuple = *it9;
		//cout << "This Tuple Size: " << printTuple.numStrings() << endl;
		cout << "  ";
		for (unsigned int v = 0; v < printAttributes.size(); ++v) {
			cout << schemeAttributes.at(v) << "=" << printTuple.getString(v);
			if (v != (printAttributes.size() - 1)) {
				cout << ", ";
			}
		}
		cout << endl;
	}


	myDatabase.at(printPred.getName()).insertTuples(printTuples);
	//int star = 3;
	/*
	if (ruleIndex < (myRules.size() - 1)) { // as long as it's not the last one...
		Predicate currentHead = myRules.at(ruleIndex).getHeadPred();
		for (unsigned int back = (ruleIndex + 1); back < myRules.size(); ++back) {
			Predicate futurePred = myRules.at(back).getHeadPred();
			if (futurePred.getName() == currentHead.getName()) {
				myDatabase.at(currentHead.getName()).clearTuples();
			}
		}

	}
	*/
}