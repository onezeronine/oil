/* 
 * File:   scanner.h
 * Author: Kenneth Bastian
 *
 */

#include "oil_lib.h"
#include "symbol_table.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Scanner{
private:
	ifstream* source;
	SymbolTable* table;
	char *lexemeBegin, *forward, *sChar, *ret;
	int iSpace;
	void AllocateMem();
	void AllocateChar();
	void PrintLog(string err);
	char* searchChar(char* find);
public:
	Scanner();
	Scanner(ifstream* s, SymbolTable* st);
	~Scanner();
	void FreeChar();
	char* scan();
	int lineNumber;
};