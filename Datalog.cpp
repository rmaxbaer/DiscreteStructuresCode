#include "Datalog.h"
#include "Tokenizer.h"
#include "Predicate.h"

#include <string>
#include <iostream>
#include <cstdbool>
using namespace std;

void Datalog::startParse(Tokenizer& tokenVec) {
	if (parseMe(tokenVec)) {
		/* COMMENTED OUT FOR LAB 3; to get lab 2 output, this is all you need to change
		cout << "Success!" << endl;
		maxToString();
		cout << endl;
		*/
	}
	else {
		cout << "Failure!" << endl;
		cout << "  " << tokenVec.printMe(tIndex) << endl;
	}
}

bool Datalog::parseMe(Tokenizer& tokenVec) {
	if (tokenVec.getTokenType(tIndex) != "SCHEMES") return false;
	if (tokenVec.getTokenType(++tIndex) != "COLON") return false;
	return parseSchemes(tokenVec);
	//cout << "ERROR PARSE ME" << endl;
	return false;
}

bool Datalog::parseSchemes(Tokenizer& tokenVec) {
	//cout << "TESTING 1 at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	currentParams.clear();
	//cout << "TESTING 2 at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	if (tokenVec.getTokenType(++tIndex) != "ID") return false;
	currentID = tokenVec.getTokenText(tIndex);
	if (tokenVec.getTokenType(++tIndex) != "LEFT_PAREN") return false;
	if (parseIDlist(tokenVec) == false) return false;
	Predicate newPredicate(currentID, currentParams);
	mySchemes.push_back(newPredicate);

	if (tokenVec.getTokenType(tIndex + 1) == "ID") {
		return parseSchemes(tokenVec);
	}
	if (tokenVec.getTokenType(++tIndex) == "FACTS") {
		if (tokenVec.getTokenType(++tIndex) != "COLON") return false;
		return parseFacts(tokenVec);
	}
	//cout << "Falied Parse" << endl;
	return false; // this should be false; if this is reached it means that we never got to rules
}

bool Datalog::parseIDlist(Tokenizer& tokenVec) {
	//cout << "TESTING b at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	if (tokenVec.getTokenType(++tIndex) != "ID") return false;
	currentParams.push_back(tokenVec.getTokenText(tIndex));
	if (tokenVec.getTokenType(++tIndex) == "COMMA") {
		return parseIDlist(tokenVec);
	}
	if (tokenVec.getTokenType(tIndex) != "RIGHT_PAREN") {
		//cout << "parseIDlist error" << endl;
		return false;
	}
	//cout << "End ParseIDlist" << endl;
	return true;
}

bool Datalog::parseFacts(Tokenizer& tokenVec) {
	currentParams.clear();
	if (tokenVec.getTokenType(++tIndex) == "RULES") {
		if (tokenVec.getTokenType(tIndex + 1) != "COLON") {
			return false;
		}
		tIndex = tIndex + 1;
		return parseRuleHead(tokenVec);
	}
	if (tokenVec.getTokenType(tIndex) != "ID") return false;
	currentID = tokenVec.getTokenText(tIndex);
	if (tokenVec.getTokenType(++tIndex) != "LEFT_PAREN") return false;

	if (parseStringList(tokenVec) == false) return false;
	Predicate newPredicate(currentID, currentParams);
	myFacts.push_back(newPredicate);
	if (tokenVec.getTokenType(tIndex + 1) == "ID") {
		return parseFacts(tokenVec);
	}
	if (tokenVec.getTokenType(++tIndex) == "RULES") {
		if (tokenVec.getTokenType(++tIndex) != "COLON") return false;
		return parseRuleHead(tokenVec);
	}
	return false; // this should be false; if this is reached it means that we never got to rules
}

