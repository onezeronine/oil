/* 
 * File:   oil.cpp
 * Author: Kenneth Bastian
 *
 */

#include "oil.h"

int main(int argc, char** argv) {

	if(argc != 2){
   		cerr<<"Incorrect Usage of Parameters\n";
		exit(-1);
	}

	char* source_program;
	source_program = argv[1];
	
	ifstream source;
	source.open(source_program,ios::out);
	if(source){
		cout<<"Opening the file..."<<endl;
	}
	else{
		cerr<<"Error: File cannot be opened or corrupted."<<endl;
		exit(-1);
	}

	//passed by reference
	Parser parse = Parser(&source);
	parse.parse();
}
