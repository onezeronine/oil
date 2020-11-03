/* 
 * File:   parser.cpp
 * Author: Kenneth Bastian
 */

#include "parser.h"

//Destructor
Parser::~Parser(){}

//Constructor
Parser::Parser(ifstream* s){
	intr = Interpreter();
	sf = s;
	table = SymbolTable();
	declareActionTable();
	declareGotoTable();
	cout<<"initializing the PRODUCTION RULES..."<<endl;
	Rules *rules_loc = new Rules[NUM_OF_RULES+1];
	declareRules(rules_loc);
	rules = rules_loc;
	root = NULL;
	ptr = NULL;
	sptr = NULL;
	//cptr = NULL; next = NULL; root = NULL;
	//Another pass by reference on ifstream
	scan = Scanner(sf,&table);
}

//LR parsing algorithm
void Parser::parse(){
	char* input = alloc(20);
	bool ind = true;
	string str_ind;
	input = scan.scan();
	input_val = table.getOnST(input);
	s.token = EMPTY; //EMPTY = 39
	s.state = 0;
	stack.push(s);
	
	while(ind){
		if(input){
			if(s.state >= 0){	getter = Action[s.state][input_val];	}
			else{	cout<<"Fatal Error: Unknown Variable";	exit(-1);	}
			
			if(sf->eof()){ input_val = EMPTY; input = "$";}
			
			if(!Action[s.state][input_val].empty()){
				shift = getter.substr(0,1);
				if(shift == "s"){
					cout<<"Shifting token "<<table.getToken(input).tokenName<<" by "<<Action[s.state][input_val]<<endl<<endl;	
					string temp = getter.substr(1, getter.length()-1);
					s.state = atoi(temp.c_str());
										
					node *ntemp = new node;
					ntemp->key = input;
					ntemp->child = NULL; ntemp->sibling = NULL;
					s.stackNode = ntemp;
										
					free(input);
					input = scan.scan();
					if(sf->eof()){input_val = EMPTY; input = "$";}
					s.token = input_val;
					input_val = table.getOnST(input);
					
					stack.push(s);
				}
				else if (shift == "r"){
					node *t;
					string temp = getter.substr(1, getter.length()-1);
					int gotoNum = atoi(temp.c_str());
					for(int i = rules[gotoNum].getNum(); i > 0 ; i--){
						if(stack.top().stackNode){
							if(ptr == NULL){
								ptr = stack.top().stackNode;
								root = ptr;
							}
							else{
								sptr = stack.top().stackNode;
								sptr->sibling = ptr;
								ptr = sptr;
								root = ptr;
							}
						}
						stack.pop();
					}
					ptr = NULL;
					s.state = Goto[stack.top().state][rules[gotoNum].getLeft()];
					s.token = rules[gotoNum].getLeft();

					string stemp = returnStringVal(rules[gotoNum].getLeft());
					t = new node; t->key = stemp; 
					if(root != NULL) t->child = root;
					else t->child = NULL;
					t->sibling = NULL;
					root = t;
					s.stackNode = t;
					stack.push(s);
					cout<<"Reduced by rule "<<gotoNum<<endl<<endl;
					
				}
				else if (shift == "a"){
					cout<<"Language is accepted"<<endl<<"Printing the tree..."<<endl;
					intr.preorder(root); cout<<endl;
					ind = false;
				}
			}
			else{	
				cout<<endl<<"Syntax error occured at symbol '"<<input<<"' at line "<<scan.lineNumber<<endl;
				cout<<"No Action found on ["<<s.state<<"]["<<input_val<<"]"<<endl;
				ind = false;
				exit(-1);
			}
		}
		else{
			if(sf->eof()){
				cout<<"End Of File Reached."<<endl;
				ind = false;
			}
			else{
				cout<<"Unexpected error occured."<<endl;
				ind = false;
				exit(-1);
			}
			
		}//end inputs
	}//end while
	cout<<"Interpreting...."<<endl<<endl;
	
	intr.setST(&table);
	intr.interpret(root);
}


