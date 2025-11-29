/*******************************************************************************
  Chocoholics CS314 Program: Database Interface
Names: Yollaine Brooks, 
Description of Program: 
 *********************************************************************************/

#pragma once
#include <fstream>
#include "entities.h"
#include "node.h"
using namespace std;


// ProvidedService Struct
struct ProvidedService
{
	std::string current_date_time;	// current date and time
	std::string service_data_time;	// date and time service was provided
	int provider_number;			// provider number
	int member_number;				// member number
	int service_code;				// service code number
	std::string comments = "";		// optional comments
};



// EFTFile
// stores data sent as an EFT in the weekly report
struct EFTFile
{
	std::string provider_name;	// provider's name
	int provider_number;		// provider number
	int transfer_amount;		// fee to be transferred
};


// Service Class
// Holds data from the Provider directory
class Service
{	
	public:
		Service(): name(""), number(0), fee(0.0) {}
		Service(std::string _name, int _code, float _fee) : name(_name), number(_code), fee(_fee) {}

		int get_number() { return number; }
		void set_name(std::string to_add) { name = to_add; }
		void set_fee(float to_add) { fee = to_add; }
		void set_code(int code_to_add) { number = code_to_add; }
		std::string get_name() { return name; }
		float get_fee() { return fee; }
		void display_all() { cout << "\nName: " << name << endl; cout << "Number: " << number << endl; cout << "Fee: " << fee; }

	private:
		std::string name;	// name of the service (max size 20)
		int number;			// 6 digit code
		float fee;			// max of 999.99
};



// Database Class
class Database
{
	public:
		Database(int size_members = 10, int size_providers = 10, 
				int size_prov_dir = 10);							// constructor

		//~Database();													// destructor
		//void load_data();											// load data from file

		~Database();					// destructor

		// read in everything from file. call in menu before starting program
		void read_from_file();

		// write to file with new / updated data. call after user requests to quit program 
		void write_to_file();


		//Member functions
		bool load_member_data();										// load data from file
		bool write_member_data();
		void add_member(Member &);									// add member to the member table
		void update_member(int member_number);						// update specific member based on number
		void delete_member(int member_number);						// delete member based on number

		// Provider functions
		bool load_provider_data();	
		bool write_provider_data();
		void add_provider(Provider &);								// add provider to the provider table
		void update_provider(int provider_number);					// update specific provider based on number
		void delete_provider(int provider_number);					// delete provider based on number

		// Provider directory fucntions	
		bool load_provider_directory_data();
		bool write_provider_directory_data();
		void add_service(Service &);

		// recorded services
		bool load_provided_service_data();
		bool write_provided_service_data();
		void record_provided_service(ProvidedService &);			// insert provided service into table
		void get_service_data(int service_number, Service & copy);	// service to get from Providerdirectory




		void generate_weekly_report();								// create the manager's weekly report
		void remove_all();
		
		void display_members();
		void display_providers();
		void display_prov_dir();
		void display_recorded_ser();

	private:
		void verify_member(int member_number);		// verify that a member exists
		void verify_provider(int provider_number);	// verify that a provider exists
		void verify_service(int service_number);	// verify that a service exists
		int hash_function(int key_value);		// has function 

		// for the destructor	
		template <typename TYPE>
			void remove_all(node<TYPE> **table, int table_size);

		template <typename TYPE>
			void add_to_table(node<TYPE> **table, int table_size, TYPE &to_add);

		template <typename TYPE>	
			void remove_LLL(node<TYPE> *&head);

		template <typename TYPE>
			TYPE *find(node<TYPE> **table, int table_size, int number_to_find);


		template <typename TYPE>
			TYPE *find(node<TYPE> *& head, int number_to_find);


		template <typename TYPE>
			void display(node<TYPE> **table, int table_size);

		template <typename TYPE>
			void display(node<TYPE> *head);
		
		template <typename TYPE>	
			bool find_and_remove(node<TYPE> **table, int table_size, int number_to_find);

		template <typename TYPE>	
			bool find_and_remove(node<TYPE> *&head, int number_to_find);


		node<Member> **Members;						// member hash table
		int members_size;							// size of member hash table

		node<Provider> **Providers;					// provider hash table
		int providers_size;							// size of provider hash table

		//std::vector<Service> ProviderDirectory
		node<Service> **ProviderDirectory;			// provider directory hash table
		int prov_dir_size;							// size of provider directory hash table

		std::vector<ProvidedService> ProvidedServices;	// vector of provided services

};

//----------------------------------------------------------------
//------------------ Templated functions -------------------------
//----------------------------------------------------------------


// adding to table
	template <typename TYPE>
void Database::add_to_table(node<TYPE> **table, int table_size, TYPE &to_add)
{
	int index = hash_function(to_add.get_number());

	// allocate node
	node<TYPE>* new_node = new node<TYPE>(to_add);

	// chain at head
	new_node->next = table[index];
	table[index] = new_node;
}


// removing a LLL for index wrapper

	template <typename TYPE>
void Database::remove_all(node<TYPE> **table, int table_size)
{	
	for (int i = 0; i < table_size; ++i)
	{
		if (table[i])
			remove_LLL(table[i]);

		table[i] = nullptr;
	}	

	return;
}

// removing a LLL for index recursive

	template <typename TYPE>
void Database::remove_LLL(node<TYPE> *&head)
{
	if (!head)
		return;

	// get to end of list	
	remove_LLL(head->next);

	delete head;
	head = nullptr;	
	return;
}

	template <typename TYPE>
TYPE *Database::find(node<TYPE> **table, int table_size, int number_to_find)
{
	for (int i = 0; i < table_size; ++i)
	{
		if (table[i])
			return find(table[i], number_to_find);
	}

	return nullptr; // if enitiy not found	
}

	template <typename TYPE>
TYPE *Database::find(node<TYPE> *& head, int number_to_find)
{
	if (!head)
		return nullptr;

	if (head->data.get_number() == number_to_find)
		return &(head->data); // need to return a * type 

	return find(head->next, number_to_find);
}



template <typename TYPE>	
bool Database::find_and_remove(node<TYPE> **table, int table_size, int number_to_find)
{
	bool result = false;

	for (int i = 0; i < table_size; ++i)
	{
		result = find_and_remove(table[i], number_to_find);
		
		// if it was found in i's LLL
		if (result)
			break;
	}	
	
	return result;
}

template <typename TYPE>	
bool Database::find_and_remove(node<TYPE> *&head, int number_to_find)
{
	if (!head)
		return false;
	if (head->data.get_number() == number_to_find)
	{
		node<TYPE> *hold = head;
		head = head->next;
		delete hold;
		return true;
	}
	
	return find_and_remove(head->next, number_to_find);
}


template <typename TYPE>
void Database::display(node<TYPE> **table, int table_size)
{
	for (int i = 0; i < table_size; i++)
		display(table[i]);
}

	template <typename TYPE>
void Database::display(node<TYPE> *head)
{
	if (!head)
		return;

	head->data.display_all();
	display(head->next);
	return;
}

