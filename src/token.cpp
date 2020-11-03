/* 
 * File:   token.cpp
 * Author: Kenneth Bastian
 *
 */

//NOT USED... Feb 11, 2011

#include "token.h"

Token::Token(std::string TokenName, int TokenNum, std::string type, std::string val){
	this->tokenName = TokenName;
	this->tokenInt = TokenNum;
	this->type = type;
	this->value = val;
}