//Initialize the Action Table
//Action [STATE NUMBER] [TOKEN REPRESENTATION]
void Parser::declareActionTable(){
cout<<"Initializing Action Table"<<endl;
//State 0
Action[0][2] = "s2"; 

//State 1
Action[1][29] = "acc";

//State 2
Action[2][3] = "r3"; Action[2][4] = "r3"; Action[2][6] = "r3"; Action[2][7] = "r3"; Action[2][11] = "r3"; 
Action[2][14] = "r3"; Action[2][17] = "r3"; Action[2][18] = "r3"; Action[2][19] = "r3"; Action[2][25] = "r3"; 
Action[2][28] = "r3";

//State 3
Action[3][3] = "s11"; Action[3][4] = "s12"; Action[3][6] = "s13"; Action[3][7] = "s14";
Action[3][11] = "s15"; Action[3][14] = "s16"; Action[3][17] = "s17"; Action[3][18] = "s18";
Action[3][19] = "s19"; Action[3][28] = "s20"; 

//State 4
Action[4][3] = "r2"; Action[4][4] = "r2"; Action[4][6] = "r2"; Action[4][7] = "r2";
Action[4][11] = "r2"; Action[4][14] = "r2"; Action[4][17] = "r2"; Action[4][18] = "r2";
Action[4][19] = "r2"; Action[4][25] = "r2"; Action[4][28] = "r2";

//State 5
Action[5][3] = "r4"; Action[5][4] = "r4"; Action[5][6] = "r4"; Action[5][7] = "r4";
Action[5][11] = "r4"; Action[5][14] = "r4"; Action[5][17] = "r4"; Action[5][18] = "r4";
Action[5][19] = "r4"; Action[5][25] = "r4"; Action[5][28] = "r4";

//State 6
Action[6][17]="s21";

//State 7
Action[7][3] = "r5"; Action[7][4] = "r5"; Action[7][6] = "r5"; Action[7][7] = "r5";
Action[7][11] = "r5"; Action[7][14] = "r5"; Action[7][17] = "r5"; Action[7][18] = "r5";
Action[7][19] = "r5"; Action[7][25] = "r5"; Action[7][28] = "r5"; 

//State 8
Action[8][3] = "r6"; Action[8][4] = "r6"; Action[8][6] = "r6"; Action[8][7] = "r6";
Action[8][11] = "r6"; Action[8][14] = "r6"; Action[8][17] = "r6"; Action[8][18] = "r6";
Action[8][19] = "r6"; Action[8][25] = "r6"; Action[8][28] = "r6";


//State 9
Action[9][3] = "r7"; Action[9][4] = "r7"; Action[9][6] = "r7"; Action[9][7] = "r7";
Action[9][11] = "r7"; Action[9][14] = "r7"; Action[9][17] = "r7"; Action[9][18] = "r7";
Action[9][19] = "r7"; Action[9][25] = "r7"; Action[9][28] = "r7"; 

//State 10
Action[10][3] = "r8"; Action[10][4] = "r8"; Action[10][6] = "r8"; Action[10][7] = "r8";
Action[10][11] = "r8"; Action[10][14] = "r8"; Action[10][17] = "r8"; Action[10][18] = "r8";
Action[10][19] = "r8"; Action[10][25] = "r8"; Action[10][28] = "r8";

//State 11
Action[11][17] = "r10"; 

//State 12
Action[12][17] = "r11";

//State 13
Action[13][17] = "r13"; 

//State 14
Action[14][24] = "s22"; 

//State 15
Action[15][8] = "s23";

//State 16
Action[16][17] = "r14";

//State 17
Action[17][1] = "s24"; 

//State 18
Action[18][17] = "s26"; Action[18][23] = "s27";

//State 19
Action[19][17] = "r12";

//State 20
Action[20][17] = "s26"; Action[20][23] = "s27"; 

//State 21
Action[21][8] = "s29"; 

//State 22
Action[22][17] = "s31"; Action[22][27] = "s32";


//State 23
Action[23][29] = "r1";

//State 24
Action[24][17] = "s37"; Action[24][23] = "s38"; Action[24][24] = "s39";

//State 25
Action[25][24] = "s40";

//State 26
Action[26][12] = "s42"; Action[26][15] = "s43"; Action[26][16] = "s44";
Action[26][20] = "s45"; Action[26][21] = "s46";

//State 27
Action[27][12] = "s42"; Action[27][15] = "s43"; Action[27][16] = "s44";
Action[27][20] = "s45"; Action[27][21] = "s46";

//State 28
Action[28][24] = "s48";

//State 29
Action[29][3] = "r9"; Action[29][4] = "r9"; Action[29][6] = "r9"; Action[29][7] = "r9";
Action[29][11] = "r9"; Action[29][14] = "r9"; Action[29][17] = "r9"; Action[29][18] = "r9";
Action[29][19] = "r9"; Action[29][25] = "r9"; Action[29][28] = "r9";

//State 30
Action[30][25] = "s49";

//State 31 
Action[31][25] = "r40";

//State 32
Action[32][25] = "r39";

//State 33
Action[33][0] = "s50"; Action[33][8] = "s51"; Action[33][27] = "s52";

//State 34
Action[34][0] = "r18"; Action[34][5] = "s53"; Action[34][8] = "r18";
Action[34][22] = "s54"; Action[34][25] = "r18"; Action[34][27] = "r18";

//State 35
Action[35][0]="r21"; Action[35][5]="r21"; Action[35][8]="r21"; 
Action[35][22]="r21"; Action[35][25]="r21"; Action[35][27]="r21"; 

//State 36
Action[36][0]="r23"; Action[36][5]="r23"; Action[36][8]="r23"; 
Action[36][13]="s55"; Action[36][22]="r23"; Action[36][25]="r23";
Action[36][27]="r23"; 

//State 37
Action[37][0]="r25"; Action[37][5]="r25"; Action[37][8]="r25"; 
Action[37][13]="r25"; Action[37][22]="r25"; Action[37][25]="r25"; 
Action[37][27]="r25"; 

//State 38
Action[38][0]="r26"; Action[38][5]="r26"; Action[38][8]="r26"; 
Action[38][13]="r26"; Action[38][22]="r26"; Action[38][25]="r26"; 
Action[38][27]="r26"; 

//State 39
Action[39][17]="s37"; Action[39][23]="s38"; Action[39][24]="s39"; 

//State 40
Action[40][3]="r3"; Action[40][4]="r3"; Action[40][6]="r3"; 
Action[40][7]="r3"; Action[40][11]="r3"; Action[40][14]="r3"; 
Action[40][17]="r3"; Action[40][18]="r3"; Action[40][19]="r3"; 
Action[40][25]="r3"; Action[40][28]="r3"; 

//State 41
Action[41][17]="s58"; Action[41][23]="s59"; 

//State 42
Action[42][17]="r37"; Action[42][23]="r37"; 

//State 43
Action[43][17]="r35"; Action[43][23]="r35"; 

//State 44
Action[44][17]="r36"; Action[44][23]="r36"; 

//State 45
Action[45][17]="r33"; Action[45][23]="r33"; 

//State 46
Action[46][17]="r34"; Action[46][23]="r34"; 

//State 47
Action[47][17]="s60"; Action[47][23]="s61"; 

//State 48
Action[48][3]="r3";Action[48][4]="r3";  Action[48][6]="r3"; 
Action[48][7]="r3"; Action[48][11]="r3"; Action[48][14]="r3";
Action[48][17]="r3"; Action[48][18]="r3"; Action[48][19]="r3"; 
Action[48][25]="r3"; Action[48][28]="r3"; 

//State 49
Action[49][8]="s63";

//State 50
Action[50][17]="s37"; Action[50][23]="s38"; Action[50][24]="s39"; 

//State 51
Action[51][3]="r15"; Action[51][4]="r15"; Action[51][6]="r15";
Action[51][7]="r15"; Action[51][11]="r15"; Action[51][14]="r15"; 
Action[51][17]="r15"; Action[51][18]="r15"; Action[51][19]="r15";
Action[51][25]="r15"; 
Action[51][28]="r15"; 

//State 52
Action[52][17]="s37"; Action[52][23]="s38"; Action[52][24]="s39"; 

//State 53
Action[53][17]="s37"; Action[53][23]="s38"; Action[53][24]="s39"; 

//State 54
Action[54][17]="s37"; Action[54][23]="s38"; Action[54][24]="s39"; 

//State 55
Action[55][17]="s37"; Action[55][23]="s38"; Action[55][24]="s39"; 

//State 56
Action[56][0]="s50"; Action[56][25]="s69";Action[56][27]="s52";

//State 57
Action[57][3]="s11"; Action[57][4]="s12"; Action[57][6]="s13"; 
Action[57][7]="s14"; Action[57][14]="s16"; Action[57][17]="s17"; 
Action[57][18]="s18"; Action[57][19]="s19"; Action[57][25]="s70"; 
Action[57][28]="s20"; 

//State 58
Action[58][24]="r29"; 

//State 59
Action[59][24]="r30"; 

//State 60
Action[60][24]="r31"; 

//State 61
Action[61][24]="r32"; 

//State 62
Action[62][3]="s11"; Action[62][4]="s12"; Action[62][6]="s13"; 
Action[62][7]="s14"; Action[62][14]="s16"; Action[62][17]="s17"; 
Action[62][18]="s18"; Action[62][19]="s19"; Action[62][25]="s71"; 
Action[62][28]="s20"; 

//State 63
Action[63][3]="r38"; Action[63][4]="r38"; Action[63][6]="r38"; 
Action[63][7]="r38"; Action[63][11]="r38"; Action[63][14]="r38"; 
Action[63][17]="r38"; Action[63][18]="r38"; Action[63][19]="r38"; 
Action[63][25]="r38"; Action[63][28]="r38"; 

//State 64
Action[64][0]="r16"; Action[64][5]="s53"; Action[64][8]="r16"; 
Action[64][22]="s54"; Action[64][25]="r16"; Action[64][27]="r16"; 

//State 65
Action[65][0]="r17"; Action[65][5]="s53"; Action[65][8]="r17"; 
Action[65][22]="s54"; Action[65][25]="r17"; Action[65][27]="r17"; 

//State 66
Action[66][0]="r20"; Action[66][5]="r20"; Action[66][8]="r20"; 
Action[66][22]="r20"; Action[66][25]="r20"; Action[66][27]="r20"; 

//State 67
Action[67][0]="r19"; Action[67][5]="r19"; Action[67][8]="r19"; 
Action[67][22]="r19"; Action[67][25]="r19"; Action[67][27]="r19"; 

//State 68
Action[68][0]="r22"; Action[68][5]="r22"; Action[68][8]="r22"; 
Action[68][22]="r22"; Action[68][25]="r22"; Action[68][27]="r22"; 

//State 69
Action[69][0]="r24"; Action[69][5]="r24"; Action[69][8]="r24"; 
Action[69][13]="r24"; Action[69][22]="r24"; Action[69][25]="r24"; 
Action[69][27]="r24"; 

//State 70
Action[70][3]="r27"; Action[70][4]="r27"; Action[70][6]="r27"; 
Action[70][7]="r27"; Action[70][11]="r27"; Action[70][14]="r27"; 
Action[70][17]="r27"; Action[70][18]="r27"; Action[70][19]="r27"; 
Action[70][25]="r27"; Action[70][28]="r27"; 

//State 71
Action[71][3]="r28"; Action[71][4]="r28"; Action[71][6]="r28"; 
Action[71][7]="r28"; Action[71][11]="r28"; Action[71][14]="r28"; 
Action[71][17]="r28"; Action[71][18]="r28"; Action[71][19]="r28"; 
Action[71][25]="r28"; Action[71][28]="r28"; 
}

