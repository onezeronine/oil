/* 
 * File:   scanner.cpp
 * Author: Kenneth Bastian
 *
 */
#include "scanner.h"

Scanner::Scanner(){}

Scanner::Scanner(ifstream* s, SymbolTable *st){
	table = st;
	source = s;
	lineNumber = 1;
	AllocateMem();
	std::cout<<"Scanning..."<<endl<<endl;
}

Scanner::~Scanner(){}

char* Scanner::scan(){
	char* cCh;
	int decPt, iCh;
	AllocateChar();
	while(source->good()){
		bool ind = true;
		source->read(lexemeBegin,1);
		iSpace = (int)*lexemeBegin;
		if(iSpace == 10)
			lineNumber ++;
		//[FIXED] - Last character duplication - January 9, 2012
		if(source->good()){
			if(!isspace(iSpace)){
				switch(*lexemeBegin){
				
				//BLOCK COMMENT AND DIVISION SYMBOL
				case '/':
					*forward = source->peek();
					if(*forward == '*'){
						while(ind){
							source->read(lexemeBegin,1);
							if(*lexemeBegin == '*'){
								*forward = source->peek();
								if(*forward == '/')
									ind = false;
							}
						}
						source->read(lexemeBegin,1);
					}
					else{
						cCh = this->searchChar(lexemeBegin);
						return cCh;
					}
				break;
			
				//INLINE COMMENT
				case '#':
					while(ind){
						source->read(lexemeBegin,1);
						if(*lexemeBegin == '\n')
							ind = false;
					}
					break;

				//ADD OPERATOR
				case '+':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;
				//MINUS OPERATOR
				/*Disambiguated for negative symbol and minus symbol*/
				case '-':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;
				//MULTIPLY SYMBOL
				case '*':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;
				//EXP SYMBOL
				case '^':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;
				//OPEN AND CLOSE PARENTHESIS
				case '(':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;
				case ')':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;
				case ',':
					cCh = this->searchChar(lexemeBegin);
					return cCh;
					break;

				//STRING LITERALS
				case '"':
					source->read(lexemeBegin,1);
					*sChar = *lexemeBegin;
					while(ind){
						source->read(lexemeBegin,1);
						if(source->peek() == '"'){
							strcat(sChar, lexemeBegin);
							ind = false;
							//Just read one more ... [BUG]
							source->read(lexemeBegin,1);
							//token value for string literal is 38
							table->insertOnST(sChar,Token("STR_LIT",27,"STR_LIT",sChar));
							return sChar;
						}
						else{
							if(source->eof()){
								PrintLog("ERROR: STRING LITERAL QUOTATION EXPECTED");
								ind = false;
								return 0;
						}
						if(*lexemeBegin != '\n'){
							strcat(sChar, lexemeBegin);
						}
					}
				}
				break;
	
				//DELIMITER
				case ';':
					*sChar = ';';
					sChar = table->getKey(sChar);
					if(sChar) return sChar;
					else return 0;
					break;

				//FUNCTION-STATEMENT
				case ':':
					*sChar = ':';
					*forward = source->peek();
					if(*forward == '='){
						source->read(lexemeBegin,1);
						strcat(sChar,lexemeBegin);
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					else{
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					break;

				//GREATER THAN SYMBOL
				case '>':
					*sChar = '>';
					*forward = source->peek();
					if(*forward == '='){
						source->read(lexemeBegin,1);
						strcat(sChar,lexemeBegin);
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					else{
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					break;

				//LESS THAN SYMBOL
				case '<':
					*sChar = '<';
					*forward = source->peek();
					if(*forward == '='){
						source->read(lexemeBegin,1);
						strcat(sChar,lexemeBegin);
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					else{
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					break;

				//NOT RELOP SYMBOL
				case '!':
					*sChar = '!';
					*forward = source->peek();
					if(*forward == '='){
						source->read(lexemeBegin,1);
						strcat(sChar,lexemeBegin);
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					else{
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					break;

				//EQUALITY SYMBOL
				case '=':
					*sChar = '=';
					*forward = source->peek();
					if(*forward == '='){
						source->read(lexemeBegin,1);
						strcat(sChar,lexemeBegin);
						sChar = table->getKey(sChar);
						if(sChar) return sChar;
						else return 0;
					}
					else return 0;
					break;

				//CONCATENATION OPERATOR
				case '.':
					*forward = source->peek();
					iCh = (int)*forward;
					if(!isdigit(iCh)){
						sChar = table->getKey(".");
						if(sChar) return sChar;
						else return 0 ;
					}
					else if(isdigit(iCh)){
						//FOR NUMERIC VALUES SUCH AS .021 .2928 etc.
						*sChar = *lexemeBegin;
						decPt = 0;
						while(ind){
							*forward = source->peek();
						
							if(*forward == '.' && decPt == 1){
								PrintLog("ERROR: MISUSED CONCATENATION OPERATOR OR DECIMAL POINT");
								source->read(lexemeBegin,1);
							}
							else if(*forward== '.' && decPt == 0)
								decPt = 1;

							iCh = (int)*forward;
							if(isdigit(iCh) || *forward == '.'){	
								source->read(lexemeBegin,1);
								strcat(sChar,lexemeBegin);
							}
							else{
								ind = false;
								table->insertOnST(sChar,Token("NUMBER",23,"NUMBER",sChar));
								return sChar;
							}
						}
					}
				else{
					PrintLog("ERROR: MISUSED CONCATENATION OPERATOR OR DECIMAL POINT");
					return 0;
				}
				break;

				default:
					*sChar = *lexemeBegin;
					iCh = (int)*lexemeBegin;
					if(isdigit(iCh)){
						decPt = 0;
						while(ind){
							*forward = source->peek();
							if(*forward == '.' && decPt == 1){
								source->read(lexemeBegin,1);
								PrintLog("ERROR: MISUSED DECIMAL POINT");
								return 0;
							}
							else if(*forward== '.' && decPt == 0)
								decPt = 1;

							iCh = (int)*forward;
							if(isdigit(iCh)||*forward == '.'){	
								source->read(lexemeBegin,1);
								strcat(sChar,lexemeBegin);
							}
							else{
								//INVALID IDENTIFIER
								if(isalpha(iCh)){
									PrintLog("ERROR: INVALID IDENTIFIER");
									while(ind){
										if(isalpha(iCh)||isdigit(iCh)||*lexemeBegin == '_'){
											source->read(lexemeBegin,1);
											iCh = (int)*lexemeBegin;
										}
										else{
											ind = false;
											return 0;
										}
									}
								}
								//ELSE IT IS A NUMERIC LITERAL
								else{
									//install numeric value to symbol table and return the key.
									//token value for num is 37
									table->insertOnST(sChar,Token("NUMBER",23,"NUMBER",sChar));
									return sChar;
									ind = false;
								}
							}
						}
					}
					else if(isalpha(iCh) || *lexemeBegin == '_'){
						
						while(ind){
							*forward = source->peek();
							iCh = (int)*forward;
							if(isalpha(iCh)|| *forward == '_' || isdigit(iCh)){
								source->read(lexemeBegin,1);
								strcat(sChar,lexemeBegin);
							}
							else{
								cCh = table->getKey(sChar);
								if(cCh){
									ind = false;
									return cCh;
								}
								else{
									//If it was preceded by a parenthesis, it returns instead a def_routine
									//For maintainability issues, this should not be here. - December 28, 2011
									if(*forward == '('){
										//token value for DEF is 36
										table->insertOnST(sChar,Token("DEF_NAME",7,"DEF_NAME",""));
										ind = false;	
										return sChar;
									}
									else{
										//token value for ID is 35
										table->insertOnST(sChar,Token("ID",17,"",""));
										ind = false;
										return sChar;
									}
								}
							}
						}
					}
					else {
						PrintLog("ERROR: NOT FOUND IN THE SYMBOL TABLE");
						return 0;
					}
					break;
				}
			}
		}
		else
			return 0;
	}
	return 0;
}

char* Scanner::searchChar(char* find){
	find = table->getKey(find);
	if(find){
		return find;
	}
	else{
		PrintLog("ERROR: NOT FOUND IN THE SYMBOL TABLE");
		return 0;
	}
}

//Prints the error message
void Scanner::PrintLog(const string err){cout<<err<<endl;}

//Allocates the memory to prevent NULL pointers for the lexical analyzer
void Scanner::AllocateMem(){
	//lesser size_t means the heap may overwrite other values - December 26, 2011
	lexemeBegin = alloc(10);
	forward = alloc(10);
}

//For iterating character allocation and deallocation
void Scanner::AllocateChar(){sChar = alloc(200);}
void Scanner::FreeChar(){free(sChar);}
