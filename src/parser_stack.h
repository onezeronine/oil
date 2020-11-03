/* 
 * File:   parser_stack.h
 * Author: Kenneth Bastian
 *
 */

#include "syntax_tree.h"

struct ParserStack{
	int state;
	int token;
	node *stackNode;
};
