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




/******************** SONIA SECTION ********************/

/*
 *  node<Member> **Members;                                         // member hash table
 int members_size;                                                       // size of member hash table

 node<Provider> **Providers;                                     // provider hash table
 int providers_size;                                                     // size of provider hash table

//std::vector<Service> ProviderDirectory
node<Service> **ProviderDirectory;                      // provider directory hash table
int prov_dir_size;
*/
// Constructor with arguments
Database::Database(int size_members, int size_providers, int size_prov_dir)
{
	members_size = size_members;
	providers_size = size_providers;
	prov_dir_size = size_prov_dir;

	Members = new node<Member>*[members_size];
	Providers = new node<Provider>*[providers_size];	
	ProviderDirectory = new node<Service>*[prov_dir_size];

	for (int i = 0; i < members_size; ++i)
		Members[i] = nullptr;

	for (int i = 0; i < providers_size; ++i)
		Providers[i] = nullptr;

	for (int i = 0; i < prov_dir_size; ++i)
		ProviderDirectory[i] = nullptr;

	read_from_file();
	// vector for provided services is automattically intialized 
}

// Destructor
Database::~Database()
{
	write_to_file(); // adding new data / updated data into DB

	// templated remove all function in .h file
	remove_all(Members, members_size);
	remove_all(Providers, providers_size);
	remove_all(ProviderDirectory, prov_dir_size);

	ProvidedServices.clear();
}



void Database::read_from_file()
{
	bool mem, pro, dir, record;

	mem = load_member_data();
	pro = load_provider_data();
	dir = load_provider_directory_data();
	record = load_provided_service_data();

	void write_to_file();

	if (!mem || !pro || !dir || !record)
		cerr << "\nerror." << endl;	
}



void Database::write_to_file()
{

}

/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     MEMBER DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


// Loading data from database into hash 
// tables. This is done at the beginning of every program.
bool Database::load_member_data()
{
	ifstream file_in("members.txt");
	if (!file_in)
	{
		cerr << "\ncould not open file.\n";
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM MEMBER DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	Member to_add;
	string line;

	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		string name_tmp;
		int number_tmp;
		string street_add_tmp;
		string city_tmp;
		string state_tmp;
		int zip_code_tmp;
		string status_tmp;

		// number (1)
		getline(ss, temp, '|');
		number_tmp = stoi(temp);
		to_add.set_number(number_tmp);

		// name (2nd)
		getline(ss, name_tmp, '|');
		to_add.set_name(name_tmp);

		// street (3rd)
		getline(ss, street_add_tmp, '|');
		to_add.get_address().street_addr = street_add_tmp;

		// city (4th)
		getline(ss, city_tmp, '|');
		to_add.get_address().city = city_tmp;

		// state (5th)
		getline(ss, state_tmp, '|');
		to_add.get_address().state = state_tmp;

		// zip (6th)
		getline(ss, temp, '|');
		zip_code_tmp = stoi(temp);
		to_add.get_address().zip_code = zip_code_tmp;

		// status (7th, no delimtier)
		getline(ss, status_tmp);
		to_add.set_status(status_tmp);

		// insert
		add_member(to_add);
	}

	return true;
}

// adding member to hash table
void Database::add_member(Member & to_add)
{	
	add_to_table(Members, members_size, to_add);
}


// updating a member in the hash table & DB
void Database::update_member(int member_number)
{


}

// deleting member from hash table & DB
void Database::delete_member(int member_number)
{
}




/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *		     PROVIDER DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


