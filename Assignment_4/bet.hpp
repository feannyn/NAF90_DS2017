/*NOTE*/
/*On some of my functions the TA (Mehran) assisted me to get more streamlined code.
Some of my code was correct but he provided better alternative to what I had..
I labeled the areas accordingly*/

/*I have also noted areas of confusion where code would not behave as I anticipated*/

//Nicholas Feanny; naf16b



BET::BET()
{
	init(); // create a empty BETree	
}

BET::BET(const string& postfix)
{
	//call init() function
//	init();

	//call buildFromPostfx function
	buildFromPostfix(postfix);
}

BET::BET(const BET& arg) //copy constructor
{

	//initialize the member data of the new object 
	init();	
	root = clone(arg.root);
	treeSize = size(arg.root);
	leaves = leaf_nodes(arg.root);
}

BET::~BET() //destructor
{
	makeEmpty(this->root);
}

bool BET::buildFromPostfix(const string& postfix)//will build new tree. return true if successful build.
{	
	init();	
	//establish necessary variables
	string holder;	
	stringstream ss(postfix);
	vector<string> vStar;
	stack<BinaryNode*> sT;
	
	while(ss >> holder)
	{
		vStar.push_back(holder);	
	}		

	for(int i = 0; i < vStar.size(); i++)
	{
		if(isOperand(vStar[i]))
		{
			BinaryNode* newNode = new BinaryNode;
			newNode->Data = vStar[i];
			sT.push(newNode);
		}
		else if(isOperator(vStar[i]))
		{
			
			//check to verify that there are always two operands on the stack 
			//for the duration of the loop
			//Mehran Suggested this technique as prior I was doing this
			//in an if/else statement that execute the pop behavior only after 
			//the verification of the stack which caused issues
			//by checking at the start it bypasses any potential hazards. 
			
			//this if statement checks to verify that the stack maintains a size of 2 elements
			//if at any point it only contains less than 2 then it will return false.
			if(sT.size() < 2)
			{
				cout << "PostFix Expression Error (INSIDE IF)" << endl;
				return false;
			}

			BinaryNode* l_Node = new BinaryNode;
			BinaryNode* r_Node = new BinaryNode;

			//created this binaryNode but for whatever reason 
			//if I did the intialization starting at line 75 to 77 I'd get a 
			//a seg fault versus just one lining the binarynode via the constructor	
			//BinaryNode* backup = new BinaryNode; 
			
			r_Node = sT.top();
			sT.pop();

			l_Node = sT.top();
			sT.pop();
			
			//can use constructor here
			BinaryNode* backup = new BinaryNode(vStar[i], l_Node, r_Node);
//			backup->Data = vStar[i];
//			backup->left = l_Node;
//			backup->right = r_Node;		
	

			//push the current status of the expression onto the stack 	
			sT.push(backup);					
		}			
	}

	if(sT.size() > 1)
	{
		cout << "Error in postfix expression" << endl; //Mehran assisted me with this.
		return false;
	}
	//once the loop is completed, set the root node to the expression
	root = sT.top();
	sT.pop();
	
	treeSize = size(root);
	leaves = leaf_nodes(root);

	return true;
}

const BET& BET::operator=(const BET& arg) //assignment operator;
{
	//initialize and transfer data of pre-existing private data
	treeSize = size(arg.root);
	leaves = leaf_nodes(arg.root);
		
	//call the clone function to recreate the BETree
	//store in return the calling object
	root = clone(arg.root);
	
	return *this;
}

void BET::printInfixExpression() //prints out the infix expression
{
//	cout << "NON-Helper INFIX PRINT " << endl;
//	cout << "top node" << this->root->Data << endl;
	printInfixExpression(this->root);
//	cout << "INFIX CALL COMPLETED!!!!" << endl;
	cout << endl;
}

void BET::printPostfixExpression() //prints out the post fix expression;
{
	if(root != nullptr)
		printPostfixExpression(this->root);
	cout << endl;
}

size_t BET::size() //returns the number of nodes in the tree
{
	return size(this->root);
}

size_t BET::leaf_nodes()//returns number of leaf nodes in the tree
{
	return leaf_nodes(this->root);
}

