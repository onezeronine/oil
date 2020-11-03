/* 
 * File:   token.h
 * Author: Kenneth Bastian
 *
 */
#include <map>
#include <string>
#include <vector>

class Token{
public:
	//Token attributes
	std::string tokenName; //ID, RELOP, ADD etc.
	int tokenInt;			//35, 1, 0, etc.
	std::string type;		//int, float etc.
	std::string value;		//runtime values...
	Token();
	Token(std::string TokenName, int TokenNum, std::string type, std::string val);
private:
};
