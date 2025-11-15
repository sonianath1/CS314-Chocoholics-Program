/*******************************************************************************
Chocoholics CS314 Program: Entities Interface
Names: Yollaine Brooks,
Description of Program:
*********************************************************************************/

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
		int get_number();							// get identification number
		string & get_name();						// get name of entity
		bool compare_number(int number_to_compare);	// compare entity number with incoming number
		void update_data(Entity & to_copy);			// update entity data

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
		void update_data(Member & to_copy);	// update member data

	private:
		std::string status;					// Validated, Invalid Number, Member Suspended
};

// Provider Class
class Provider : public Entity
{
	public:
		Provider();								// constructor
		void update_data(Provider & to_copy);	// update provider data

	private:
		std::vector<int> services_provided;		// Services the provider provides

};