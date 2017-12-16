#include "passserver.h"


using namespace cop4530;

void Menu();

int main()
{

	//declare the variables
	size_t size;
	char input;
	string user;
	char fileName[25];
	string newPassword;	


	//create new user pair
	pair<string, string> newUser;
	pair<string, string> cP;

	//ask user for capacity
	cout << "Hello." << endl;
	cout << "Please Enter preferred hash table capacity: ";
	cin >> size;

	while(cin.fail())
	{
		cout << "Not a valid type for the size... enter a integer" << endl;
		cin.clear();//clear error flag on cin so further input/output ops work
		cin.ignore(100, '\n');//will move to the newline to remove potential invalid type from the input stream;
		cin >> size;
	}

	//instantiate PassServer object
	PassServer hT(size);

	do
	{
		Menu();						
		cin >> input;			
		cout << endl;

		switch(input)
		{
			case 'l':
				//ask user to input file name;
				cout << "Please enter a file name: ";
				cin >> fileName;												
				//call the load function	
				hT.load(fileName);
				break;

			case 'a':	
				//ask for necessary input from user
				cout << "Please enter new userName: ";
				cin >> newUser.first;

				cout << "Now, enter his/her new password: ";
				cin >> newUser.second;

				//check the success of adding user
				if(hT.addUser(newUser))
				{
					cout << "User successfully added!" << endl;
				}
				else
				{
					cout << "user addition was unsuccessful!" << endl;
				}

				break;

			case 'r':
				//ask for what user to remove
				cout << "Please enter User name you'd like to remove: ";
				cin >> user;
				
				//determine the success of the removal
				if(hT.removeUser(user))
					cout << "Removal successful!" << endl;
				else 
				{
					cout << "Failed to remove user, please try again." << endl;
				}

				break;

			case 'c':
				//ask for current user
				cout << "Please enter username: ";
				cin >> cP.first;				

				cout << "Now, enter the current password: ";
				cin >> cP.second;
				cout << endl;
					
				//promote the user to update password			
				cout << "Please enter in a new updated password: ";
				cin >> newPassword;	

				//check the success of the change 
				if(hT.changePassword(cP,newPassword))
				{
					cout << "Password change successful!" << endl;
				}
				else
					cout << "Password change FAILED" << endl;
				break;

			case 'f':
				//please enter username
				cout << "Please enter a username: ";				
				cin >> user;

				if(hT.find(user))
				{
					cout << "User found!" << endl;
				}
				else
					cout << "User not found yo..." << endl;
				break;

			case 'd':
				hT.dump();				
				break;

			case 's':
				cout << "The size of the table is: " << hT.size() << endl;
				break;

			case 'w':
				//ask for a filename
				cout << "Please enter a file name you would like to load to the table: ";
				//get fileName
				cin >> fileName;	
				cout << endl;			

				if(hT.write_to_file(fileName))
				{
					cout << "Hash_table written to file succesfully!" << endl;
				}
				else
					cout << "Hash_table \"write_to_file\" attempt FAILED" << endl;

				break;

			case 'x':
				cout << endl;
				break;

			default:
				cout << "Invalid input, please provide a valid input" << endl;
		}

	}while(input != 'x');
	
	return 0;
}


void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";

}
