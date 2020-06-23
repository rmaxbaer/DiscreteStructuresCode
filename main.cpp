#include "Tokenizer.h"
#include "Token.h"
#include "Datalog.h"
#include "Interpreter.h"
#include "Database.h"

#include <iostream> 

using namespace std;
int main(int argc, char* argv[]) {
	string fileName = argv[1];
	//string fileName = "InputFile.txt";
	Tokenizer myTokenizer;
	myTokenizer.read(fileName);
	// START OF LAB 2
	Datalog myDatalog;
	myDatalog.startParse(myTokenizer);


	//LAB 3
	Database myDatabase;
	Interpreter myInterpreter;
	myInterpreter.loadDataBase(myDatalog, myDatabase);


	//cout << endl << "TESTING intersection:" << endl << endl;





}