// loading in provider data from file
bool Database::load_provider_data()
{
	ifstream file_in("providers.txt");
	if (!file_in)
	{
		cerr << "could not open providers.txt\n";
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING FROM PROVIDER DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	string line;
	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		Provider to_add;

		//provider number
		getline(ss, temp, '|');
		to_add.set_number(stoi(temp));

		// name
		getline(ss, temp, '|');
		to_add.set_name(temp);

		// street
		getline(ss, temp, '|');
		to_add.get_address().street_addr = temp;

		// city
		getline(ss, temp, '|');
		to_add.get_address().city = temp;

		// state
		getline(ss, temp, '|');
		to_add.get_address().state = temp;

		// zip
		getline(ss, temp, '|');
		to_add.get_address().zip_code = stoi(temp);

		// service list (comma)
		string services_tmp;
		getline(ss, services_tmp); // last field, no delimiter needed

		// clear old vector 
		to_add.clear_services();

		if (!services_tmp.empty())
		{
			stringstream _service(services_tmp);
			string code;

			while (getline(_service, code, ','))
			{
				if (!code.empty())
					to_add.add_service(stoi(code));
			}
		}

		// store into hash table
		add_provider(to_add);
	}

	return true;
}


// adding provider data into hash table / DB
void Database::add_provider(Provider &to_add)
{
	add_to_table(Providers, providers_size, to_add);
}

// updating certain provider in hash table / DB
void Database::update_provider(int provider_number)
{
}

// delete certain provider
void Database::delete_provider(int provider_number)
{
}



/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *	        PROVIDER DIRECTORY DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/


// loading in provider directory data into HT from DB
bool Database::load_provider_directory_data()
{
	ifstream file_in("providerdirectory.txt");
	if (!file_in)
	{
		cerr << "\ncould not open file." << endl;
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING PROVIDER DIRECTORY DATABASE ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	string line;
	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		Service to_add;

		// service code
		getline(ss, temp, '|');
		to_add.set_code(stoi(temp));

		// service name
		getline(ss, temp, '|');
		to_add.set_name(temp);

		// fee
		getline(ss, temp, '|');
		to_add.set_fee(stof(temp));

		// insert into hash table
		add_service(to_add);
	}

	return true;
}

// adding service data into hash table 
void Database::add_service(Service &to_add)
{
	add_to_table(ProviderDirectory, prov_dir_size, to_add);
}


// getting info about a service based on number 
void Database::get_service_data(int service_number, Service& copy)
{
	Service *found = find(ProviderDirectory, prov_dir_size, service_number);

	if (!found)
	{
		cerr << "\nservice not found.\n" << endl;
		return;
	}

	copy = *(found); // deference found to copy contents
}


/***************☆*: .｡. o(≧▽≦)o .｡.:*☆**************
 *
 *	        RECORDED SERVICES DATA
 *
 * **************☆*: .｡. o(≧▽≦)o .｡.:*☆*************/



// Loading in past services data into HT  
bool Database::load_provided_service_data()
{
	ifstream file_in("providedservices.txt");
	if (!file_in)
	{
		cerr << "Could not open providedservices.txt\n";
		return false;
	}

	cout << "☆*: .｡. o(≧▽≦)o .｡.:*☆ LOADING PROVIDED SERVICES ☆*: .｡. o(≧▽≦)o .｡.:*☆\n";

	string line;
	while (getline(file_in, line))
	{
		if (line.empty()) continue;

		stringstream ss(line);
		string temp;

		ProvidedService to_add;

		// current date/time
		getline(ss, to_add.current_date_time, '|');

		// service date/time
		getline(ss, to_add.service_data_time, '|');

		// provider number
		getline(ss, temp, '|');
		to_add.provider_number = stoi(temp);

		// member number
		getline(ss, temp, '|');
		to_add.member_number = stoi(temp);

		// service code
		getline(ss, temp, '|');
		to_add.service_code = stoi(temp);

		// comments (full rest of line)
		getline(ss, to_add.comments);

		ProvidedServices.push_back(to_add);
	}

	return true;
}




// Adding to the vector
void Database::record_provided_service(ProvidedService &to_add)
{
	ProvidedServices.push_back(to_add);
}





void Database::display_members()
{
	display(Members,members_size);
}
void Database::display_providers()
{
	display(Providers,providers_size);

}
void Database::display_prov_dir()
{
	display(ProviderDirectory,prov_dir_size);
}


/******************** SONIA SECTION ********************/










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
