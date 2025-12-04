/*******************************************************************************
  Chocoholics CS314 Program: Entities Interface
Names: Yollaine Brooks,
Description of Program:
 *********************************************************************************/
#pragma once
#include <string>
#include <vector>
#include <regex>

using std::string;

// address struct
struct address
{
	string street_addr; // street address, max 25 char
	string city;		// max 14 char
	string state;		// max 2 char
	int zip_code;		// max 5 digits
};

// Base Entity Class
class Entity
{
	public:
		Entity();									// constructor
		Entity(const string, const int, const address);
		
		int get_number();							// get identification number
		string & get_name();						// get name of entity
		bool compare_number(int number_to_compare);	// compare entity number with incoming number
		void update_data(const Entity & to_copy);			// update entity data

		// setters	
		void set_name(const std::string & new_name) { name = new_name; }
		void set_number(int new_number) { number = new_number; }
		void set_address(address & new_address) { addr = new_address; }
		address & get_address() { return addr; }  // returns reference
		void display_all();
		friend class EntityTest;

	private:
		string name;		// 25 char max
		int number;			// identifier, max 9 digits
		address addr;		// address struct

};

// Member Class
class Member : public Entity
{
	public:
		Member();							// constructor
		Member(const string, const int, const address, const string);
		
		void update_data(const Member & to_copy);	// update member data

		void set_status(const std::string & new_status) { status = new_status; } // setter 
		std::string get_status() { return status; }
		void display_all();
		friend class MemberTest;
	private:
		std::string status;					// Validated, Invalid Number, Member Suspended
};

// Provider Class
class Provider : public Entity
{
	public:
		Provider();								// constructor
		Provider(const string, const int, const address, const std::vector<int>&);
		
		void update_data(const Provider & to_copy);	// update provider data
		
		// for vector 
		void add_service(int to_add) { services_provided.push_back(to_add); }
		std::vector<int> get_services() { return services_provided; }
		void clear_services() { services_provided.clear(); }
		void display_all();
		friend class ProviderTest;

	private:
		std::vector<int> services_provided;		// Services the provider provides

};

// Test Classes
class EntityTest
{
	public:
		void constructor_test();
		void get_number_test();								// get identification number
		void get_name_test();								// get name of entity
		void compare_number_test();	// compare entity number with incoming number
		void update_data();					// update entity data

		// setters	
		void set_name_test();
		void set_number_test();
		void get_address_test();
		void display_all_test();
};

class MemberTest
{
	public:
		void constructor_test();
		void update_data_test();
		void set_status_test();
		void get_status_test();
		void display_all_test();
};

class ProviderTest
{
	public:
		void constructor_test();
		void update_data_test();
		void add_service_test();
		void get_services_test();
		void clear_services_test();
		void display_all_test();
};