bool Datalog::parseStringList(Tokenizer& tokenVec) {
	//cout << "TESTING at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	if (tokenVec.getTokenType(++tIndex) != "STRING") return false;
	currentParams.push_back(tokenVec.getTokenText(tIndex));
	domainStrings.insert(tokenVec.getTokenText(tIndex));
	if (tokenVec.getTokenType(++tIndex) == "COMMA") {
		return parseStringList(tokenVec);
	}
	if ((tokenVec.getTokenType(tIndex) != "RIGHT_PAREN") || (tokenVec.getTokenType(++tIndex) != "PERIOD")) {
		//cout << "parseStringList error" << endl;
		return false;
	}

	//cout << "end ParseStringList" << endl;
	return true;
}


bool Datalog::parseRuleHead(Tokenizer& tokenVec) {
	ruleBody.clear();
	if (tokenVec.getTokenType(++tIndex) == "QUERIES") {
		if (tokenVec.getTokenType(tIndex + 1) != "COLON") {
			return false;
		}
		tIndex = tIndex + 1;
		if (parseQueries(tokenVec)) {
			//cout << "Faile 118" << endl;
			return true;
		}
		else {
			//cout << "Faile 122" << endl;
			return false;
		}
	}
	currentParams.clear();
	if (tokenVec.getTokenType(tIndex) != "ID") return false;
	currentID = tokenVec.getTokenText(tIndex);
	if (tokenVec.getTokenType(++tIndex) != "LEFT_PAREN") return false;
	if (parseIDlist(tokenVec) == false) return false;
	Predicate newPredicate(currentID, currentParams);
	ruleHead = newPredicate;

	if (tokenVec.getTokenType(++tIndex) != "COLON_DASH") return false;
	//cout << "TESTING before second " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	if (parseRuleBody(tokenVec) == false) {
		//cout << "TESTING before faile at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
		//cout << "Faile 1  " << endl;
		return false;
	}
	else {
		//cout << "Passed 133" << endl;
		//Rule newRule(ruleHead, ruleBody);
		//myRules.push_back(newRule);
		return true; // LEGAL???
	}

	if (tokenVec.getTokenType(tIndex + 1) != "ID") {
		if (parseRuleHead(tokenVec)) {
			//cout << "passed 137" << endl;
			return true;
		}
		else {
			//cout << "TESTING 141 at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
			//cout << "Fail 141" << endl;
			return false;
		}

		//return parseRuleHead(tokenVec);
	}

	return false; // FAALLLSSSEEEEEEE
}

bool Datalog::parseRuleBody(Tokenizer& tokenVec) {
	currentParams.clear();
	if (tokenVec.getTokenType(++tIndex) != "ID") return false;
	currentID = tokenVec.getTokenText(tIndex);
	if (tokenVec.getTokenType(++tIndex) != "LEFT_PAREN") return false;
	if (parseBodyList(tokenVec) == false) return false;
	Predicate newPredicate(currentID, currentParams);
	ruleBody.push_back(newPredicate);

	if (tokenVec.getTokenType(++tIndex) == "COMMA") {
		//cout << "TESTING before first at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
		return parseRuleBody(tokenVec);

	}
	Rule newRule(ruleHead, ruleBody);
	myRules.push_back(newRule);

	if (tokenVec.getTokenType(tIndex) == "PERIOD") {
		if (tokenVec.getTokenType(tIndex + 1) == "ID") {
			//cout << "TESTING me at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
			parseRuleHead(tokenVec);
			if (checkingQs == true) {
				return true;
			}

		}
		// This is where we've gone too far
		if (tokenVec.getTokenType(tIndex + 1) != "QUERIES") return false;
		tIndex = tIndex + 1;
		if (tokenVec.getTokenType(++tIndex) != "COLON") return false;


		//Rule newRule(ruleHead, ruleBody);
		//myRules.push_back(newRule);
		if (parseQueries(tokenVec)) {
			//cout << "returning True 159" << endl;
			return true;
		}
		else {
			//cout << "Faile 187" << endl;
			return false;
		}

	}
	//cout << "End Parse Body.." << endl;
	return false; // this should be false; if this is reached it means that we never got to rules
}

