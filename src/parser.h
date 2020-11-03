/* 
 * File:   parser.h
 * Author: Kenneth Bastian
 *
 */

#ifndef _PARSER_H
#define	_PARSER_H

//#include "interpreter.h"
#include "parser_stack.h"
#include "parser_declarations.h"
#include <stack>

using namespace std;

class Parser{
private:
	ifstream* sf;
	Scanner scan;
	SymbolTable table;
	Interpreter intr;
	typedef stack<ParserStack> stStack;
	stStack stack;	//stack variable
	int input_val;
	string getter, shift;

	string Action[NUM_OF_STATES][NUM_OF_TOKENS];
	int Goto[NUM_OF_STATES][NUM_OF_VARIABLES];
	Rules *rules;
	
	node *root, *ptr, *sptr;
	//node *last,*cptr, *root;
	ParserStack s;

	void declareActionTable();
	void declareGotoTable();
public:
	Parser(ifstream* s);
	~Parser();
	void parse();
};




#endif