//Initialize the Goto Table
//Goto [STATE NUMBER] [VARIABLE REPRESENTATION]
void Parser::declareGotoTable(){
cout<<"Initializing Goto Table"<<endl;
Goto[0][0] = 1; 

Goto[2][1] = 3; 

Goto[3][2] = 4; Goto[3][3] = 5; Goto[3][4] = 6; Goto[3][5] = 7;
Goto[3][10] = 8; Goto[3][11] = 9; Goto[3][14] = 10;

Goto[18][12] = 25;

Goto[20][12] = 28; 

Goto[22][15] = 30; 

Goto[24][6] = 33; Goto[24][7] = 34; Goto[24][8] = 35; Goto[24][9] = 36;

Goto[26][13] = 41;

Goto[27][13] = 47;

Goto[39][6]=56; Goto[39][7]=34; Goto[39][8]=35; Goto[39][9]=36;

Goto[40][1]=57;

Goto[48][1]=62;

Goto[50][7]=64; Goto[50][8]=35; Goto[50][9]=36;

Goto[52][7]=65; Goto[52][8]=35; Goto[52][9]=36;

Goto[53][8]=66; Goto[53][9]=36;

Goto[54][8]=67; Goto[54][9]=36;

Goto[55][8]=68; Goto[55][9]=36;

Goto[57][2]=4; Goto[57][3]=5; Goto[57][4]=6; Goto[57][5]=7; Goto[57][10]=8; Goto[57][11]=9; Goto[57][14]=10;

Goto[62][2]=4; Goto[62][3]=5; Goto[62][4]=6; Goto[62][5]=7; Goto[62][10]=8; Goto[62][11]=9; Goto[62][14]=10;
}