bool Datalog::parseBodyList(Tokenizer& tokenVec) {
	if (tokenVec.getTokenType(++tIndex) != "ID") {
		if (tokenVec.getTokenType(tIndex) != "STRING") {
			//cout << "Faile 190" << endl;
			return false;
		}
	}

	currentParams.push_back(tokenVec.getTokenText(tIndex));
	if (tokenVec.getTokenType(++tIndex) == "COMMA") {
		return parseBodyList(tokenVec);
	}
	if (tokenVec.getTokenType(tIndex) != "RIGHT_PAREN") {
		//cout << "parseBodyList error" << endl;
		return false;
	}

	//cout << "end ParseBodyList" << endl;
	return true;
}


bool Datalog::parseQueries(Tokenizer& tokenVec) {
	currentParams.clear();
	if (tokenVec.getTokenType(++tIndex) != "ID") return false;
	currentID = tokenVec.getTokenText(tIndex);
	if (tokenVec.getTokenType(++tIndex) != "LEFT_PAREN") return false;
	if (parseQueryList(tokenVec) == false) return false;
	Predicate newPredicate(currentID, currentParams);
	myQueries.push_back(newPredicate);

	if (tokenVec.getTokenType(tIndex + 1) == "ID") {
		return parseQueries(tokenVec);
	}
	//cout << "TESTING before EOF at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	if (tokenVec.getTokenType(++tIndex) != "EOF") {
		return false;
	}
	else {
		checkingQs = true;
		return true;
	}
	//cout << "FINAL" << endl;
	//cout << "End Parse Query.." << endl;
	//cout << "TESTING after EOF at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	//cout << "returning true pq" << endl;
	return true; // this should be false; if this is reached it means that we never got to rules
}

bool Datalog::parseQueryList(Tokenizer& tokenVec) {
	if (tokenVec.getTokenType(++tIndex) != "ID") {
		if (tokenVec.getTokenType(tIndex) != "STRING") {
			return false;
		}
	}

	currentParams.push_back(tokenVec.getTokenText(tIndex));
	if (tokenVec.getTokenType(++tIndex) == "COMMA") {
		return parseQueryList(tokenVec);
	}
	if (tokenVec.getTokenType(tIndex) != "RIGHT_PAREN") {
		//cout << "parseQueryList error 1" << endl;
		return false;
	}
	//cout << "TESTING before ? at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;
	if (tokenVec.getTokenType(++tIndex) != "Q_MARK") {
		//cout << "parseQueryList error 2" << endl;
		//checkingQs = true;
		return false;
	}
	//cout << "TESTING after ? at " << tIndex << ": " << tokenVec.getTokenType(tIndex) << endl;


	//cout << "end ParseQueryList" << endl;
	return true;
}

void Datalog::maxToString() {

	cout << "Schemes(" << mySchemes.size() << "):" << endl;
	for (unsigned int i = 0; i < mySchemes.size(); ++i) {
		cout << "  " << mySchemes.at(i).toString() << endl;
	}

	cout << "Facts(" << myFacts.size() << "):" << endl;
	for (unsigned int i = 0; i < myFacts.size(); ++i) {
		cout << "  " << myFacts.at(i).toString() << "." << endl;
	}
	cout << "Rules(" << myRules.size() << "):" << endl;
	for (unsigned int i = 0; i < myRules.size(); ++i) {
		cout << "  " << myRules.at(i).toString() << endl;
	}
	cout << "Queries(" << myQueries.size() << "):" << endl;
	for (unsigned int i = 0; i < myQueries.size(); ++i) {
		cout << "  " << myQueries.at(i).toString() << "?" << endl;
	}
	cout << "Domain(" << domainStrings.size() << "):";
	for (auto it = domainStrings.begin(); it != domainStrings.end(); it++) {
		cout << endl << "  " << *it;
	}

}




//LAB 3

vector<Predicate> Datalog::getSchemes() {
	return mySchemes;
}

vector<Predicate> Datalog::getFacts() {
	return myFacts;
}

vector<Predicate> Datalog::getQueries() {
	return myQueries;
}


//LAB 4
vector<Rule> Datalog::getRules() {
	return myRules;
}
