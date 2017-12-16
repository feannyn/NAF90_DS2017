#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"

using namespace cop4530;


//does this need to be templated ? 
class PassServer
{
	protected:
		HashTable<string, string> store;

	public:
		PassServer(size_t size = 101);
		~PassServer();
		bool load(const char *filename);
		bool addUser(std::pair<string,  string> & kv);
		bool addUser(std::pair<string, string> && kv);	
		bool removeUser(const string & k);
		bool changePassword(const pair<string, string> &p, const string & newpassword);
		bool find(const string & user);
		void dump();
		size_t size();
		bool write_to_file(const char *filename);
	
	private:
		string encrypt(const string & str);

};

//#include "passserver.cpp"

#endif
