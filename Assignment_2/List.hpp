//Nicholas Feanny; Naf16b;

using namespace std;

//helper const iterator constructor (1 parameter)
template<typename T>
List<T>::const_iterator::const_iterator(Node* p )
{
	current = p;
}

//helper function retrieve
template<typename T>
T& List<T>::const_iterator::retrieve() const
{
	//if I understand this correctly all this does is retrieve the data from the current
	//Node
	return this->current->data;
}

template<typename T>
List<T>::const_iterator::const_iterator()// default zero parameter constructor
{
	current = nullptr;
}
template<typename T>
const T& List<T>::const_iterator::operator*() const // operator*() to return element
{
	return retrieve();
}

// increment/decrement operators
template<typename T>//pre increment
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
	this->current = this->current->next;//set calling object current to current's next
	return *this;//dereferenced current to access next 
						 //which is a node pointer and is holding an address
						 // of the next node 
						 // it must be dereferenced to access it's data

}

template<typename T>//post increment
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
	auto temp = *this;//auto is representative of the return value
					 //so you do not have to type it out
	this->current = this->current->next;
	return temp ;
}

template<typename T>//pre decrement 
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
	this->current = this->current->prev;//set calling object current to current's next
	return *this;//dereferenced current to access next 
						 //which is a node pointer and is holding an address
						 // of the next node 
						 // it must be dereferenced to access it's data
}

template<typename T>//post decrement
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
	auto temp = *this;//auto is representative of the return value
					 //so you do not have to type it out
					 //List<T>::const_iterator& (the return)
	this->current = this->current->prev;//alternatively --(*this)
	return temp ;
}

// comparison operators
template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{
	//compare the data of the calling object and the argument object passed in
	if(current == rhs.current)
	{
		return true;
	}

	return false;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
	//compare the data of the calling object and the argument object passed in
	if(current != rhs.current)
	{
		return true;
	}

	return false;


	//return !(this->current->data  == rhs.current ->rhs.data);

}



//Iterator class function definitions

template<typename T>
List<T>::iterator::iterator() : const_iterator()
{
	
}

//protected 1-parameter constructor (iterator class)
template<typename T>
List<T>::iterator::iterator(Node *p) : const_iterator(p)
{
	
}

template<typename T>
T&  List<T>::iterator::operator*()
{
	//use the scoper resolution mechanics to clarify where the retrieve function is
	//coming from
	//scope resoluton operator is used by a derived class 
	//in order to determine the specific class a method/ memeber data belongs to 

	return const_iterator::retrieve();
}

template<typename T>
const T&  List<T>::iterator::operator*() const
{
	return const_iterator::operator*();
}

// increment/decrement operators
template<typename T>
typename List<T>::iterator&  List<T>::iterator::operator++()
{
	this->current = this->current->next;
	return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
	auto temp = this->current;
	this->current = this->current->next;
	return temp;	
}

template<typename T>
typename List<T>::iterator&  List<T>::iterator::operator--()
{
	this->current = this->current->prev;
	return this->current;	
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
	auto temp = this->current;
	this->current = this->current->next;
	return temp;
}


//LIST CLASS DEFINITIONS
// constructor, desctructor, copy constructoList();       

//init() helper function definition
template<typename T>
void List<T>::init()
{
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
	tail->next = nullptr;
	head->prev = nullptr;

}

template<typename T>         
List<T>::List() // default zero parameter constructor
{
	init();	
}

template<typename T>
List<T>::List(const List &rhs)   // copy constructor
{

	if(this != &rhs)
	{
		Node* holder = head->next;
		Node* rhsHolder = rhs.head->next;
		theSize = rhs.theSize;
		head = rhs.head;
		tail = rhs.tail;

		for(int i = 0; i < theSize; i++)
		{
			holder = rhsHolder;
			holder = holder->next;
			rhsHolder = rhsHolder->next;
		}	
	}	
}

