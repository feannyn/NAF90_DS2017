#include "passserver.h"

PassServer::PassServer(size_t size) : store(size)//call the store constructor
{
	//pass in the constructor for the hashtable (initialization list)
	//as this is an adaptor class so all it's functions
	//are going to manipulate the inheritant behavior of 
	//class HashTable
}

PassServer::~PassServer() 
{
	//call the store destructor 
	//wrote this so you know whats happening
	//rather than leaving it blank
//	store.~HashTable();
}

bool PassServer::load(const char *filename)
{
	return store.load(filename);
}

bool PassServer::addUser(std::pair<string,  string> & kv)
{
	kv.second = encrypt(kv.second);
	return store.insert(kv);
}

bool PassServer::addUser(std::pair<string, string> && kv)	
{
	kv.second = encrypt(kv.second);
	return store.insert(kv);
}

bool PassServer::removeUser(const string & k)
{
	return store.remove(k);
}


//Raidel Assisted me with this function 11/21/17
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
	//pair not encrypted (p)
	
	//see if what he passed is in the table
	//create temp pair with same user name with encrypted password(temp p.second)
	//once created , match with existing passwod and if matches add new password
	//create new pair and insert into the table


	//step 2: create a temp variable to hold current user with encrypted password
	pair<string, string> holder;//will be used as a temp variable
	holder.first = p.first;//new pair created store the original username
	holder.second = encrypt(p.second);//update 
//	string pSec = encrypt(p.second);		

	

	//step 3: check to verify what is passed in is in the table
	if(store.match(holder))
	{
		pair<string, string> temp;
		temp.first = p.first;
		temp.second = encrypt(newpassword);

		//step 4: verify the passwords are not the same
		if(p.second == newpassword)
		{
			return false;
		}
				
		//insert into table;
		store.insert(temp);			
		return true;
	}
	else
	{
		return false;
	}

}

bool PassServer::find(const string & user)
{
	return store.contains(user);
}

void PassServer::dump()
{
	store.dump();
}

size_t PassServer::size()
{
	return store.getSize();
}

bool PassServer::write_to_file(const char *filename)
{
	return store.write_to_file(filename);
}
	
//________________________PASS SERVER HELPER FUNCTIONS___________________

string PassServer::encrypt(const string & str)
{
  	char salt[] = "$1$########";
  	string key = str;
	char password[34];
  	
	strcpy (password, crypt(key.c_str(), salt));

	return password;
}





