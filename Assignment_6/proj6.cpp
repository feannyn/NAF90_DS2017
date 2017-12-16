//Nicholas Feanny; Naf16b; COP4530

//preprocessor directives
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cctype>
#include <map>
#include <ctime>
#include <set>
#include <iterator>
#include <vector>

//using statements
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::iterator;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::pair;
using std::map;
using std::endl;
using std::next;
using std::sort;
using std::set;
using std::vector;


//__________________FUNCTION PROTOTYPES_________________//
void digitPuncWord(map<string, int>& words, map<string, int>& chars, map<string, int>& num, string& in, int x, string& build);
void builtString(map<string, int>& store_2, string& s, int y, string& toBeBuilt);
void builtChar(map<string, int>& store_chars, string& ch, int& r);
void print(vector<pair<string, int>>& vect, string str);
vector<pair<string, int>>& sortMap(map<string, int>& pre, vector<pair<string, int>>& trade);
bool sortByValue(const pair<string, int> &x, const pair<string, int> &y);

//___________________MAIN____________________//
int main()
{
	//declarations
	string indie;//each individual string;(stands for individual)
	string total;//string with will be concatenated to 
	int newLineCount = 0;
	
	//instantiate map for characters, words, and numbers
	map<string, int> word;
	map<string, int> character;
	map<string, int> number;
	
	//instantiate the sets will hold the sort values of the map
	vector<pair<string, int>> wordVec;
	vector<pair<string, int>> characterVec;
	vector<pair<string, int>> numberVec;

	//capture time prior to the main loop
	clock_t origin = clock();

	while(getline(cin, indie))	
	{
		//because getline eats the newline by default 
		//create a counter for each iteration of the loop 
		//once complete hard code a newline into the character array then sort
		newLineCount++;	
	
		for(int i = 0;i < indie.size(); ++ i)
		{	
			digitPuncWord(word, character, number, indie, i, total);	
		}
	
	}//end of while loop
	origin = clock() - origin;

//	characterVec.push_back(pair<string, int>("\\n",newLineCount));
	character.insert(pair<string, int>("\n", newLineCount));
	characterVec = sortMap(character, characterVec);
	wordVec = sortMap(word, wordVec);			
	numberVec = sortMap(number, numberVec);

	print(characterVec, "characters");
	print(wordVec, "words");
	print(numberVec, "numbers");	
	
	return 0;
}

//__________________FUNCTION DEFINITIONS_________________//

void digitPuncWord(map<string, int>& words, map<string, int>& chars, map<string, int>& num, string& in, int x, string& build)//map, the string processed, loop iteration
{
	
	builtChar(chars, in, x);	

	//once stored into the char map, convert the characters to lower case for word map
	in[x] = tolower(in[x]);
		
	//holder string for the string being built through each iteration		
	if(!ispunct(in[x]) && !isspace(in[x]))
		build += in[x];		

	if(isalpha(in[x]))
	{		
		if(!isalpha(in[x + 1]) || in[x + 1] == '\0')
		{
			builtString(words, in, x, build);	
		}
	}
	if(isdigit(in[x]))
	{
		if(!isdigit(in[x + 1]) || in[x + 1] == '\0')
		{
			builtString(num, in, x, build);
		}	
	}	
}

//takes the built string and stores it in it's respective map if it does not exist/ else it will increment it's value by 1
void builtString(map<string, int>& store_2, string& s, int y, string& toBeBuilt)
{	
	if(store_2.count(toBeBuilt) > 0)
	{
		store_2[toBeBuilt]++;
		toBeBuilt.erase();
	}
	else
	{
		store_2.insert(pair<string, int>(toBeBuilt, 1));
		toBeBuilt.erase();
	}		
}
//This function will store individual characters into the character map
void builtChar(map<string, int>& store_char, string& ch, int& r)
{
	string hold{ch[r]};

	//store the individual char into a string object by instantiating the 
	//string object with a single char 
		

	if(store_char.count(hold) > 0)//if the character is already a key in the map, then just increment its value
		store_char[hold]++;
	else //else create a new key value pair
		store_char.insert(pair<string, int>(hold, 1));

}

//This function will print out the map(s)
void print(vector<pair<string, int>>& vect, string str)
{
	if(vect.size() < 10)
	{
		cout << "Total " << vect.size() << " different " << str << ", " << " most used:" << endl;

		for(int i = 0; i < vect.size(); i++)
		{
			if(vect[i].first.size() == 1)
			{	//VERIFY YOUR CODE HERE TO MAKE THE COUNT IS CORRECT
				if(vect[i].first == "\t")
				{
					cout << "No. "<< i << ":" << "\\t" << '\t' << '\t' << vect[i].second << endl;
				}
				else if(vect[i].first == "\n")
				{
					cout << "No. "<< i << ":" << "\\n" << '\t' << '\t' << vect[i].second << endl;
				}
				else	
					cout << "No. "<< i << ":" << vect[i].first << '\t' << '\t' << '\t' << vect[i].second << endl;
				
			}
			else
				cout << "No. "<< i << ":" << vect[i].first  << '\t' << '\t' << vect[i].second << endl;
	
		}
	}
	else
	{	
		cout << "Total " << vect.size() << " different " << str << ", " << "10 most used:" << endl;

		for(int i = 0; i < 10 ; i++)
		{
			if(vect[i].first.size() == 1)
				cout << "No. "<< i << ":" << vect[i].first  << '\t' << '\t' << '\t' << vect[i].second << endl;
			else	
				cout << "No. "<< i << ":" << vect[i].first  << '\t' << '\t' << vect[i].second << endl;
		}
	}		
}


//This function will return the map sorted from lowest to to highest occurring value
//return by reference so that there is an implicit address to the object
//being returned
vector<pair<string, int>>& sortMap(map<string, int>& pre, vector<pair<string, int>>& trade)
{	
	//store the values of the map into the set
		trade.insert(trade.begin(), pre.begin(), pre.end());


	//CHECK IF THE SIZE OF THE VECTOR IS 1 ie THE CHARACTER ARRAY AND USE THE SORT BY VALUE OPTIONAL PARAMETER!!!!!!!!! if vector at index 1 is greater than 1...
	//sort the values
		
		sort(trade.begin(), trade.end(), sortByValue);
	
		return trade;
}

bool sortByValue(const pair<string, int> &x, const pair<string, int> &y)
{
	if(x.second == y.second)
	{
		return (y.first > x.first);
	}

	return (x.second > y.second);	
}




