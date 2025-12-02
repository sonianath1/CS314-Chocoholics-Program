/*******************************************************************************
  Chocoholics CS314 Program: Database Interface
Names: Yollaine Brooks, 
Description of Program: 
 *********************************************************************************/

#pragma once
#include <fstream>
#include <iostream>
#include "entities.h"
#include "node.h"
#include "error.h"
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
		friend class ServiceTest;	// friend test class for Service

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
		bool load_member_data();									// load data from file
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
		friend class DatabaseTest;                                  // friend database testing class

	private:
		void verify_member(int member_number);		// verify that a member exists
		void verify_provider(int provider_number);	// verify that a provider exists
		void verify_service(int service_number);	// verify that a service exists
		int hash_function(int key_value, int table_size);		// hash function 

		// for the destructor	
		template <typename TYPE>
			void remove_all(node<TYPE> **table, int table_size);

		template <typename TYPE>
			void add_to_table(node<TYPE> **table, int table_size, TYPE &to_add);

		template <typename TYPE>	
			void remove_LLL(node<TYPE> *&head);

		template <typename TYPE>
			TYPE *find(node<TYPE> **table, int number_to_find, int index);


		template <typename TYPE>
			TYPE *find(node<TYPE> *& head, int number_to_find);


		template <typename TYPE>
			void display(node<TYPE> **table, int table_size);

		template <typename TYPE>
			void display(node<TYPE> *head);
		
		template <typename TYPE>	
			bool find_and_remove(node<TYPE> **table, int number_to_find, int index);

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
	int index = hash_function(to_add.get_number(), table_size);

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
TYPE *Database::find(node<TYPE> **table, int number_to_find, int index)
{
//	int index = hash_function(number_to_find);
	return find(table[index], number_to_find);
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
bool Database::find_and_remove(node<TYPE> **table, int number_to_find, int index)
{
	//int index = hash_function(number_to_find);
	return find_and_remove(table[index], number_to_find);
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

//-------------------------------------------------------------
//---------------------- Test Classes -------------------------
//-------------------------------------------------------------


class DatabaseTest
{
    public:
        void constructor_test();
		void destructor_test();

		// read in everything from file. call in menu before starting program
		void read_from_file_test();

		// write to file with new / updated data. call after user requests to quit program 
		void write_to_file_test();

        void load_member_test();
		void write_member_test();
        void add_member_test();
        void update_member_test();
        void delete_member_test();
		void load_provider_test();
		void write_provider_test();
        void add_provider_test();
        void update_provider_test();
		void delete_provider_test();
		// Provider directory functions	
		void load_provider_directory_test();
		void write_provider_directory_test();
		void add_service_test();
        void get_service_data_test();
        void generate_weekly_report_test();


		// recorded services
		void load_provided_service_test();
		void write_provided_service_test();
		void record_provided_service_test();

		void verify_member_test();		// verify that a member exists
		void verify_provider_test();	// verify that a provider exists
		void verify_service_test();		// verify that a service exists
		void hash_function_test();		// has function 

		// member
		void member_remove_all_test();
		void member_add_to_table_test();
		void member_remove_LLL_test();
		void member_table_find_test();
		void member_LLL_find_test();
		void member_table_find_remove_test();
		void member_LLL_find__remove_test();
		
		// provider
		void provider_remove_all_test();
		void provider_add_to_table_test();
		void provider_remove_LLL_test();
		void provider_table_find_test();
		void provider_LLL_find_test();
		void provider_table_find_remove_test();
		void provider_LLL_find__remove_test();

		// provider directory
		void provider_directory_remove_all_test();
		void provider_directory_add_to_table_test();
		void provider_directory_remove_LLL_test();
		void provider_directory_table_find_test();
		void provider_directory_LLL_find_test();
		void provider_directory_table_find_remove_test();
		void provider_directory_LLL_find__remove_test();
};

class ServiceTest
{
	public:
		void default_constructor_test();
		void constructor_test();
		void get_number_test();
		void set_name_test();
		void set_fee_test();
		void set_code_test();
		void get_name_test();
		void get_fee_test();
		void display_all_test();
};
