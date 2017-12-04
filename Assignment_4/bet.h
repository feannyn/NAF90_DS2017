#ifndef _BET_H
#define _BET_H

#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>

using std::vector;
using std::cout;
using std::cin;
using std::stringstream;
using std::stack;
using std::string;
using std::endl;


class BET
{
	private:
		
		struct BinaryNode
		{
			BinaryNode* left;
			BinaryNode* right;

			string Data;

			BinaryNode(const string& s = "empty", BinaryNode* l = nullptr, BinaryNode* r = nullptr)
			{
				right = r;
				left = l;
				Data = s;
			}
			BinaryNode(string&& s, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
			{
				right = r;
				left = l;
				Data = std::move(s);
			}	
		};
		
		
	public:

		BET(); //default constructor

	//	one-parameter constructor, where parameter "postfix" is string containing a postfix expression. 
	//	The tree should be built based on the postfix expression. 
	//	Tokens in the postfix expression are separated by spaces.
		BET(const string& postfix); 

		BET(const BET& arg); //copy constructor

		~BET(); //destructor

		bool buildFromPostfix(const string& postfix);//will build new tree. return true if successful build.

		const BET& operator=(const BET& arg); //assignment operator;

		void printInfixExpression(); //prints out the infix expression

		void printPostfixExpression(); //prints out the post fix expression;

		size_t size(); //returns the number of nodes in the tree

		size_t leaf_nodes();//returns number of leaf nodes in the tree

		bool empty();

	private:
		BinaryNode* root;
		size_t treeSize;
		size_t leaves;	
	
		void printInfixExpression(BinaryNode* n);

		void makeEmpty(BinaryNode* &t);

		BinaryNode* clone(BinaryNode* t);

		void printPostfixExpression(BinaryNode* n);

		size_t size(BinaryNode* t);

		size_t leaf_nodes(BinaryNode* t);

		void init();

		bool isOperand(string arg) const;
		
		bool isOperator(string arg) const;

		int precedence(string arg) const;
};

#endif 

#include "bet.hpp"
