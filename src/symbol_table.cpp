/*
 * File:   symbol_table.cpp
 * Author: Kenneth Bastian
 *
 */

#include "symbol_table.h"

SymbolTable::SymbolTable(){
	//Token keys, values
	//map.insert(iMap::value_type("and", Token("AND",0,"LOGICAL_OP","")));
	map.insert(iMap::value_type("begin", Token("BEGIN",2,"BEGIN","")));
	map.insert(iMap::value_type("boo", Token("BOO",3,"DATA_TYPE","")));
	map.insert(iMap::value_type("chr", Token("CHR",4,"DATA_TYPE","")));
	//map.insert(iMap::value_type("const", Token("CONST",4,"CONST","")));
	//map.insert(iMap::value_type("define", Token("DEFINE",5,"DEFINE","")));
	//map.insert(iMap::value_type("else", Token("ELSE",6,"ELSE","")));
	map.insert(iMap::value_type("end", Token("END",11,"END","")));
	//map.insert(iMap::value_type("enddef", Token("ENDDEF",8,"ENDDEF","")));
	map.insert(iMap::value_type("flt", Token("FLT",14,"DATA_TYPE","")));
	map.insert(iMap::value_type("while", Token("WHILE",28,"WHILE","")));
	map.insert(iMap::value_type("if", Token("IF",18,"IF","")));
	map.insert(iMap::value_type("int", Token("INT",19,"DATA_TYPE","")));
	//map.insert(iMap::value_type("or", Token("OR",13,"LOGICAL_OP","")));
	//map.insert(iMap::value_type("return", Token("RETURN",14,"RETURN","")));
	map.insert(iMap::value_type("dbl", Token("DBL",6,"DATA_TYPE","")));
	
	map.insert(iMap::value_type(";", Token(";",8,"DELIM","")));

	map.insert(iMap::value_type(":=", Token(":=",1,"ASSIGN_OP","")));
	map.insert(iMap::value_type(">=", Token(">=",15,"RELATIONAL_OP","")));
	map.insert(iMap::value_type(">", Token(">",16,"RELATIONAL_OP","")));
	map.insert(iMap::value_type("<=", Token("<=",20,"RELATIONAL_OP","")));
	map.insert(iMap::value_type("<", Token("<",21,"RELATIONAL_OP","")));
	map.insert(iMap::value_type("==", Token("==",12,"RELATIONAL_OP","")));
	//map.insert(iMap::value_type("!=", Token("!=",23,"RELATIONAL_OP","")));
	//map.insert(iMap::value_type("!", Token("!",24,"LOGICAL_OP","")));

	map.insert(iMap::value_type("+", Token("+",0,"ADD","")));
	map.insert(iMap::value_type("-", Token("-",26,"SUBTRACT","")));
	map.insert(iMap::value_type("*", Token("*",22,"MULTIPLY","")));
	map.insert(iMap::value_type("/", Token("/",5,"DIVIDE","")));
	map.insert(iMap::value_type("^", Token("^",13,"EXPONENT","")));
	//map.insert(iMap::value_type(".", Token(".",30,"CONCATENATION","")));

	//map.insert(iMap::value_type(",", Token(",",31,"COMMA","")));
	map.insert(iMap::value_type("(", Token("(",24,"OPEN PAREN","")));
	map.insert(iMap::value_type(")", Token(")",25,"CLOSED PAREN","")));
	//map.insert(iMap::value_type(":", Token(":",34,"COLON","")));
}

SymbolTable::~SymbolTable(){}

int SymbolTable::getOnST(char *sChar){
	char* s = alloc(20);
	itrLoc = map.find(sChar);
	if(itrLoc != map.end()){
		int s = itrLoc->second.tokenInt;
		//copy(str.begin(),str.end(),s);
		return s;
	}
	return 0;
}

char* SymbolTable::getKey(char *sChar){
	//Note: is this a memory leak?
	char* s = alloc(20);
	itrLoc = map.find(sChar);
	if(itrLoc != map.end()){
		string str = itrLoc->first;
		copy(str.begin(),str.end(),s);
		return s;
	}
	return 0;
}



void SymbolTable::insertOnST(char *sChar, Token value){
	map.insert(iMap::value_type(sChar, value));
}

Token SymbolTable::getToken(char *sChar){
	itrLoc = map.find(sChar);
	if(itrLoc != map.end()){
		return itrLoc->second;
	}
}

void SymbolTable::setToken(string sChar, Token value){
	itrLoc = map.find(sChar);
	if(itrLoc != map.end() || itrLoc->second.type == "int" || itrLoc->second.type == "dbl" || itrLoc->second.type == "boo" || itrLoc->second.type == "flt" ){
		map.erase(itrLoc);
		map.insert(iMap::value_type(sChar, value));
	}
	else{
		cout<<"Error: Variable '"<<sChar<<"' not declared";
		exit(-1);
	}
}