template<typename T>
List<T>::List(List && rhs)       // move constructor
{
	theSize = rhs.theSize;
	head = rhs.head;
	tail = rhs.tail;

	rhs.theSize = 0;	
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

// num elements with value of val
template<typename T>
 List<T>::List(int num, const T& val)
{
	init();	
	
	for(int i = 0; i < num; i++)
	{				
		push_back(val);	
	}	
}

// constructs with elements [start, end)
template<typename T>
List<T>::List(const_iterator start, const_iterator end) 
{
	init();
	for(start; start != end; ++start)
	{
			
		push_back(*start);

	}

	//	tail->next = nullptr;

}

// constructs with a copy of each of the elements in the initalizer_list
template<typename T>
List<T>::List (std::initializer_list<T> iList)
{
	init();


	int i = 0;

	for(T x : iList)
	{
		push_back(x);
	}	

}

template<typename T>
List<T>::~List() // destructor
{
	clear();
	delete head;
	delete tail;
}

// copy assignment operator
template<typename T>
const List<T>& List<T>::operator=(const List &rhs)
{	
	if(this != &rhs)
	{
		Node* holder = head->next;
		Node* rhsHolder = rhs.head->next;
		theSize = rhs.theSize;
		head = rhs.head;
		tail = rhs.tail;

		for(int i = 0; i < theSize; i++)
		{
			holder = rhsHolder;
			holder = holder->next;
			rhsHolder = rhsHolder->next;
		}	
	}

	return *this;
}

// move assignment operator
template<typename T>
List<T>& List<T>::operator=(List && rhs)
{
	//create temp variables to hold the address/values of calling object
	int tempSize = theSize;
	Node* tempHead = head;
	Node* tempTail = tail;

	// assign data of right side to left side
	theSize = rhs.theSize;
	head = rhs.head;
	tail = rhs.tail;
	
	//assign right side garabage data
	rhs.theSize = tempSize;
	rhs.head = tempHead;
	rhs.tail = tempTail;

	return *this;
}

// sets list to the elements of the initializer_list
template<typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList)
{
	clear();
 	
	int i = 0;
	for(T x: iList)
	{
		push_back(x);
	}

	return *this;
 	
}

// member functions
template<typename T>
int  List<T>::size() const       // number of elements
{
	return theSize;
}

