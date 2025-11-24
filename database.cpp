#include <iostream>
#include <cstdlib>
#include <ctime>
#include "database.h"
using namespace std;
/*******************************************************************************
  Chocoholics CS314 Program
Names: Sonia Nath, Yollaine Brooks,
Description of Program:
 *********************************************************************************/


// Constructor with arguments
Database::Database(int size_members, int size_providers, int size_prov_dir)
{
	Members = new node<Member>*[members_size];
	Providers = new node<Provider>*[size_providers];	
	ProviderDirectory = new node<Service>*[size_prov_dir];

	for (int i = 0; i < size_members; ++i)
		Members[i] = nullptr;

	for (int i = 0; i < size_providers; ++i)
		Providers[i] = nullptr;

	for (int i = 0; i < size_prov_dir; ++i)
		ProviderDirectory[i] = nullptr;

	// vector for provided services is automattically intialized 
}

// Destructor
Database::~Database()
{
	remove_all(Members);
	remove_all(Providers);
	remove_all(ProviderDirectory);
	ProvidedServices.clear();
}


void Database::remove_all(node<Member> **Members) 
{ return; }
void Database::remove_all(node<Provider> **Providers) 
{ return; }
void Database::remove_all(node<Service> **ProviderDirectory) 
{ return; }




// Loading data from database into hash 
// tables. This is done at the beginning of every program.
bool Database::load_member_data()
{
	ifstream file_in; //fstream variable for reading in
	Member to_add;
	std::string name_tmp;
	int number_tmp;
	std::string street_add_tmp;
	std::string city_tmp;
	std::string state_tmp;
	int zip_code_tmp;
	std::string status_tmp;

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆" << endl;

	file_in.open("member.txt");
	if (!file_in)
	{
		cerr << "\ncould not open file." << endl;
		return false;
	}


	// first attempt to reach 
	file_in >> name_tmp;	
	to_add.set_name(name_tmp);
	file_in.ignore(100, '|');

	while (file_in && !file_in.eof())
	{ 
		// digit 
		file_in >> number_tmp;
		to_add.set_number(number_tmp);
		file_in.ignore(100, '|');

		// getting address
		file_in >> street_add_tmp;
		to_add.get_address().street_addr = street_add_tmp;
		file_in.ignore(100, '|');

		file_in >> city_tmp;
		to_add.get_address().city = city_tmp;
		file_in.ignore(100, '|');

		file_in >> state_tmp;
		to_add.get_address().state = state_tmp;
		file_in.ignore(100, '|');

		file_in >> zip_code_tmp;
		to_add.get_address().zip_code = zip_code_tmp;
		file_in.ignore(100, '|');

		// status 
		file_in >> status_tmp;
		to_add.set_status(status_tmp);


		add_member(to_add); // adding member into the hash table

		// get data member	
		file_in >> name_tmp;    
		to_add.set_name(name_tmp);
		file_in.ignore(100, '|');
	}

	return true;
}

// Sonia
void Database::add_member(Member & to_add)
{	
	// random number as key
	int index = hash_function(to_add.get_number());
	
	node<Member>* new_member = new node<Member>(to_add);

		if (!Members[index])
			Members[index] = new_member;
		else // just adding at beginnging so no recurisve 
		{
			new_member->next = Members[index];
			Members[index] = new_member;
		}
	return;
}


// Sonia
void Database::update_member(int member_number)
{
}

//Sonia
void Database::delete_member(int member_number)
{
}

// Sonia
void Database::add_provider(Provider &)
{
}

//Sonia
void Database::update_provider(int provider_number)
{
}

//Sonia
void Database::delete_provider(int provider_number)
{
}

// Sonia
void Database::record_provided_service(ProvidedService &)
{
}


void Database::get_service_data(int service_number, Service& copy)
{
}

void Database::generate_weekly_report()
{
}

void Database::verify_member(int member_number)
{
}

void Database::verify_provider(int provider_number)
{
}

void Database::verify_service(int service_number)
{
}

// Yasmine
int Database::hash_function(int key_value)
{
	return 0;
}
