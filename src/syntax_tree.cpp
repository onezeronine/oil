/* 
 * File:   syntax_tree.cpp
 * Author: Kenneth Bastian
 *
 */

#include "syntax_tree.h"

void Interpreter::preorder(node* p){
    if(p){	
		cout<<p->key<<" ";
		cout<<" [sibling: ";preorder(p->sibling);	cout<<"]";
		cout<<"[child: ";	preorder(p->child);		cout<<"]";
    }
}

void Interpreter::setST(SymbolTable *st){
	_Table = st;
	//cout<<"Symbol Table transferred"<<endl<<endl;
}

void Interpreter::interpret(node *root){
	if(root != NULL){
		interpret(root->child);

		if(root->key == "FUNC"){
			node *ptr;
			if(root->child->key == "print"){
				ptr = root->child;
				string temp = ptr->sibling->sibling->child->key;
				cout<<temp<<endl;
			}
			if(root->child->key == "get"){
				string dest_id = root->child->key;
				string value;
				cin>>value;
				_Table->setToken(dest_id,Token("ID",17,"",value));
			}
			if(root->child->key == "printv"){
				char *pId = alloc(10);
				ptr = root->child;
				string sId = ptr->sibling->sibling->child->key;
				copy(sId.begin(),sId.end(),pId);
				Token tokId = _Table->getToken(pId);
				cout<<tokId.value<<endl;
			}
		}

		if(root->key == "EXPR"){
			this->intr_expr(root);
			//pop each element in the stack
			//As you pop, you compare elements etc.
			//Assume that it is postfix and it is always valid...
		}

		if(root->key == "DECL"){
			this->intr_decl(root);
		}

		interpret(root->sibling);
	}
}


void Interpreter::intr_expr(node *expr){
	if(expr){
		intr_expr(expr->child);
		intr_expr(expr->sibling);
		string t = expr->key;
		if(expr->key == "EXPR" || expr->key == "PAREN" || expr->key == "EXP3" || expr->key == "EXP2" || expr->key == "EXP1" || expr->key == ")" || expr->key == "(" || expr->key == ";"){}
		else{
			//push in the stack AS string
			string temp = expr->key;
			char *loc = alloc(10);
			copy(temp.begin(), temp.end(), loc);
			Token n = _Table->getToken(loc);
			if(n.value == "") _postfix.push(expr->key);
			else	_postfix.push(n.value);
			//cout<<expr->key<<n.value<<endl;
		}
	}
}

void Interpreter::intr_decl(node *decl){
	string data_type = decl->child->child->key;
	string id = decl->child->sibling->key;
	if(data_type == "int"){
		_Table->setToken(id, Token("ID", 17, "int", "0"));
	}
	if(data_type == "flt"){
		_Table->setToken(id, Token("ID", 17, "flt", "0"));
	}
	if(data_type == "dbl"){
		_Table->setToken(id, Token("ID", 17, "dbl", "0"));
	}
	if(data_type == "boo"){
		_Table->setToken(id, Token("ID", 17, "boo", "0"));
	}
}