template<typename T>
bool  List<T>::empty() const     // check if list is empty
{
	if(theSize == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
void  List<T>::clear()           // delete all elements
{
	if(!empty())
	{
		while(!empty())
		{
			pop_back();
		}
		
	}	
}

template<typename T>
void  List<T>::reverse()         // reverse the order of the elements
{
	
	Node* current;
	Node* holder;
	Node* spike;

	current = head;

	while(current != head->next)
	{
		holder = current->next;
		current->next = current->prev;
		current->prev = holder;

		current = holder;
	}
		
	spike = head;
	head = tail;
	tail = spike;


}
//FOR THE NEXT 4 FUNCTION DO WE 
template<typename T>
T&  List<T>::front()             // reference to the first element
{
	return head->next;
}

template<typename T>
const T&  List<T>::front() const
{
	return head->next;
}

template<typename T>
T&  List<T>::back()              // reference to the last element
{
	return tail->prev;
}

template<typename T>
const T&  List<T>::back() const
{
	return tail->prev;
}

template<typename T>
void  List<T>::push_front(const T & val) // insert to the beginning
{
	iterator iter(head);
	insert(iter, val);
}

template<typename T>
void  List<T>::push_front(T && val)      // move version of insert
{	
	insert(begin() ,std::move(val));
}

template<typename T>
void  List<T>::push_back(const T & val)  // insert to the end
{
	iterator itr(tail->prev);
	insert(itr, val);
}

template<typename T>
void  List<T>::push_back(T && val)       // move version of insert
{
	iterator itr(tail->prev);
	insert(itr, std::move(val));
}

template<typename T>
void  List<T>::pop_front()               // delete first element
{
	iterator iter(head->next);
	erase(iter);	
}

template<typename T>
void  List<T>::pop_back()                // delete last element
{
	iterator iter(tail->prev);
	erase(iter);
}

template<typename T>
void  List<T>::remove(const T &val)      // remove all elements with value = val
{

	for(auto itr = begin(); itr != end();)
	{
		if(*itr == val)
		{
			itr = erase(itr);
		}
		else
			itr++;
	}

}

//This is weird.......
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)	// remove all elements for which Predicate pred
						//  returns true. pred can take in a function object
{
//	typename List<T>::iterator itr;	
	for(auto itr = begin(); itr != end();)
	{
		
		if(pred(*itr))
		{
			itr = erase(itr);

		}
		else 
		{
			itr++;
		}
	}
}

// print out all elements. ofc is deliminitor
template<typename T>
void List<T>::print(std::ostream& os, char ofc) const 
{
	iterator itr(head->next);

	while(itr != end())
	{
		os << *itr << ofc;
		itr++;
	}
}

template<typename T>
typename List<T>::iterator List<T>::begin()               // iterator to first element
{
	iterator itr(head->next);
//	itr.current = head->next;
	return itr;
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
	const_iterator itr(head->next);
//	itr.current = head->next;
	return itr;
}

template<typename T>
typename List<T>::iterator List<T>::end()                 // end marker iterator
{
	iterator itr;
	itr.current = tail;
	return itr;
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
	const_iterator itr;
	itr.current = tail;
//	cout << *itr << "tail value" << endl;
//	cout << "TAIL PRINTED FAIL" << endl;
	return itr;
}

template<typename T>
typename List<T>::iterator  List<T>::insert(iterator itr, const T& val)  // insert val ahead of itr
{
	//create new node
	Node* newNode = new Node;
	Node* actual = itr.current;
	iterator x(actual);
	
	//set the value
	newNode->data = val;

	//set the new Node's next and prev to the appropriate positions
	newNode->next = actual->next;
	newNode->prev = actual->next->prev;

	//now set the pointers of the already existing nodes to the new new appropriately 
	actual->next = newNode;
	newNode->next->prev = newNode;


	//increment size
	++theSize;

	return x;
}

template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)      // move version of insert
{
	//create new node
	Node* newNode = new Node;

	Node* actual = itr.current;	

	iterator x(actual);		

	//set the value using std::swap
	std::swap(newNode->data, val);

	//set the new Node's next and prev to the appropriate positions
	newNode->next = actual->next;
	newNode->prev = actual->next->prev;

	//now set the pointers of the already existing nodes to the new new appropriately 
	actual->next = newNode;
	newNode->next->prev = newNode;

	//increment size
	++theSize;

	return x;

}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr)                 // erase one element
{
	//declare new Node and return 
	Node* actual = itr.current;
	iterator x(actual->next);

	//set the previous and next node of itr equal to each other
	actual->prev->next = actual->next;
	actual->next->prev = actual->prev;

	//set current's pointers to null
	actual->next = nullptr;
	actual->prev = nullptr;
	
	
	//remove the node
	delete itr.current;

	//decrement size;
	--theSize;
;

	return x;
}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) // erase [start, end)
{
	
	iterator x;	

	for(x = start; x != end;)//why no increment here ????
	{
		x = erase(x);
	}

	return end;
}

// overloading comparison operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
	//instantiate the iterators here(figure out the syntax)
	auto rIter = rhs.begin();
	auto lIter = lhs.begin();
	
	if(lhs.size() != rhs.size())
	{
		return false;
	}
	else
	{
		for(rIter; rIter != rhs.end(); rIter++)
		{
			if(*rIter != *lIter)
			{
				return false;
			}
			lIter++;	
		}
	}

	return true;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
	return !(lhs == rhs);
}

// overloading output operator
template <typename T>
std::ostream &  operator<<(std::ostream &os, const List<T> &l)
{
	l.print(os);
	return os;
}

