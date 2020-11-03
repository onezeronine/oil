/* 
 * File:   parser_declarations.cpp
 * Author: Kenneth Bastian
 *
 */
#include "parser_declarations.h"

void Rules::setCFG(int LS, int RS[5],int num){
	this->left_side = LS;
	for(int x=0; x<sizeof(RS); x++){
		this->right_side[x] = RS[x];
	}
	this->num_of_var = num;
}

int Rules::getLeft(){
	return left_side;
}

int *Rules::getRight(){
	return right_side;
}

int Rules::getNum(){
	return num_of_var;
}

int checkNode(int value){
	if(value == BEGIN) return 1;
	else if(value == END) return 1;
	else if(value == CHR || value == INT || value == FLT || value == BOO || value == DBL) return 1;
	else if(value == NUM_LIT || value == STR_LIT || value == ID || value == DEF) return 1;
	else if(value == WHILE || value == IF) return 1;
	else if(value == LT || value == GT || value == LE || value == GE || value == EQ) return 1;
	else if(value == A_OP || value == S_OP || value == M_OP || value == D_OP || value == EXP_OP) return 1;
	else return 0;
}
//Initialize the Rules
//setCFG (LEFT SIDE REPRESENTATION, RIGHT SIDE PRODUCTIONS, NUMBER OF PRODUCTIONS)
//num_of_ = number of productions that is necessary to be popped out.
void declareRules(Rules *rules){
	int setOfR[41][5];

	setOfR[1][0] = BEGIN; setOfR[1][1] = V_STMTS; setOfR[1][2] = END; setOfR[1][3] = DELIM;
	rules[BEGIN_END].setCFG(V_BEGIN_END, setOfR[1], 4);

	setOfR[2][0] = V_STMTS; setOfR[2][1] = V_STMT;
	rules[STMTS1].setCFG(V_STMTS, setOfR[2], 2);
	
	setOfR[3][0] = EMPTY;
	rules[STMTS2].setCFG(V_STMTS, setOfR[3], 0);

	setOfR[4][0] = V_DECL;
	rules[STMT1].setCFG(V_STMT, setOfR[4], 1);

	setOfR[5][0] = V_EXPR;
	rules[STMT2].setCFG(V_STMT, setOfR[5], 1);

	setOfR[6][0] = V_COND;
	rules[STMT3].setCFG(V_STMT, setOfR[6], 1);

	setOfR[7][0] = V_WHILE;
	rules[STMT4].setCFG(V_STMT, setOfR[7], 1);

	setOfR[8][0] = V_FUNC;
	rules[STMT5].setCFG(V_STMT, setOfR[8], 1);

	setOfR[9][0] = V_DT; setOfR[9][1] = ID; setOfR[9][2] = DELIM;
	rules[DECL].setCFG(V_DECL, setOfR[9], 3);

	setOfR[10][0] = BOO;
	rules[DT1].setCFG(V_DT, setOfR[10], 1);

	setOfR[11][0] = CHR;
	rules[DT2].setCFG(V_DT, setOfR[11], 1);

	setOfR[12][0] = INT;
	rules[DT3].setCFG(V_DT, setOfR[12], 1);

	setOfR[13][0] = FLT;
	rules[DT4].setCFG(V_DT, setOfR[13], 1);

	setOfR[14][0] = DBL;
	rules[DT5].setCFG(V_DT, setOfR[14], 1);

	setOfR[15][0] = ID; setOfR[15][1] = ASSIGN_OP; setOfR[15][2] = V_EXP_P; setOfR[15][3] = DELIM;
	rules[EXPR].setCFG(V_EXPR, setOfR[15], 4);

	setOfR[16][0] = V_EXP_P; setOfR[16][1] = A_OP; setOfR[16][2] = V_EXP_2P;
	rules[EXP_P1].setCFG(V_EXP_P, setOfR[16], 3);

	setOfR[17][0] = V_EXP_P; setOfR[17][1] = S_OP; setOfR[17][2] = V_EXP_2P;
	rules[EXP_P2].setCFG(V_EXP_P, setOfR[17], 3);

	setOfR[18][0] = V_EXP_2P; 
	rules[EXP_P3].setCFG(V_EXP_P, setOfR[18], 1);

	setOfR[19][0] = V_EXP_2P; setOfR[19][1] = M_OP; setOfR[19][2] = V_EXP_3P;
	rules[EXP_2P1].setCFG(V_EXP_2P, setOfR[19], 3);
	
	setOfR[20][0] = V_EXP_2P; setOfR[20][1] = D_OP; setOfR[20][2] = V_EXP_3P;
	rules[EXP_2P2].setCFG(V_EXP_2P, setOfR[20], 3);

	setOfR[21][0] = V_EXP_3P; 
	rules[EXP_2P3].setCFG(V_EXP_2P, setOfR[21], 1);

	setOfR[22][0] = V_PAREN; setOfR[23][1] = EXP_OP; setOfR[23][2] = V_EXP_3P;
	rules[EXP_3P1].setCFG(V_EXP_3P, setOfR[22], 3);

	setOfR[23][0] = V_PAREN;
	rules[EXP_3P2].setCFG(V_EXP_3P, setOfR[23], 1);

	setOfR[24][0] = PR_BEG; setOfR[23][1] = V_EXP_P; setOfR[23][2] = PR_END;
	rules[PAREN1].setCFG(V_PAREN, setOfR[24], 3);

	setOfR[25][0] = ID; 
	rules[PAREN2].setCFG(V_PAREN, setOfR[25], 1);
	
	setOfR[26][0] = NUM_LIT; 
	rules[PAREN3].setCFG(V_PAREN, setOfR[26], 1);

	setOfR[27][0] = IF; setOfR[27][1] = V_REL; setOfR[27][2] = PR_BEG; setOfR[27][3] = V_STMTS; setOfR[27][4] = PR_END; 
	rules[COND].setCFG(V_COND, setOfR[27], 5);

	setOfR[28][0] = WHILE; setOfR[28][1] = V_REL; setOfR[28][2] = PR_BEG; setOfR[28][3] = V_STMTS; setOfR[28][4] = PR_END; 
	rules[WHILE1].setCFG(V_WHILE, setOfR[28], 5);

	setOfR[29][0] = ID; setOfR[29][1] = V_REL_OP; setOfR[29][2] = ID;
	rules[REL1].setCFG(V_REL, setOfR[29], 3);

	setOfR[30][0] = NUM_LIT; setOfR[30][1] = V_REL_OP; setOfR[30][2] = ID;
	rules[REL2].setCFG(V_REL, setOfR[30], 3);

	setOfR[31][0] = ID; setOfR[31][1] = V_REL_OP; setOfR[31][2] = NUM_LIT;
	rules[REL3].setCFG(V_REL, setOfR[31], 3);

	setOfR[32][0] = NUM_LIT; setOfR[32][1] = V_REL_OP; setOfR[32][2] = NUM_LIT;
	rules[REL4].setCFG(V_REL, setOfR[32], 3);

	setOfR[33][0] = GT; 
	rules[REL_OP1].setCFG(V_REL_OP, setOfR[33], 1);

	setOfR[34][0] = LT; 
	rules[REL_OP2].setCFG(V_REL_OP, setOfR[34], 1);

	setOfR[35][0] = EQ; 
	rules[REL_OP3].setCFG(V_REL_OP, setOfR[35], 1);

	setOfR[36][0] = GE; 
	rules[REL_OP4].setCFG(V_REL_OP, setOfR[36], 1);

	setOfR[37][0] = LE; 
	rules[REL_OP5].setCFG(V_REL_OP, setOfR[37], 1);

	setOfR[38][0] = DEF; setOfR[38][1] = PR_BEG; setOfR[38][2] = V_F_PARAM; setOfR[38][3] = PR_END; setOfR[38][4] = DELIM;   
	rules[FUNC].setCFG(V_FUNC, setOfR[38], 5);

	setOfR[39][0] = STR_LIT; 
	rules[F_PARAM1].setCFG(V_F_PARAM, setOfR[39], 1);

	setOfR[40][0] = ID; 
	rules[F_PARAM2].setCFG(V_F_PARAM, setOfR[40], 1);
}

std::string returnStringVal(int val){
	switch(val){
	case 0:
		return "START";
	case 1:
		return "STMTS";
	case 2:
		return "STMT";
	case 3:
		return "DECL";
	case 4:
		return "DT";
	case 5:
		return "EXPR";
	case 6:
		return "EXP1";
	case 7:
		return "EXP2";
	case 8:
		return "EXP3";
	case 9:
		return "PAREN";
	case 10:
		return "COND-STMT";
	case 11:
		return "WHILE-LOOP";
	case 12:
		return "REL";
	case 13:
		return "REL_OP";
	case 14:
		return "FUNC";
	case 15:
		return "PARAM";
	default:
		return "NONE";
	}

}