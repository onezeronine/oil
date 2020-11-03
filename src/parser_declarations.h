/* 
 * File:   parser_declarations.h
 * Author: Kenneth Bastian
 *
 */

#include <string>

/*numeric values for significant variables*/
const static int NUM_OF_TOKENS = 29;
const static int NUM_OF_VARIABLES = 16;
const static int NUM_OF_STATES = 72;
const static int NUM_OF_RULES = 41;

/*rule number representations*/
const static int	BEGIN_END	=	1;
const static int	STMTS1	=	2;
const static int	STMTS2	=	3;
const static int	STMT1	=	4;
const static int	STMT2	=	5;
const static int	STMT3	=	6;
const static int	STMT4	=	7;
const static int	STMT5	=	8;
const static int	DECL	=	9;
const static int	DT1	=	10;
const static int	DT2 =	11;
const static int	DT3	=	12;
const static int	DT4	=	13;
const static int	DT5	=	14;
const static int	EXPR	=	15;
const static int	EXP_P1	=	16;
const static int	EXP_P2	=	17;
const static int	EXP_P3	=	18;
const static int	EXP_2P1	=	19;
const static int	EXP_2P2	=	20;
const static int	EXP_2P3	=	21;
const static int	EXP_3P1	=	22;
const static int	EXP_3P2	=	23;
const static int	PAREN1	=	24;
const static int	PAREN2	=	25;
const static int	PAREN3	=	26;
const static int	COND	=	27;
const static int	WHILE1	=	28;
const static int	REL1	=	29;
const static int	REL2	=	30;
const static int	REL3	= 	31;
const static int	REL4	=	32;
const static int	REL_OP1	=	33;
const static int	REL_OP2	=	34;
const static int	REL_OP3	=	35;
const static int	REL_OP4	=	36;
const static int	REL_OP5	=	37;
const static int	FUNC	=	38;
const static int	F_PARAM1=	39;
const static int	F_PARAM2=	40;


/*Token representations*/
const static int	A_OP	=	0;
const static int	ASSIGN_OP	=	1;
const static int	BEGIN=	2;
const static int	BOO	=	3;
const static int	CHR	=	4;
const static int	D_OP	=	5;
const static int	DBL		=	6;
const static int	DEF		=	7;
const static int	DELIM	=	8;
//const static int	FLT		=	9;
const static int	EMPTY=	29; //special
const static int	END	=	11;
const static int	EQ		=	12;
const static int	EXP_OP	=	13;
const static int	FLT		=	14;
const static int	GE		=	15;
const static int	GT	=	16;
const static int	ID	=	17;
const static int	IF	=	18;
const static int	INT	=	19;
const static int	LE	=	20;
const static int	LT	=	21;
const static int	M_OP	=	22;
const static int	NUM_LIT	=	23;
const static int	PR_BEG	=	24;
const static int	PR_END	=	25;
const static int	S_OP	=	26;
const static int	STR_LIT	=	27;
const static int	WHILE	=	28;


/*variable representation*/
const static int	V_BEGIN_END	=	0;
const static int	V_STMTS		=	1;
const static int	V_STMT		=	2;
const static int	V_DECL		=	3;
const static int	V_DT		=	4;
const static int	V_EXPR	=	5;
const static int	V_EXP_P		=	6;
const static int	V_EXP_2P	=	7;
const static int	V_EXP_3P	=	8;
const static int	V_PAREN		=	9;
const static int	V_COND	=	10;
const static int	V_WHILE	=	11;
const static int	V_REL	=	12;
const static int	V_REL_OP	=	13;
const static int	V_FUNC		=	14;
const static int	V_F_PARAM	=	15;


class Rules{
private:
	int left_side;
	int right_side[5];
	int num_of_var;
public:
	void setCFG(int LS, int RS[5], int num);
	int getNum();
	int getLeft();
	int *getRight();
};

void declareRules(Rules *rules);
int checkNode(int value);
std::string returnStringVal(int val);