/*
 * File:   symbol_table.h
 * Author: Kenneth Bastian
 *
 */

#include "token.h"
#include "oil_lib.h"

using namespace std;


class SymbolTable{
private:
	//int should be of type Token...
	typedef map	<string,Token> iMap;
	iMap map;
	iMap::const_iterator itrLoc;
public:
	SymbolTable();
	~SymbolTable();
	void insertOnST(char *id, Token value);
	int getOnST(char *sChar);
	char* getKey(char *sChar);
	Token getToken(char *sChar);
	void setToken(string sChar, Token value);

};


