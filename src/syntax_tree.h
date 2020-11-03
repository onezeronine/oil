/* 
 * File:   syntax_tree.h
 * Author: Kenneth Bastian
 *
 */
/* 
 * File:   syntax_tree.h
 * Author: Kenneth Bastian
 *
 */
#include <iostream>
#include <string>
#include <stack>
#include "scanner.h"

struct node{
	string key;
	node *sibling;
	node *child;
	string val;
};

class Interpreter{
private:
	SymbolTable *_Table;
	string value;
	stack<string> _postfix;
public:
	bool is_number(const std::string& s);
	void setST(SymbolTable *st);
	void preorder(node *p);
	void interpret(node *root);	
	void intr_expr(node *exp);
	void intr_decl(node *decl);
};

