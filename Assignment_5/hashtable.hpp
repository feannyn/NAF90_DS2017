//Nicholas Feanny;naf16b;

template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size)//one parameter constructor
{
	table.resize(prime_below(size));
	current = 0;	
}

template<typename K, typename V>
HashTable<K, V>::~HashTable()//destructor 
{
	clear();
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K & k)//check if k is in hash table
{

	//hash the key to obtain the index to look in
	size_t  index = myhash(k);
	
	//typename vector<list<pair<K, V>>>::iterator& itr-- equivalent terator below V
	for(auto itr = table[index].begin(); itr != table[index].end(); itr++) 
	{
		if(itr->first == k)
		{
			return true;
		}	
	}

	return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv)//check is KV pair is in table
{
	if(contains(kv.first))
	{
		for(auto & itr : table[myhash(kv.first)])
		{
			if(itr == kv)
			{
				return true;
			}
		}
	}	

	return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> & kv)//adds kv pair into table
{
	//call hash function
	size_t pos = myhash(kv.first);

	//check to verify kv pair is not duplicated
	for(auto itr = table[pos].begin(); itr != table[pos].end(); itr++)	
	{
		if(itr->first == kv.first)
		{
			if(itr->second != kv.second)
			{
				itr->second = kv.second;
				return true;
			}
			else if(itr->second == kv.second)
				return false;
		}		
	}

//	++current;

	//increment current from the start then check if rehash is necessary
	if(++current > table.size())
	{
		//rehash the function if deemed necessary 	
		rehash();
		current += 1;
	}

	//push_back kv_pair
	table[pos].push_back(kv);	

	return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(pair<K,  V> && kv)//move variant of insert
{
	//call hash function
	size_t pos = myhash(kv.first);

	//check to verify kv pair is not duplicated
	for(auto itr = table[pos].begin(); itr != table[pos].end(); itr++)	
	{
		if(itr->first == kv.first)
		{
			if(itr->second != kv.second)
			{
				//move variant of updating the second data value of kv argument being passed in
				//essentially, 
				itr->second = std::move(kv.second);
				return true;
			}
			else if(itr->second == kv.second)
				return false;
		}		
	}
	
//	++current;

	//rehash the function if deemed necessary 	
	if(++current > table.size())
	{
		rehash();
		current += 1;
	}
	//push_back kv_pair
	table[pos].push_back(std::move(kv));	

	return true;

}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K & k)//removes kv pair from the table
{
	size_t index = myhash(k);


	//cnver to ranged bsaed if possible
	for(auto itr = table[index].begin(); itr != table[index].end(); itr++)
	{
		if(itr->first == k)
		{	
			table[index].erase(itr);
			current--;
			return true;
		}
	}

	return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear()//delete all elements in the hash table
{
	makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename)//load the content of the file into table
{
	//declare filestream object and open the file
	ifstream fin;
	fin.open(filename);

	//create a pair holder variable
	pair<K, V> hp;

	//make sure the file opens properly
	if(!fin)
	{
		cerr << "Attempt to open the file failed" << endl;
		return false;
	}

	while(fin.good())
	{	
		//store the cstrings into 
		fin >> hp.first >> hp.second;
	//	fin.ignore(); //get rid of that newline my guy

		//insert function call here
		//this increments size, rehashes and inserts the pair
	
		insert(hp);	
	}

	fin.close();	
	return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump()//displays all the entries in the hash table
{
	for(int i = 0; i < table.size(); i++)
	{
		auto itr = table[i].begin();
	
		cout << "v[" << i << "]: ";		

		if(table[i].size() == 1)
		{
			cout << itr->first << " " << itr->second; 
		}
		else if(table[i].size() > 1)
		{
			for(; itr != table[i].end(); itr++)
			{				
				cout << itr->first << " " << itr->second << " : ";
			}
		}

		cout << endl;			
	}
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename)//writes all elements from the table into the file.
{

	//create ofstream variable
	ofstream fout;

	//open the file that fout will be writing to..
	fout.open(filename);

	//basically the same thing as the dump file so just C&P it here and replace cout with fout	
	//with minor tweaks to the format
	for(int i = 0; i < table.size(); i++)
	{
		if(!fout)
		{	
			cerr << "Not a Valid File Name" << endl;
			return false;
		}
		else
		{			
			for(auto itr = table[i].begin(); itr != table[i].end(); itr++)
			{				
				fout << itr->first << " " << itr->second << endl;
			}
	
						
		}
		fout  << endl;
	}

	fout.close();

	return true;
}

template<typename K, typename V>
size_t HashTable<K, V>::getSize() const
{
	cout << "current: " << current << endl;
	cout << "Table size: " << table.size() << endl;
	return current;
}

//_________________________________helper functions________________________________
template<typename K, typename V>
void HashTable<K, V>::makeEmpty()//deletes all elements in the hashtable
{
	for(int i = 0; i < table.size(); i++)
	{
		table[i].clear();
	}
}

//used textbook example 5.22 page 229 as guidance for this function
template<typename K, typename V>
void HashTable<K, V>::rehash()//Rehash function.
{
	//step 1: create new vector 
	//could use auto here
	//create a new vector
	//use the copy constructor
	vector<list<pair<K, V>>> ht = table;

	//step 2:
	//resize the vector (the original)
	table.resize(prime_below(table.size() * 2));	

	//step 3: clear the the old list
	//will iterate through the vector and clear each list at each index
	for(auto & itr : table)
		itr.clear();

	//step 4:
	//set size back to zero because the size will be iterated in insert
	//(do not want to double the size of the table)
	current = 0;

	//step 5:
	//start transferring data from holder table to resized and updated table
	for(int i = 0; i < ht.size(); i++)
	{
		for(auto & LDI : ht[i])
		//step 7: insert data into the resized table
		//insert increments current; rehashes when necessary; and hashes the key values
		//use std::move because the data limits are r values not l values;
		insert(std::move(LDI));
				
	}
	
		
}	


template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k)//return the index of the vector entry where kstored
//two functions used to find the prime number used in setting up the vector.
{
	//size is off by 1 because its not putting in the correct size
	static hash<K> hf;
	return hf(k) % table.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

