#ifndef HASHTABLE_H
#define HASHTABLE_H

//declare before usage my guy
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <list>
#include <utility>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <crypt.h>
#include <cstring>


using std::string;
using std::vector;
using std::cerr;
using std::list;
using std::hash;
using std::pair;
using std::find;
using std::iterator;
using std::cout;
using std::cin;
using std::endl;
using std::begin;
using std::end;
using std::ofstream;
using std::ifstream;


namespace cop4530
{
	template<typename K, typename V>
	class HashTable
	{
		public:
			HashTable(size_t size = 101);//one parameter constructor
			~HashTable();//destructor 
			bool contains(const K & k);//check if k is in hash table
			bool match(const pair<K, V> &kv);//check is KV pair is in table
			bool insert(const pair<K, V> & kv);//adds kv pair into table
			bool insert (pair<K,  V> && kv);//move variant of insert
			bool remove(const K & k);//removes kv pair from the table
			void clear();//delete all elements in the hash table
			bool load(const char *filename);//load the content of the file into table
			void dump();//displays all the entries in the hash table
			bool write_to_file(const char *filename);//writes all elements from the table into the file.

			size_t getSize() const;//grab the current size of the hashtable

		private:
			//member data
			size_t current;
			vector<list<pair<K, V>>> table;
			

			void makeEmpty();//deletes all elements in the hashtable
			void rehash();//Rehash function.
			size_t myhash(const K &k);//return the index of the vector entry where kstored
			//two functions used to find the prime number used in setting up the vector.
			unsigned long prime_below (unsigned long l);//
			void setPrimes(vector<unsigned long>& sp);

			// max_prime is used by the helpful functions provided
			// to you.
			static const unsigned int max_prime = 1301081;

			// the default_capacity is used if the initial capacity 
			// of the underlying vector of the hash table is zero. 
			static const unsigned int default_capacity = 11;
	};

	#include "hashtable.hpp"	
} //end of namespace

#endif