bool BET::empty()
{
	if(root == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

//PRIVATE MEMBER HELPER FUNCTIONS
//Mehran helped me fix this function specifically 
//in relation to how the function takes into consideration Parenthesis placement
//for the infix notation 
void BET::printInfixExpression(BinaryNode* n)
{
	bool flag = false; 	//start with a false flag which will act as a switch to close a open-ended paren

	if(n != nullptr)//
	{
	//	cout << "Inside Infix OUTTER ifs" << endl;
		if(isOperator(n->Data))//verify that the root node data is an operator
		{
			if(n->left != nullptr && isOperator(n->left->Data))//check to see that n->left is not null and it's data is an operator
			{
				if(precedence(n->left->Data) < precedence(n->Data))//check precedence of the operator which determines parenthesis placement
				{
					cout << "( ";
					flag = true;
				}	
			}
		}	
		printInfixExpression(n->left);	//recursive function which will repeatedly make the same call above multiple times till it breaks out and empties the stck 
			

		if(flag)//if the flag is true then close paren then set closing parenthesis then reset the flag to false
		{
			cout << ") ";
			flag = false;
		}
	
		
		cout << n->Data << " ";//print out current "root" node

		if(isOperator(n->Data))//repeat of what was done on the left but for the right side
		{
			if(n->right != nullptr && isOperator(n->right->Data))
			{
				if(precedence(n->right->Data) <= precedence(n->Data))//<= because of the precedence on the interior allows it to open and close
				{
					cout << "( ";
					flag = true;
				}	
			}
		}
		printInfixExpression(n->right);

		if(flag)
		{
			cout << ") ";
			flag = false;
		}			
	}
}

void BET::makeEmpty(BinaryNode* &t)
{
	if(t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	
	t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode* t)
{
	if(t != nullptr)
	{
		return new BinaryNode(t->Data, clone(t->left), clone(t->right));
	}
	else 
		return nullptr;
}
		
void BET::printPostfixExpression(BinaryNode* n)
{
	if(n != nullptr)
	{
		printPostfixExpression(n->left);
		printPostfixExpression(n->right);
		cout << n->Data << " ";
	}
	
}

size_t BET::size(BinaryNode* t)
{
	if(t == nullptr)
	{
		//return 0 if the rot node is not Instantiated
		//i.e., the root node == null
		return 0;
	}
/*	else if(t->left == nullptr && t->right == nullptr)
	{
		//return 1 if both right and left nodes of equal to null then return 1
		//i.e., add 1;
		return 1;
	}*/
	else	
		//this is the recursive call for the size function
		//basically, the return will add the recursive calls for both the left and right
		//side of the size function
		//these calls will continue to run until the else-if statement is reached
		return (size(t->left) + size(t->right)) + 1;


/*	if(t != 0)
	{
		size(t->left);
		size(t->right);
		treeSize++;
	}
	return treeSize;*/

}

size_t BET::leaf_nodes(BinaryNode* t)
{	
	//check to see if t is null
	if(t != 0)
	{	
		//if t->left and right are null return 1
		if(t->left == nullptr && t->right == nullptr)
		{
			return 1;
		}	
	}
	return leaf_nodes(t->left) + leaf_nodes(t->right);
	//this function returns a recursive call(s) to both right and left and then adds the 
	//results together to determine the number of leaf nodes
	//depending on the size of the tree each recursive call will return a 1 for each function for a 
	//maximum of 2 per call which will then continue for the duration of the run 
}


//ADDITIONAL HELPER FUNCTIONS
//initializer function for constructors
void BET::init()
{
	root = nullptr;
	treeSize = 0;
	leaves = 0;
}


bool BET::isOperand(string arg) const
{
	if(isdigit(arg[0]) || isalpha(arg[0]))
		return true;
	
	return false;
}

bool BET::isOperator(string arg) const
{
	if(arg == "+" || arg == "-" || arg == "*" || arg == "/")
	{
		return true;
	}

	
	return false;
}



int BET::precedence(string arg) const
{
	if(arg == "/" || arg ==  "*")
	{
		return 2;
	}
	else
	{
		return 1;
	}
}






	
